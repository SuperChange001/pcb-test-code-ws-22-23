//
// Created by chao on 13/09/2021.
//

#include "pac193x.h"
#include "hardware/i2c.h"
#include <stdio.h>

/*! \brief  Check if the PAC193x is on the I2C Bus
 *
 * \param none
 *
 * \returns -1: sensor is offline
 *          else: sensor on line
 */
int pac193x_onBus(uint8_t device_slave_addr)
{
    int ret;
    uint8_t readbuffer[2];
    ret = i2c_read_blocking(I2C_CH, device_slave_addr, readbuffer, 1, false);
    return ret;
}

/*! \brief apply REFRESH command to pac193x
 *         the accumulator data, accumulator count, Vbus,
 *         Vsense measurements are all refreshed
 *         and the accumulators are reset.
 *
 * \param none
 *
 * \returns none
 */
void pac193x_refresh(void) {
    uint8_t cmdbuffer[2];
    cmdbuffer[0] = PAC1934_REFRESH_CMD_ADDR;
    cmdbuffer[1] = 0x01;
    i2c_write_blocking(I2C_CH, PAC193X_SLAVE_ADDR, cmdbuffer, 2, false);
}

/*! \brief Initilize the PAC193x through the I2C bus
 *
 * \param none
 *
 * \returns -1: sensor is offline
 *          else: sensor is initialized
 */
int pac193x_init(void)
{

    uint8_t cmdbuffer[2];

    if(pac193x_onBus(PAC193X_SLAVE_ADDR)<0)
        return -1;

    cmdbuffer[0] = PAC1934_NEG_PWR_ADDR;
    cmdbuffer[1] = 0x00;
    i2c_write_blocking(I2C_CH, PAC193X_SLAVE_ADDR, cmdbuffer, 2, false);

    cmdbuffer[0] = PAC1934_CTRL_ADDR;
    cmdbuffer[1] = 0x02;
    i2c_write_blocking(I2C_CH, PAC193X_SLAVE_ADDR, cmdbuffer, 2, false);

    cmdbuffer[0] = PAC1934_CHANNEL_DIS_ADDR;
    cmdbuffer[1] = 0x00;
    i2c_write_blocking(I2C_CH, PAC193X_SLAVE_ADDR, cmdbuffer, 2, false);

    // configure the function of the SLOW PIN
    cmdbuffer[0] = PAC1934_SLOW_ADDR;
    cmdbuffer[1] = 0x14;
    i2c_write_blocking(I2C_CH, PAC193X_SLAVE_ADDR, cmdbuffer, 2, false);

    pac193x_refresh();
    sleep_ms(1);
}


/*! \brief Get the device information
 *
 * \param none
 *
 * \outputs product_id: pass the product id of pac193x
 *          manufacturer_id: pass the manufacturer id of pac193x
 *          revision_id: pass the revision id of pac193x
 *
 * \returns none
 */
void pac193x_getInfo(uint8_t *product_id, uint8_t *manufacturer_id, uint8_t *revision_id)
{
    uint8_t cmdbuffer[2];

    //0x58 for PAC1931
    //0x59 for PAC1932
    //0x5a for PAC1933
    //0x5b for PAC1934
    cmdbuffer[0] = PAC1934_PRODUCT_ID_ADDR;
    i2c_write_blocking(I2C_CH, PAC193X_SLAVE_ADDR, cmdbuffer, 1, false);
    i2c_read_blocking(I2C_CH, PAC193X_SLAVE_ADDR, product_id, 1, false);

    // should be always 0x5d
    cmdbuffer[0] = PAC1934_MANUFACTURER_ID_ADDR;
    i2c_write_blocking(I2C_CH, PAC193X_SLAVE_ADDR, cmdbuffer, 1, false);
    i2c_read_blocking(I2C_CH, PAC193X_SLAVE_ADDR, manufacturer_id, 1, false);

    // reversion id
    cmdbuffer[0] = PAC1934_REVISION_ID_ADDR;
    i2c_write_blocking(I2C_CH, PAC193X_SLAVE_ADDR, cmdbuffer, 1, false);
    i2c_read_blocking(I2C_CH, PAC193X_SLAVE_ADDR, revision_id, 1, false);
}





/*! \brief Print the device information
 *
 * \param none
 *
 * \outputs through the printf() in stdio.
 *
 * \returns none
 */
void pac193x_printInfo(void)
{
    uint8_t product_id, manufacture_id, reversion_id;
    pac193x_getInfo(&product_id, &manufacture_id, &reversion_id);
    printf("Product id: %2x\r\nManufacture id: %2x\r\nReversion id: %2x\r\n", product_id, manufacture_id, reversion_id);
}