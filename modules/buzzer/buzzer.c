#include "ch.h"
#include "hal.h"
#include "buzzer.h"

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
		pwmDisableChannel(&PWMDRIVER, 2);
		chSemWait(&sem);
		while(tone_s->freq_hz != 0 || tone_s->duration_ms != 0){
			if(state == STOP)
				break;
			else {
				if(tone_s->freq_hz != 0){
					pwmcfg.period = FREQUENCY_TO_PERIOD(tone_s->freq_hz);
					pwmStart(&PWMDRIVER, &pwmcfg);
					pwmEnableChannel(&PWMDRIVER, 2, PWM_PERCENTAGE_TO_WIDTH(&PWMDRIVER, 5000));
				} else
					pwmEnableChannel(&PWMDRIVER, 2, PWM_PERCENTAGE_TO_WIDTH(&PWMDRIVER, 0));
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
