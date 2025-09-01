#include <zephyr/drivers/i2c.h>

#pragma once

// Defining an I2C node named "oled"
// - "oled" must be mapped in the overlay or device tree
#define I2C0_NODE DT_NODELABEL(oled)

// Init commands
// "oled" dimensions
#define OLED_PAGES 8
#define OLED_HEIGHT 64
#define OLED_WIDTH 128
// this = OLED_WIDTH / 8
#define OLED_BYTES_PER_ROW 16

// "oled" commands
#define DISPLAY_OFF 0xAE
#define DISPLAY_ON 0xAF

#define CLOCK 0xD5
#define CLOCK_DEFAULT 0x80

#define MULTIPLEX 0xA8
#define MULTIPLEX_VALUE 0x3F

#define DISPLAY_OFFSET 0xD3
#define DISPLAY_OFFSET_DEFAULT 0x00

#define START_LINE 0x40

#define CHARGE_PUMP 0x8D
#define CHARGE_PUMP_ON 0x14

#define MEMORY_WRITE_MODE 0x20
// 0x00 is go right along the row then go next at the end
#define MEMORY_WRITE_BY_PAGE 0x00

// 0xA1 start left
// 0xA0 start right
#define HORIZONTAL_ORIENTATION 0xA1
// 0xC8 start top
// 0xC8 start bottom
#define VERTICAL_ORIENTATION 0xC8

#define COM_PINS 0xDA
#define COM_PINS_VALUE 0x12

#define BRIGHTNESS 0x81
// 0x00 - 0xFF
#define BRIGHTNESS_LEVEL 0xCF

#define CONTRAST_POWER_EFFICIENCY 0xD9
#define CONTRAST_POWER_EFFICIENCY_VALUE 0xF1

#define STABILITY_POWER_CONSUMPTION 0xDB
#define STABILITY_POWER_CONSUMPTION_VALUE 0x40

#define DISPLAY_RAM 0xA4
#define DISPLAY_ALL_ON 0xA5

#define NORMAL_DISPLAY 0xA6
// Just means instead of 0 off, 1 on -> 0 on, 1 off
#define INVERSE_DISPLAY 0xA7

// Flushing
#define FLUSH_BYTES 16

extern const struct i2c_dt_spec display_i2c;

void init_display(const struct i2c_dt_spec *device_spec);

// int write_pixel(const uint8_t page, const uint8_t y, const uint8_t value);

void draw_bitmap(const uint8_t *bitmap, uint8_t width, uint8_t height, uint8_t bytes_per_row);

void flush_buffer(const struct i2c_dt_spec *device_spec);
