#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>

#include "utils.h"

static uint8_t buffer[MAX_BUFFER_SIZE + 1];

// Reusabe helper to write commands to i2c devices
int write_i2c_command(const struct i2c_dt_spec *device_spec, char command)
{
    // I2C commands are prefixed with the 0x00 byte first
    uint8_t prepared_command[2] = {COMMAND_BYTE, (uint8_t)command};

    // Return back wehther or not it failed
    return i2c_write_dt(device_spec, prepared_command, sizeof(prepared_command));
}

// Reusabe helper to write data to i2c devices
int write_data_i2c_command(const struct i2c_dt_spec *device_spec, uint8_t *data, uint8_t width)
{
    if (width > MAX_BUFFER_SIZE)
        return 1;

    // I2C data writes are prefixed with the 0x40 byte first
    buffer[0] = DATA_BYTE;

    memcpy(&buffer[1], data, width);

    // Return back wehther or not it failed
    return i2c_write_dt(device_spec, buffer, width + 1);
}

void handle_i2c_write_failure(const struct i2c_dt_spec *device_spec, char command)
{
    printk("Failed to write to I2C device address %x using command %x \n\r",
           device_spec->addr, command);
}

void handle_i2c_write_data_failure(const struct i2c_dt_spec *device_spec)
{
    printk("Failed to write data to I2C device address %x \n\r",
           device_spec->addr);
}
