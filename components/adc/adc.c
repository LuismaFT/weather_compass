
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/soc_caps.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

#include "adc.h"

static int adc_raw[2][10];
static int voltage[2][10];

adc_oneshot_unit_handle_t adc1_handle;

adc_cali_handle_t adc1_cali_chan0_handle = NULL;
bool do_calibration1_chan0 = false;
adc_cali_handle_t adc1_cali_chan1_handle = NULL;
bool do_calibration1_chan1 = false;
adc_cali_handle_t adc1_cali_chan2_handle = NULL;
bool do_calibration1_chan2 = false;
adc_cali_handle_t adc1_cali_chan3_handle = NULL;
bool do_calibration1_chan3 = false;

void adc_read_value(const int channel, struct value_and_voltage* value_and_voltage) {
    adc_oneshot_read(adc1_handle, channel, &adc_raw[0][0]);
    value_and_voltage->value = adc_raw[0][0];
    adc_cali_raw_to_voltage(adc1_cali_chan0_handle, adc_raw[0][0], &voltage[0][0]);
    value_and_voltage->voltage =voltage[0][0];
}

void adc_init()
{
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };
    adc_oneshot_new_unit(&init_config1, &adc1_handle);
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN,
    };
    adc_oneshot_config_channel(adc1_handle, ADC1_CHAN0, &config);
    do_calibration1_chan0 = example_adc_calibration_init(ADC_UNIT_1, ADC1_CHAN0, ADC_ATTEN, &adc1_cali_chan0_handle);

    adc_oneshot_config_channel(adc1_handle, ADC1_CHAN6, &config);
    do_calibration1_chan1 = example_adc_calibration_init(ADC_UNIT_1, ADC1_CHAN6, ADC_ATTEN, &adc1_cali_chan1_handle);

    adc_oneshot_config_channel(adc1_handle, ADC1_CHAN4, &config);
    do_calibration1_chan2 = example_adc_calibration_init(ADC_UNIT_1, ADC1_CHAN4, ADC_ATTEN, &adc1_cali_chan2_handle);
    
    adc_oneshot_config_channel(adc1_handle, ADC1_CHAN5, &config);
    do_calibration1_chan3 = example_adc_calibration_init(ADC_UNIT_1, ADC1_CHAN5, ADC_ATTEN, &adc1_cali_chan3_handle);
}

void adc_terminate() {
    adc_oneshot_del_unit(adc1_handle);

    if (do_calibration1_chan0)
        example_adc_calibration_deinit(adc1_cali_chan0_handle);

    if (do_calibration1_chan1)
        example_adc_calibration_deinit(adc1_cali_chan1_handle);

    if (do_calibration1_chan2)
        example_adc_calibration_deinit(adc1_cali_chan2_handle);
    
    if (do_calibration1_chan3)
        example_adc_calibration_deinit(adc1_cali_chan3_handle);    

}

// ADC Calibration
bool example_adc_calibration_init(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle)
{
    adc_cali_handle_t handle = NULL;
    esp_err_t ret = ESP_FAIL;
    bool calibrated = false;

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    if (!calibrated) {
        //ESP_LOGI(TAG, "calibration scheme version is %s", "Curve Fitting");
        adc_cali_curve_fitting_config_t cali_config = {
            .unit_id = unit,
            .chan = channel,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_curve_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif
#if ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
    if (!calibrated) {
        // ESP_LOGI(TAG, "calibration scheme version is %s", "Line Fitting");
        adc_cali_line_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_line_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif
    *out_handle = handle;
    if (ret == ESP_OK) {
        printf("Calibration Success\n");
    } else if (ret == ESP_ERR_NOT_SUPPORTED || !calibrated) {
        printf("eFuse not burnt, skip software calibration\n");
    } else {
        printf("Invalid arg or no memory\n");
    }

    return calibrated;
}

void example_adc_calibration_deinit(adc_cali_handle_t handle)
{
#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    // ESP_LOGI(TAG, "deregister %s calibration scheme", "Curve Fitting");
    adc_cali_delete_scheme_curve_fitting(handle);
#elif ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
    // ESP_LOGI(TAG, "deregister %s calibration scheme", "Line Fitting");
    adc_cali_delete_scheme_line_fitting(handle);
#endif
}

