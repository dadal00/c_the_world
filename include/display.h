#include <zephyr/drivers/i2c.h>

#pragma once

extern const struct i2c_dt_spec display_i2c;

void init_display(const struct i2c_dt_spec *device);
