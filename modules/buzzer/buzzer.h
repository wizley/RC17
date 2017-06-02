/*
 * buzzer.h
 *
 *  Created on: Jun 22, 2015
 *      Author: u564
 */

#ifndef MODULES_BUZZER_BUZZER_H_
#define MODULES_BUZZER_BUZZER_H_

#define PWMDRIVER PWMD2

#define PWM_TIME_BASE 14000000 /* 14 MHz */

#define FREQUENCY_TO_PERIOD(freq)	(PWM_TIME_BASE / freq)

typedef struct {
	uint16_t freq_hz;
	uint16_t duration_ms;
} buzzer_tone_t;

typedef int16_t buzzer_mode_t;

typedef enum {
	PLAYING = 0,
	STOP = 1
} buzzer_state_t;

void buzzer_init(void);
void buzzer_play(buzzer_tone_t *tone, buzzer_mode_t mode);
void buzzer_stop(void);

#endif /* MODULES_BUZZER_BUZZER_H_ */
