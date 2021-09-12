#include <stdio.h>
#include "pico/stdlib.h"
#include "main.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

// I2C reserves some addresses for special purposes. We exclude these from the scan.
// These are any addresses of the form 000 0xxx or 111 1xxx
bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int main() {
    stdio_init_all();
//#if PICO_TINY2040_LEDS
//    gpio_init(PICO_DEFAULT_LED_PIN_R);
//    gpio_set_dir(PICO_DEFAULT_LED_PIN_R, GPIO_OUT);
//    gpio_init(PICO_DEFAULT_LED_PIN_G);
//    gpio_set_dir(PICO_DEFAULT_LED_PIN_G, GPIO_OUT);
//    gpio_init(PICO_DEFAULT_LED_PIN_B);
//    gpio_set_dir(PICO_DEFAULT_LED_PIN_B, GPIO_OUT);
//#endif
//    while (true) {
//        printf("Hello, world!\n");
//        gpio_put(PICO_DEFAULT_LED_PIN_R, 1);
//        sleep_ms(200);
//        gpio_put(PICO_DEFAULT_LED_PIN_G, 1);
//        sleep_ms(200);
//        gpio_put(PICO_DEFAULT_LED_PIN_B, 1);
//
//        sleep_ms(200);
//        gpio_put(PICO_DEFAULT_LED_PIN_R, 0);
//        sleep_ms(200);
//        gpio_put(PICO_DEFAULT_LED_PIN_G, 0);
//        sleep_ms(200);
//        gpio_put(PICO_DEFAULT_LED_PIN_B, 0);
//        sleep_ms(200);
//
//    }

    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(3, 2, GPIO_FUNC_I2C));

    printf("\nI2C Bus Scan\n");
    printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

//    for (int addr = 0; addr < (1 << 7); ++addr) {
        uint16_t addr = 0x23;
//        if (addr % 16 == 0) {
            printf("%02x ", addr);
//        }

        // Perform a 1-byte dummy read from the probe address. If a slave
        // acknowledges this address, the function returns the number of bytes
        // transferred. If the address byte is ignored, the function returns
        // -1.

        // Skip over any reserved addresses.
        int ret;
        uint8_t rxdata;
//        if (reserved_addr(addr))
//            ret = PICO_ERROR_GENERIC;
//        else
        ret = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);

        printf(ret < 0 ? "." : "@");
        printf(addr % 16 == 15 ? "\n" : "  ");
//    }
    printf("Done.\n");
    return 0;
}