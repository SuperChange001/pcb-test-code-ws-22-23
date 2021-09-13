
#include "pico/stdlib.h"
#include <stdio.h>
#include "main.h"
#include "sht31.h"
#include "hardware/i2c.h"
#include "adxl345.h"
#include "pac193x.h"


/*
// 0x44 temp sensor
// 0x53 adxl345
int main()
{
    float temp, humidity;
    int16_t xAccl, yAccl, zAccl;
    stdio_init_all();

    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c1, 10 * 1000);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3  );
    adxl345_init();

    while(1)
    {
        char c=getchar_timeout_us(100);
        if(c=='t')
        {
            printf("hello: ");
            sht31_readTempHum(&temp,&humidity);
            printf("temp: %f, humidity: %f\r\n", temp, humidity);
            adxl345_readData(&xAccl, &yAccl, &zAccl);
            printf("acc_x: %d, acc_y:%d, acc_z:%d\r\n", xAccl, yAccl, zAccl);
        }

//        sleep_ms(1000);
    }

}
*/

int main()
{
    stdio_init_all();

    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c1, 10 * 1000);
    gpio_set_function(6, GPIO_FUNC_I2C);
    gpio_set_function(7, GPIO_FUNC_I2C);
    gpio_pull_up(6);
    gpio_pull_up(7);

    gpio_init(29);
    gpio_set_dir(29, GPIO_OUT);
    gpio_put(29, 1);

    pac193x_init();

    while(1)
    {
        char c=getchar_timeout_us(100);
        if(c=='t')
        {
            printf("hello: ");

            pac193x_printInfo();
        }

//        sleep_ms(1000);
    }

}
