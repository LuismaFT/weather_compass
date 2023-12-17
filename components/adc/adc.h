
#ifndef __HEADER_ADC__
#define __HEADER_ADC__

#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

#define ADC1_CHAN0          ADC_CHANNEL_0   // <-----------
// #define ADC1_CHAN1          ADC_CHANNEL_1
// #define ADC1_CHAN2          ADC_CHANNEL_2
#define ADC1_CHAN3          ADC_CHANNEL_3   // <-----------
#define ADC1_CHAN4          ADC_CHANNEL_4   // <-----------
#define ADC1_CHAN5          ADC_CHANNEL_5
#define ADC1_CHAN6          ADC_CHANNEL_6
#define ADC1_CHAN7          ADC_CHANNEL_7

#define ADC2_CHAN0          ADC_CHANNEL_0
#define ADC2_CHAN1          ADC_CHANNEL_1
#define ADC2_CHAN2          ADC_CHANNEL_2
#define ADC2_CHAN3          ADC_CHANNEL_3
#define ADC2_CHAN4          ADC_CHANNEL_4
#define ADC2_CHAN5          ADC_CHANNEL_5
#define ADC2_CHAN6          ADC_CHANNEL_6
#define ADC2_CHAN7          ADC_CHANNEL_7
#define ADC2_CHAN8          ADC_CHANNEL_8
#define ADC2_CHAN9          ADC_CHANNEL_9

#define ADC_ATTEN           ADC_ATTEN_DB_12

bool example_adc_calibration_init(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle);
void example_adc_calibration_deinit(adc_cali_handle_t handle);

struct value_and_voltage {
    int value;
    int voltage;
};

void adc_init();
void adc_terminate();
void adc_read_value(const int channel, struct value_and_voltage* value_and_voltage);

#endif // __HEADER_ADC__

