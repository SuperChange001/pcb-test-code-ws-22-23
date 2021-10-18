//
// Created by chao on 12/09/2021.
//

#include "sht31.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>

/**
 * Performs a CRC8 calculation on the supplied values.
 *
 * @param data  Pointer to the data to use when calculating the CRC8.
 * @param len   The number of bytes in 'data'.
 *
 * @return The computed CRC8 value.
 */
static uint8_t crc8(const uint8_t *data, int len) {
    /*
     * CRC-8 formula from page 14 of SHT spec pdf
     * Test data 0xBE, 0xEF should yield 0x92
     *
     * Initialization data 0xff
     * Polynomial 0x31 (x8 + x5 + x4 +1)
     * Final XOR 0x00
     */


    uint8_t crc = 0xff;

    for (int j = len; j; --j) {
        crc ^= *data++;

        for (int i = 8; i; --i) {
            crc = (crc & 0x80) ? (crc << 1) ^ 0x31 : (crc << 1);
        }
    }
    return crc;
}

/**
 * Internal function to perform a temp + humidity read.
 *
 * @return True if successful, otherwise false.
 */
int sht31_readTempHum(float *temp, float *humidity) {
    int ret;
    uint8_t readbuffer[6];
    uint8_t cmdbuffer[2]={0x2C, 0x06};


    i2c_write_blocking(i2c0, 0x44, cmdbuffer, 2, false);

    sleep_ms(500);

    ret = i2c_read_blocking(i2c0, 0x44, readbuffer, sizeof(readbuffer), false);

    if (readbuffer[2] != crc8(readbuffer, 2) ||
        readbuffer[5] != crc8(readbuffer + 3, 2)){
        ret=-1;
        return ret;
    }

    int32_t stemp = (int32_t)(((uint32_t)readbuffer[0] << 8) | readbuffer[1]);
    // simplified (65536 instead of 65535) integer version of:
    // temp = (stemp * 175.0f) / 65535.0f - 45.0f;
    stemp = ((4375 * stemp) >> 14) - 4500;
    *temp = (float)stemp / 100.0f;

    uint32_t shum = ((uint32_t)readbuffer[3] << 8) | readbuffer[4];
    // simplified (65536 instead of 65535) integer version of:
    // humidity = (shum * 100.0f) / 65535.0f;
    shum = (625 * shum) >> 12;
    *humidity = (float)shum / 100.0f;


    return true;
}
