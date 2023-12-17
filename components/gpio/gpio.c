
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#include "gpio.h"

void gpio_set_mode(int gpio_pin, int mode) {
    gpio_config_t io_conf = {};                     // zero-initialize the config structure.
    io_conf.intr_type = GPIO_INTR_DISABLE;          // disable interrupt
    if (mode == OUTPUT)
        io_conf.mode = GPIO_MODE_OUTPUT;            // set as output mode
    else if (mode == INPUT)
        io_conf.mode = GPIO_MODE_INPUT;             // set as input mode
    io_conf.pin_bit_mask = (1ULL<<gpio_pin);        // bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pull_down_en = 0;                       // disable pull-down mode
    io_conf.pull_up_en = 0;                         // disable pull-up mode
    gpio_config(&io_conf);                          // configure GPIO with the given settings
}

