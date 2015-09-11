#ifndef _UART1_H_
#define _UART1_H_

#include "ch.h"
#include "hal.h"
//#include "app.h"
extern uint16_t debug_buf[40];
extern uint8_t debug_bool;

/*
 #define U1_BRG					(1)
 #define ONE_BYTE_CYCLE_DIV8		((((U1_BRG + 1) * 16) * 11) / 8)
 #define TRANCEIVE_DELAY			(200 /8)
 #define CALLBACK_DELAY			(200 /8)

 #define U1_QUEUE_BIT_SIZE		(5)
 #define U1_QUEUE_SIZE			(1 << U1_QUEUE_BIT_SIZE)
 #define U1_QUEUE_BIT_MASK		(U1_QUEUE_SIZE - 1)
 */
#define ONE_BYTE_CYCLE_DIV8		((2000000 / 625000 * 8 ) ) /* ticks per bit */
#define TRANCEIVE_DELAY			(10)
#define CALLBACK_DELAY			(10)
#define U1_QUEUE_SIZE			(1 << 5)
#define U1_QUEUE_BIT_MASK		(U1_QUEUE_SIZE - 1)

typedef struct {
	semaphore_t sync_start_sem;
	event_source_t sync_complete_event;
} COMMDriver;
extern COMMDriver comm;

typedef struct {
	uint8_t ID;

	uint8_t NumberOfTransmitData;
	int8_t *ptrTransmitData;
	void (*FuncBeforeTransmit)(volatile void*);

	uint8_t NumberOfReceiveData;
	int8_t *ptrReceiveData;
	void (*FuncAfterReceive)(volatile void*);

	void (*FinishCallback)(volatile void*);

	uint32_t TranceiveTime;

	volatile void *arg;
} U1TRANCEIVE;

int32_t U1Enqueue(uint8_t ID, uint8_t NumberOfTransmitData, volatile void * ptrTransmitData, void (*FuncBeforeTransmit)(volatile void *), uint8_t NumberOfReceiveData,
		volatile void * ptrReceiveData, void (*FuncAfterReceive)(volatile void *), void (*FinishCallback)(volatile void*), volatile void *arg);

//static VirtualTimer uart_vt;

//extern Semaphore CtrlLpSem;

extern volatile int32_t U1ReceiveFramingErrorCount;
extern volatile int32_t U1ReceiveChecksumErrorCount;

void frame_end_timer(GPTDriver *gptp);
void rxerr(UARTDriver *uartp, uartflags_t e);
void rxend(UARTDriver *uartp);
void comm_lld_init(void);

#endif  /* _UART1_H_ */
