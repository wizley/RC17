#include "comm_lld.h"

uint16_t debug_buf[40] = {0};
uint8_t debug_bool = 0;

volatile int32_t U1Running = 0;
volatile int32_t U1ReceiveFramingErrorCount = 0;
volatile int32_t U1ReceiveChecksumErrorCount = 0;

//EVENTSOURCE_DECL(sync_complete_evt);
semaphore_t txSem;
COMMDriver comm;
//static VirtualTimer uart_vt;

static U1TRANCEIVE U1Queue[U1_QUEUE_SIZE];
static int32_t U1QueueHead = 0;
static int32_t U1QueueTail = 0;

int32_t U1Enqueue(uint8_t ID, uint8_t NumberOfTransmitData, volatile void *ptrTransmitData, void (*FuncBeforeTransmit)(volatile void*), uint8_t NumberOfReceiveData,
		volatile void *ptrReceiveData, void (*FuncAfterReceive)(volatile void*), void (*FinishCallback)(volatile void*), volatile void *arg) {

	int32_t head = U1QueueHead;
	int32_t tail = U1QueueTail;
	int32_t n;

	if ((tail + 1 == U1_QUEUE_SIZE && head == 0) || (tail + 1 == head)) {
		return 0;
	}

	U1Queue[tail].ID = ID;
	U1Queue[tail].NumberOfTransmitData = NumberOfTransmitData;
	U1Queue[tail].ptrTransmitData = (int8_t*) ptrTransmitData;
	U1Queue[tail].FuncBeforeTransmit = FuncBeforeTransmit;
	U1Queue[tail].NumberOfReceiveData = NumberOfReceiveData;
	U1Queue[tail].ptrReceiveData = (int8_t*) ptrReceiveData;
	U1Queue[tail].FuncAfterReceive = FuncAfterReceive;
	U1Queue[tail].FinishCallback = FinishCallback;
	U1Queue[tail].arg = arg;
	n = NumberOfTransmitData > NumberOfReceiveData ? NumberOfTransmitData : NumberOfReceiveData;
	n = n > 0 ? n + 2 : 1;
	U1Queue[tail].TranceiveTime = n * ONE_BYTE_CYCLE_DIV8 + TRANCEIVE_DELAY;

	if (FuncBeforeTransmit) {
		U1Queue[tail].TranceiveTime += CALLBACK_DELAY; // Allocate extra time slot for calling function
	}
	if (FuncAfterReceive) {
		U1Queue[tail].TranceiveTime += CALLBACK_DELAY; // Allocate extra time slot for calling function
	}
	if (FinishCallback) {
		U1Queue[tail].TranceiveTime += CALLBACK_DELAY; // Allocate extra time slot for calling function
	}

	//chSysLock();
	U1QueueTail = (tail + 1) & U1_QUEUE_BIT_MASK;
	if (head == tail) {
		chSysLock();
		chSemSignalI(&txSem);
		chSchRescheduleS();
		chSysUnlock();
	}

	//chSysUnlock();
	return 1;
}

typedef struct {
	uint8_t NumberOfData;
	uint16_t Buffer[32]; // TODO to uint8_t
	uint16_t *ptrBuffer;
	uint8_t checksum;
} U1BUFFER;

static U1BUFFER U1Transmit;
static U1BUFFER U1Receive;
static U1TRANCEIVE * Sequence = &U1Queue[0];

UARTConfig uart_cfg_1 = {
	NULL, /* End of Transmission buffer callback               */
	NULL, /* Physical end of transmission callback             */
	rxend, /* Receive buffer filled callback                    */
	NULL, /* Char received while out of the UART_RECEIVE state */
	rxerr, /* Receive error callback                            */
	625000UL, /* Baudrate                                          */
	USART_CR1_M | USART_CR1_RE | USART_CR1_TE, /* cr1 register values     */
	USART_CR2_LBDL, /* cr2 register values                               */
	0 /* cr3 register values                               */
};

GPTConfig gpt_cfg = {
	2000000, /* Timer clock in Hz. */
	frame_end_timer, /* Timer callback     */
	0,
	0
};

void frame_end_timer(GPTDriver *gptp) {
//void Trigger(void *p) {
	(void) gptp;

	//chSysLockFromIsr();
	//uartStopReceiveI(&UARTD6);
	//chSysUnlockFromIsr();
	if (Sequence->FinishCallback != 0)
		Sequence->FinishCallback(Sequence->arg); // TODO

	U1QueueHead = (U1QueueHead + 1) & U1_QUEUE_BIT_MASK;

	if (U1QueueHead == U1QueueTail) {
//		chSysLockFromIsr();
//		chSemSignalI(&CtrlLpSem);
//		chSysUnlockFromIsr();
		chSysLockFromISR();
		chEvtBroadcastFlagsI(&comm.sync_complete_event, EVENT_MASK(0)); //TODO to ptr
		chSysUnlockFromISR();
	} else {
		chSysLockFromISR();
		chSemSignalI(&txSem);
		chSysUnlockFromISR();
	}
	//chSysUnlockFromIsr();
	return;
}

static THD_WORKING_AREA(waIncomingFrame, 4096);
static THD_FUNCTION(ProcessIncomingFrame, arg){
	chRegSetThreadName("ProcessIncomingFrame");
	(void) arg;

	while (TRUE) {
		chSemWait(&txSem);

		Sequence = &U1Queue[U1QueueHead];

		U1Transmit.Buffer[0] = ((int16_t) (Sequence->ID)) | 0x100;

		//chSysLock();
		/* Starts the timer.*/
		//chVTSetI(&uart_vt, MS2ST(1), Trigger, NULL); // TODO
		//chSysUnlock();
		//gptStartOneShot(&GPTD1, 1 * 2000000 / 1000);
		gptStartOneShot(&GPTD14, Sequence->TranceiveTime);

		// Transmit
		if (Sequence->FuncBeforeTransmit != 0)
			Sequence->FuncBeforeTransmit(Sequence->arg);

		U1Transmit.NumberOfData = Sequence->NumberOfTransmitData + 1;
		if (U1Transmit.NumberOfData > 1) {
			int8_t checksum = 0xAA ^ Sequence->ID;
			int8_t i;
			for (i = 1; i < U1Transmit.NumberOfData; i++) {
				U1Transmit.Buffer[i] = Sequence->ptrTransmitData[i - 1] & 0xFF;
				checksum ^= U1Transmit.Buffer[i];
			}
			U1Transmit.Buffer[i] = checksum & 0xFF;
			//U1Transmit.ptrBuffer = (uint8_t*) U1Transmit.Buffer;
			U1Transmit.ptrBuffer = U1Transmit.Buffer;
			U1Transmit.NumberOfData++;
		}

		uartStartSend(&UARTD1, U1Transmit.NumberOfData, U1Transmit.ptrBuffer);

		//U1Receive.NumberOfData = Sequence->NumberOfReceiveData > 0 ? Sequence->NumberOfReceiveData + 1 : 0;
		U1Receive.NumberOfData = Sequence->NumberOfReceiveData + 1;
		//U1Receive.ptrBuffer = (uint8_t*) U1Receive.Buffer;
		U1Receive.ptrBuffer = U1Receive.Buffer;
		U1Receive.checksum = Sequence->ID;
		uartStopReceive(&UARTD1);
		uartStartReceive(&UARTD1, U1Receive.NumberOfData, U1Receive.ptrBuffer);
	}
	//return;
}

void rxerr(UARTDriver *uartp, uartflags_t e) {
	(void) uartp;
	(void) e;
	//U1ReceiveFramingErrorCount++;
	U1ReceiveFramingErrorCount = e;
	U1Receive.NumberOfData = 0;
}

void rxend(UARTDriver *uartp) {
	int8_t i;
	(void) uartp;
    //debug_bool = 0;
	for (i = 0; i <= Sequence->NumberOfReceiveData; i++) {
		U1Receive.checksum ^= U1Receive.Buffer[i];
		debug_buf[i] =U1Receive.Buffer[i];

	}
    //debug_bool = 1;
	if (U1Receive.checksum == 0xAA) {
		for (i = 0; i < Sequence->NumberOfReceiveData; i++) {
			Sequence->ptrReceiveData[i] = U1Receive.Buffer[i];
		}
		if (Sequence->FuncAfterReceive != 0)
			Sequence->FuncAfterReceive(Sequence->arg);
	} else {
		U1ReceiveChecksumErrorCount++;
	}

}

void comm_lld_init(void) {

	palClearPad(GPIOG, GPIOG_USART1_EN);
	uartStart(&UARTD1, &uart_cfg_1);
	gptStart(&GPTD14, &gpt_cfg);

	chSemObjectInit(&txSem, 0);
	chThdCreateStatic(waIncomingFrame, sizeof(waIncomingFrame), HIGHPRIO, ProcessIncomingFrame, NULL);

	U1Running = 0;

	U1Transmit.NumberOfData = 0;

	U1ReceiveFramingErrorCount = 0;
	U1ReceiveChecksumErrorCount = 0;
}
