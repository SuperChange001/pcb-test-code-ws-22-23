/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/dma.h"
#define NSAMP 1000

void __not_in_flash_func(adc_capture)(uint16_t *buf, size_t count) {
    adc_fifo_setup(true, false, 0, false, false);
    adc_run(true);
    for (int i = 0; i < count; i = i + 1)
        buf[i] = adc_fifo_get_blocking();
    adc_run(false);
    adc_fifo_drain();
}

int main() {
    uint16_t adc_buf[NSAMP];

    stdio_init_all();
    printf("ADC Example, measuring GPIO26\n");

    adc_init();

    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    adc_gpio_init(27);
    // Select ADC input 0 (GPIO26)
    adc_set_clkdiv(9600); //5K samples per second

    while (1) {
        // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
        adc_select_input(1);
        const float conversion_factor = 3.3f / (1 << 12);
        uint16_t result = adc_read();
        printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);

        adc_run(false);
        adc_select_input(0);
        adc_capture(adc_buf, NSAMP);
        printf("audio:\r\n");
        for(int ii=0;ii<NSAMP;ii++){
            printf("%d,", adc_buf[ii]);
        }
        printf("\r\n");


//        const float conversion_factor = 3.3f / (1 << 12);
//        uint16_t result = adc_read();
//        printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
        sleep_ms(500);
    }
}