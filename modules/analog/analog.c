//<<<<<<< HEAD
///*
// * analog.c
// *
// *  Created on: Jun 20, 2015
// *      Author: u564
// */
//
//#include "ch.h"
//#include "hal.h"
//#include "analog.h"
//
//static adcsample_t samples2[ADC_GRP2_NUM_CHANNELS * ADC_GRP2_BUF_DEPTH];
///*
// * ADC streaming callback.
// */
//uint16_t ADCValue[8] = {0};
//static void adccallback(ADCDriver *adcp, adcsample_t *buffer, size_t n) {
//  //dmaBufferInvalidate(buffer, n);
//  if(samples2 != buffer){
////  if (adcp == &ADCD1){
////    if (adcp->state == ADC_COMPLETE) {
//
//         ADCValue[0] = (uint16_t)((samples2[0]+samples2[8]+samples2[16]+samples2[24]+samples2[32]+samples2[40]+samples2[48]+samples2[56])/8.0);
////      }
////     if (samples2 == buffer) {
////       nx += n;
////     }
////     else {
////       ny += n;
////     }
//  }
//}
//
//static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {
//
//  (void)adcp;
//  (void)err;
//
//  osalDbgAssert(TRUE, "ADC ERROR");
//}
//
///*
// * ADC conversion group.
// * Mode:        Continuous, 16 samples of 8 channels, SW triggered.
// * Channels:    IN11, IN12, IN11, IN12, IN11, IN12, Sensor, VRef.
// */
//static const ADCConversionGroup adcgrpcfg2 = {
//  TRUE,
//  ADC_GRP2_NUM_CHANNELS,
//  adccallback,
//  adcerrorcallback,
//  0,                        /* CR1 */
//  ADC_CR2_SWSTART,          /* CR2 */
//  ADC_SMPR1_SMP_AN11(ADC_SAMPLE_56) |
//  ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_144) | ADC_SMPR1_SMP_VREF(ADC_SAMPLE_144),
//  ADC_SMPR2_SMP_AN0(ADC_SAMPLE_56),                        /* SMPR2 */
//  ADC_SQR1_NUM_CH(ADC_GRP2_NUM_CHANNELS),
//  ADC_SQR2_SQ8_N(ADC_CHANNEL_SENSOR) | ADC_SQR2_SQ7_N(ADC_CHANNEL_VREFINT),
//  ADC_SQR3_SQ6_N(ADC_CHANNEL_IN0)   | ADC_SQR3_SQ5_N(ADC_CHANNEL_IN11) |
//  ADC_SQR3_SQ4_N(ADC_CHANNEL_IN0)   | ADC_SQR3_SQ3_N(ADC_CHANNEL_IN11) |
//  ADC_SQR3_SQ2_N(ADC_CHANNEL_IN0)   | ADC_SQR3_SQ1_N(ADC_CHANNEL_IN11)
//};
//
//
//void adc_init(void){
///*
// * Activates the ADC1 driver and the temperature sensor.
// */
//adcStart(&ADCD1, NULL);
//adcSTM32EnableTSVREFE();
///*
// * Starts an ADC continuous conversion.
// */
//adcStartConversion(&ADCD1, &adcgrpcfg2, samples2, ADC_GRP2_BUF_DEPTH);
//}
//=======
/*
 * analog.c
 *
 *  Created on: Jun 20, 2015
 *      Author: u564
 */

#include "ch.h"
#include "hal.h"
#include "analog.h"

static adcsample_t samples2[ADC_GRP2_NUM_CHANNELS * ADC_GRP2_BUF_DEPTH];
/*
 * ADC streaming callback.
 */
uint16_t ADCValue[8] = {0};
static void adccallback(ADCDriver *adcp, adcsample_t *buffer, size_t n) {
  if(samples2 != buffer){
//  if (adcp == &ADCD1){
//    if (adcp->state == ADC_COMPLETE) {

         ADCValue[0] = (uint16_t)((samples2[0]+samples2[8]+samples2[16]+samples2[24]+samples2[32]+samples2[40]+samples2[48]+samples2[56])/8.0);
//      }
//     if (samples2 == buffer) {
//       nx += n;
//     }
//     else {
//       ny += n;
//     }
  }
}

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {

  (void)adcp;
  (void)err;

  osalDbgAssert(TRUE, "ADC ERROR");
}

/*
 * ADC conversion group.
 * Mode:        Continuous, 16 samples of 8 channels, SW triggered.
 * Channels:    IN11, IN12, IN11, IN12, IN11, IN12, Sensor, VRef.
 */
static const ADCConversionGroup adcgrpcfg2 = {
  TRUE,
  ADC_GRP2_NUM_CHANNELS,
  adccallback,
  adcerrorcallback,
  0,                        /* CR1 */
  ADC_CR2_SWSTART,          /* CR2 */
  ADC_SMPR1_SMP_AN11(ADC_SAMPLE_56) |
  ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_144) | ADC_SMPR1_SMP_VREF(ADC_SAMPLE_144),
  ADC_SMPR2_SMP_AN0(ADC_SAMPLE_56),                        /* SMPR2 */
  ADC_SQR1_NUM_CH(ADC_GRP2_NUM_CHANNELS),
  ADC_SQR2_SQ8_N(ADC_CHANNEL_SENSOR) | ADC_SQR2_SQ7_N(ADC_CHANNEL_VREFINT),
  ADC_SQR3_SQ6_N(ADC_CHANNEL_IN0)   | ADC_SQR3_SQ5_N(ADC_CHANNEL_IN11) |
  ADC_SQR3_SQ4_N(ADC_CHANNEL_IN0)   | ADC_SQR3_SQ3_N(ADC_CHANNEL_IN11) |
  ADC_SQR3_SQ2_N(ADC_CHANNEL_IN0)   | ADC_SQR3_SQ1_N(ADC_CHANNEL_IN11)
};


void adc_init(void){
/*
 * Activates the ADC1 driver and the temperature sensor.
 */
adcStart(&ADCD1, NULL);
adcSTM32EnableTSVREFE();
/*
 * Starts an ADC continuous conversion.
 */
adcStartConversion(&ADCD1, &adcgrpcfg2, samples2, ADC_GRP2_BUF_DEPTH);
}
//>>>>>>> 8a0975270c4439013eb3433a11c64826ce44e612
