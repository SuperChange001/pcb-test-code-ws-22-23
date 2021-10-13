//
// Created by chao on 13/09/2021.
//

#ifndef TESTSENSORBOARD_PAC193X_H
#define TESTSENSORBOARD_PAC193X_H
#include "pico/stdlib.h"
#define I2C_CH i2c1

#define PAC193X_SLAVE_ADDR 0x11 // when the addr_resistor is 499 Ohm


// PAC193x register addresses

#define PAC1934_REFRESH_CMD_ADDR            0x00
#define PAC1934_CTRL_ADDR                   0x01
#define PAC1934_ACC_COUNT_ADDR              0x02
#define PAC1934_VPOWER1_ACC_ADDR            0x03
#define PAC1934_VPOWER2_ACC_ADDR            0x04
#define PAC1934_VPOWER3_ACC_ADDR            0X05
#define PAC1934_VPOWER4_ACC_ADDR            0X06
#define PAC1934_VBUS1_ADDR                  0x07
#define PAC1934_VBUS2_ADDR                  0x08
#define PAC1934_VBUS3_ADDR                  0x09
#define PAC1934_VBUS4_ADDR                  0x0A
#define PAC1934_VSENSE1_ADDR                0x0B
#define PAC1934_VSENSE2_ADDR                0x0C
#define PAC1934_VSENSE3_ADDR                0X0D
#define PAC1934_VSENSE4_ADDR                0X0E
#define PAC1934_VBUS1_AVG_ADDR              0X0F
#define PAC1934_VBUS2_AVG_ADDR              0X10
#define PAC1934_VBUS3_AVG_ADDR              0X11
#define PAC1934_VBUS4_AVG_ADDR              0X12
#define PAC1934_VSENSE1_AVG_ADDR            0X13
#define PAC1934_VSENSE2_AVG_ADDR            0X14
#define PAC1934_VSENSE3_AVG_ADDR            0X15
#define PAC1934_VSENSE4_AVG_ADDR            0X16
#define PAC1934_VPOWER1_ADDR                0X17
#define PAC1934_VPOWER2_ADDR                0X18
#define PAC1934_VPOWER3_ADDR                0X19
#define PAC1934_VPOWER4_ADDR                0X1A
#define PAC1934_CHANNEL_DIS_ADDR            0X1C
#define PAC1934_NEG_PWR_ADDR                0X1D
#define PAC1934_REFRESH_G_CMD_ADDR          0x1E
#define PAC1934_REFRESH_V_CMD_ADDR          0x1F
#define PAC1934_SLOW_ADDR                   0X20
#define PAC1934_CTRL_ACT_ADDR               0X21
#define PAC1934_CHANNEL_DIS_ACT_ADDR        0X22
#define PAC1934_NEG_PWR_ACT_ADDR            0X23
#define PAC1934_CTRL_LAT_ADDR               0X24
#define PAC1934_CHANNEL_DIS_LAT_ADDR        0X25
#define PAC1934_NEG_PWR_LAT_ADDR            0x26

#define PAC1934_PRODUCT_ID_ADDR             0xFD
#define PAC1934_MANUFACTURER_ID_ADDR        0xFE
#define PAC1934_REVISION_ID_ADDR            0xFF



void pac193x_printInfo(void);
void pac193x_getInfo(uint8_t *product_id, uint8_t *manufacturer_id, uint8_t *revision_id);
int pac193x_init(void);



#endif //TESTSENSORBOARD_PAC193X_H
