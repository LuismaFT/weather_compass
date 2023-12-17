
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"

#include "esp_sleep.h"
#include "gpio.h"
#include "adc.h"
#include "utils.h"
#include "http.h"

typedef struct value_and_voltage vav;

// punto de entrada de la aplicación
void app_main(void)
{
    struct value_and_voltage vav;
     
    const int wakeup_time_sec = 5;
    int temperature_value = 0;
    int temperature_voltage = 0;
    int lumenes_value = 0;
    int lumenes_voltage= 0;
    int agua_value = 0;
    int agua_voltage = 0;
    float luxs = 0;
    float cels = 0;
    float percentage = 0;

    adc_init();
    init_http();
    while (1) {
        adc_read_value(ADC1_CHAN4, &vav);
        temperature_value = vav.value;
        temperature_voltage = vav.voltage;
        cels = mv_to_celsius(temperature_voltage);
        

        adc_read_value(ADC1_CHAN6, &vav);
        lumenes_value = vav.value;
        lumenes_voltage = vav.voltage;
        luxs = mv_to_lux(lumenes_voltage);
           
        adc_read_value(ADC1_CHAN5, &vav);
        agua_value = vav.value;
        agua_voltage = vav.voltage;
        percentage = value_to_percent(agua_value);
        

        printf("temperature_value = %f\n", cels);
        printf("temperature_voltage_value = %d\n",temperature_value);
        struct url_data data = {"chAU4l9GZJVQTTh2LIci/telemetry", "temperature", "", cels, ""};
        http_post(&data);
        struct url_data data6 = {"chAU4l9GZJVQTTh2LIci/attributes", "temperature", "", cels, ""};
        http_post(&data6);
        
        printf("lumenes_value = %f\n", luxs);
        printf("lumenes_mv = %d\n", lumenes_voltage);
        struct url_data data2 = {"chAU4l9GZJVQTTh2LIci/telemetry", "lumenes", "", luxs, ""};
        http_post(&data2);
        struct url_data data3 = {"chAU4l9GZJVQTTh2LIci/attributes", "lumenes", "", luxs, ""};
        http_post(&data3);
        
        printf("agua_percentage = %f\n", percentage);
        printf("agua_value = %d\n", agua_value);
        struct url_data data4 = {"chAU4l9GZJVQTTh2LIci/telemetry", "agua", "", percentage, ""};
        http_post(&data4);
        struct url_data data5 = {"chAU4l9GZJVQTTh2LIci/attributes", "agua", "", percentage, ""};
        http_post(&data5);

        vTaskDelay(pdMS_TO_TICKS(2000));
        printf("Enable timer wakeup, %ds a mimir \n", wakeup_time_sec);
        esp_sleep_enable_timer_wakeup(wakeup_time_sec * 1000000);
        esp_deep_sleep_start();
    }

    adc_terminate();
}

