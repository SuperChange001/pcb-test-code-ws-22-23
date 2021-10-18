
#include "pico/stdlib.h"
#include <stdio.h>
#include "main.h"
#include "sht31.h"
#include "hardware/i2c.h"
#include "adxl345.h"
#include "pac193x.h"
#include "hardware/adc.h"

void setup_i2c1_sda_line(void){
    gpio_set_function(6, GPIO_FUNC_I2C);
    gpio_pull_up(6);
}

void setup_i2c1_scl_line(void){
    gpio_set_function(7, GPIO_FUNC_I2C);
    gpio_pull_up(7);
}

void setup_i2c1(void) {
    int baud_rate = 10 * 1000;
    i2c_init(i2c1, baud_rate);
    setup_i2c1_sda_line();
    setup_i2c1_scl_line();
}

void setup_i2c0_sda_line(void){
    gpio_set_function(0, GPIO_FUNC_I2C);
    gpio_pull_up(0);
}

void setup_i2c0_scl_line(void){
    gpio_set_function(1, GPIO_FUNC_I2C);
    gpio_pull_up(1);
}

 void setup_i2c0(void) {
    int baud_rate = 10 * 1000;
    i2c_init(i2c0, baud_rate);
    setup_i2c0_sda_line();
    setup_i2c0_scl_line();
}

int main()
{
    float temp, humidity;
    int16_t xAccl, yAccl, zAccl;

    stdio_init_all();

    setup_i2c1();
    setup_i2c0();

    pac193x_init();
    adxl345_init();

    //==================================================
//    adc_init();
//    // Make sure GPIO is high-impedance, no pullups etc
//    adc_gpio_init(26);
//    adc_gpio_init(27);
//    // Select ADC input 0 (GPIO26)
//    adc_set_clkdiv(9600); //5K samples per second

    while(1)
    {
        char c=getchar_timeout_us(10000);
        if(c=='t')
        {
            printf("hello: ");
            pac193x_printInfo();
            sht31_readTempHum(&temp,&humidity);
            printf("temp: %f, humidity: %f\r\n", temp, humidity);
            adxl345_readData(&xAccl, &yAccl, &zAccl);
            printf("acc_x: %d, acc_y:%d, acc_z:%d\r\n", xAccl, yAccl, zAccl);
        }

//        sleep_ms(1000);
    }

}
