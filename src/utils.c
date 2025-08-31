#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>

#include "utils.h"

// Reusabe helper to write commands to i2c devices
void write_i2c_command(const struct i2c_dt_spec *device, char command)
{
    // I2C commands are prefixed with the 0x00 byte first
    uint8_t prepared_command[2] = {0x00, (uint8_t)command};

    int ret = i2c_write_dt(device, prepared_command, sizeof(prepared_command));

    if (ret != 0)
    {
        printk("Failed to write to I2C device address %x using command %x \n\r",
               device->addr, prepared_command[1]);
    }
}
