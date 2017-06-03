#include "ch.h"
#include "hal.h"
#include "buzzer.h"

#define t (1000)

typedef enum NOTETYPE {g_=392,a=440,a_sharp=466,b=494,c=523,c_sharp=554,d=587,d_sharp=622,e=659,f=698,f_sharp=740,g=784,g_sharp=831,
                       // A1=440,A1_sharp=466,B1=494,C1=523,C1_sharp=554,D1=587,D1_sharp=622,E1=659,F1=349,F1_sharp=699,G1=784,G1_sharp=831,
                       A1=880,A1_sharp=932,B1=988,C1=1047,C1_sharp=1109,D1=1175,D1_sharp=1245,E1=1319,F1=1397,F1_sharp=1475,G1=1568,G1_sharp=1661,
                       A2=1760,A2_sharp=1865,B2=1976,C2=2083,C2_sharp=2218,D2=2349,D2_sharp=2489,E2=2637,F2=2794,F2_sharp=2960,G2=3136,G2_sharp=3322
}Note;

buzzer_tone_t start_mode[] = {
   {C1,100},
   {F2,200},
   {A2,200},
   {C2,200},
   {A2,100},
   {C2,300},
   {0,0}
};

buzzer_tone_t out_battery[] = {
  {F2,100},
  {B2,100},
  {0,0},
};

buzzer_tone_t beep[] = {
  {F2, t/4},
  {0,0}
};
buzzer_tone_t song2[] = {
  {d,t/4},{e,t/4},{f,t/2},{f,t/4},{f,t/4},{f,t/2},{f,t/2},{e,t/2},
  {d,t/2},{c,t/4},{c,t*3/4},{c,t},{a,t/4},{g_,t*3/4},{0,t/2},{f,t/4},
  {f,t/4},{f,t/2},{f,t/4},{g,t/4},{g,t/2},{g,t/2},{f,t/4},{g,t/2},{A1,t/4},
  {A1,2*t},{A1,t},{g,t/4},{f,t*3/4},{0,t/2},{f,t/4},{f,t/4},{f,t/2},{f,t/2},
  {g,t},{0,t/2},{c,t/4},{c,t/4},{A1,t},{g,t},{f,2*t},{0,t/2},{f,t/4},{f,t/4},
  {f,t/2},{f,t/4},{g,t/4},{g,t/2},{g,t/4},{g,t/4},{f,t/4},{f,t/2},{g,t/4},{g,4*t},{0,8*t},{0,0}
};

buzzer_tone_t song[] = {
  {E2,t/8},{D2,t/8},{F1_sharp,t/4},{G1_sharp,t/4},
  {C2_sharp,t/8},{B2,t/8},{D1,t/4},{E1,t/4},
  {B2,t/8},{A2,t/8},{C1_sharp,t/4},{E1,t/4},{A2,t/4},{A2,t},{0,0}
};

buzzer_tone_t song1[] = {
  {G1, t/2}, {G1, t/2}, {G1, t/2}, {D1_sharp, t/4},
  {F1, t/4}, {F1, t/4}, {F1, t/4}, {D1, t/4},{0,0}
};

static buzzer_tone_t *tone_s = NULL;
static buzzer_tone_t *head = NULL;
static buzzer_state_t state = STOP;
static buzzer_mode_t mode_s;
static semaphore_t sem;

static PWMConfig pwmcfg = {
	PWM_TIME_BASE,        /* 14MHz PWM clock frequency.   */
	PWM_TIME_BASE,            /* PWM period in ticks*/
	NULL,
	{
	 {PWM_OUTPUT_DISABLED, NULL},
	 {PWM_OUTPUT_DISABLED, NULL},
	 {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* TIM2_CH3 PB10 -> DIO7*/
	 {PWM_OUTPUT_DISABLED, NULL}
	},
	0,
	0
};


THD_WORKING_AREA(wabuzzer, 256);
THD_FUNCTION(buzzer_thread, arg) {
	chRegSetThreadName("buzzer");
	(void)arg;

	while (!chThdShouldTerminateX()) {
		state = STOP;
		pwmDisableChannel(&PWMDRIVER, PWMCHANNEL);
		chSemWait(&sem);
		while(tone_s->freq_hz != 0 || tone_s->duration_ms != 0){
			if(state == STOP)
				break;
			else {
				if(tone_s->freq_hz != 0){
					pwmcfg.period = FREQUENCY_TO_PERIOD(tone_s->freq_hz);
					pwmStart(&PWMDRIVER, &pwmcfg);
					pwmEnableChannel(&PWMDRIVER, PWMCHANNEL, PWM_PERCENTAGE_TO_WIDTH(&PWMDRIVER, 5000));
				} else
					pwmEnableChannel(&PWMDRIVER, PWMCHANNEL, PWM_PERCENTAGE_TO_WIDTH(&PWMDRIVER, 0));
				chThdSleepMilliseconds(tone_s->duration_ms);
			}
			if((++tone_s)->freq_hz == 0 && tone_s->duration_ms == 0 ){
				if(mode_s == -1 || --mode_s > 0)
					tone_s = head;
				else{
					state = STOP;
					break;
				}
			}
		}
	}
}

void buzzer_init(void) {
	pwmStart(&PWMDRIVER, &pwmcfg);
	nvicDisableVector(STM32_TIM2_NUMBER);
	chSemObjectInit(&sem, 0);
	chThdCreateStatic(wabuzzer, sizeof(wabuzzer), LOWPRIO, buzzer_thread, NULL);

}

void buzzer_play(buzzer_tone_t *tone, buzzer_mode_t mode) {
	if(tone != NULL && state == STOP) {
		tone_s = tone;
		head = tone;
		mode_s = mode;
		state = PLAYING;
		chSemSignal(&sem);
	}
}

void buzzer_stop(void){
	state = STOP;
}
