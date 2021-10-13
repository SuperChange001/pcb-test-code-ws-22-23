//
// Created by chao on 12/09/2021.
//

#ifndef MY_PROJECT_ADXL345_H
#define MY_PROJECT_ADXL345_H
#include "pico/stdlib.h"

#define I2C_CH i2c0
#define ADXL345_SLAVE_ADDR 0x53 // when ALT is connected to GND

/*! \brief  Check if the ADXL345 is on the I2C Bus
 *
 * \param none
 *
 * \returns -1: sensor is offline
 *          else: sensor on line
 */
int adxl345_onBus(void);



/*! \brief ADXL345 initialization
 *
 * \param none
 *
 * \returns -1: sensor is offline
 *          else: sensor is initialized
 */
int adxl345_init(void);


/*! \brief Read the accelerate data from the sensor
 *
 * \param *xAccl: to return acceleration in X-Axis
 * \param *yAccl: to return acceleration in Y-Axis
 * \param *zAccl: to return acceleration in Z-Axis
 *
 * \returns -1: sensor error
 *          else: valid data
 */
void adxl345_readData(int16_t *xAccl, int16_t *yAccl, int16_t *zAccl);

#endif //MY_PROJECT_ADXL345_H
