#pragma once

#define COMMAND_BYTE 0x00
#define DATA_BYTE 0x40

#define MAX_BUFFER_SIZE 16

int write_i2c_command(const struct i2c_dt_spec *device, char command);

int write_data_i2c_command(const struct i2c_dt_spec *device_spec, uint8_t *data, uint8_t width);

void handle_i2c_write_failure(const struct i2c_dt_spec *device_spec, char command);

void handle_i2c_write_data_failure(const struct i2c_dt_spec *device_spec);
