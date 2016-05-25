/*
 * analog.h
 *
 *  Created on: May 5, 2016
 *      Author: Melvin
 */

#ifndef MODULES_ANALOG_ANALOG_H_
#define MODULES_ANALOG_ANALOG_H_

#define ADC_GRP2_NUM_CHANNELS   8
#define ADC_GRP2_BUF_DEPTH      16
static adcsample_t samples2[ADC_GRP2_NUM_CHANNELS * ADC_GRP2_BUF_DEPTH];
extern uint16_t ADCValue[8];
void adc_init(void);

#endif /* MODULES_ANALOG_ANALOG_H_ */
