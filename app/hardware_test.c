#include <stdio.h>
#include "hardware_setup.h"
#include "sensor_lib/adxl345.h"
#include "sensor_lib/pac193x.h"
#include "sensor_lib/sht31.h"

int main(void)
{
    initializePeripherals();

    float temp, humidity;
    int16_t xAccl, yAccl, zAccl;

    while (1)
    {
        char c = getchar_timeout_us(10000);
        if (c == 't')
        {
            printf("hello\r\n");
            pac193x_printInfo();
            sht31_readTempHum(&temp, &humidity);
            printf("temp: %f, humidity: %f\r\n", temp, humidity);
            adxl345_readData(&xAccl, &yAccl, &zAccl);
            printf("acc_x: %d, acc_y:%d, acc_z:%d\r\n", xAccl, yAccl, zAccl);

            float res_voltage = adc_measure_voltage();
            printf("Voltage: %f V\n", res_voltage);

            adc_print_audio_record();
        }
        //        sleep_ms(1000);
    }
}

//  ToDo:
// * refactoring the sht31 lib
// * refactoring the adxl345 lib
// *
// * /
