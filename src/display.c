#include <zephyr/kernel.h>

#include "display.h"
#include "utils.h"
#include "image.h"

// Initializing the node we just defined
const struct i2c_dt_spec display_i2c = I2C_DT_SPEC_GET(I2C0_NODE);

// Initializing the display buffer
// - width * height / 8bits per byte
static uint8_t display_buffer[OLED_HEIGHT * OLED_WIDTH / 8];

// Sequence of commands for startup of display
static const uint8_t init_commands[] = {
    DISPLAY_OFF,
    CLOCK, CLOCK_DEFAULT,
    MULTIPLEX, MULTIPLEX_VALUE,
    DISPLAY_OFFSET, DISPLAY_OFFSET_DEFAULT,
    START_LINE,
    CHARGE_PUMP, CHARGE_PUMP_ON,
    MEMORY_WRITE_MODE, MEMORY_WRITE_BY_PAGE,
    HORIZONTAL_ORIENTATION, VERTICAL_ORIENTATION,
    COM_PINS, COM_PINS_VALUE,
    BRIGHTNESS, BRIGHTNESS_LEVEL,
    CONTRAST_POWER_EFFICIENCY, CONTRAST_POWER_EFFICIENCY_VALUE,
    STABILITY_POWER_CONSUMPTION, STABILITY_POWER_CONSUMPTION_VALUE,
    DISPLAY_RAM,
    NORMAL_DISPLAY,
    DISPLAY_ON};

// Starts up the display
void init_display(const struct i2c_dt_spec *device_spec)
{
    // Ensure power stablized
    k_sleep(K_MSEC(1000));

    for (size_t i = 0; i < sizeof(init_commands); i++)
    {
        if (write_i2c_command(device_spec, init_commands[i]))
        {
            handle_i2c_write_failure(device_spec, init_commands[i]);
            return;
        }
    }

    memset(display_buffer, 0, sizeof(display_buffer));

    draw_bitmap(raw_background, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, BACKGROUND_BYTES_PER_ROW);

    flush_buffer(device_spec);
}

void flush_buffer(const struct i2c_dt_spec *device_spec)
{
    // Current code skips last partial chunk unless display_buffer is divisible by FLUSH_BYTES
    // In this case 1024 / 16 = 64
    for (uint8_t i = 0; i < sizeof(display_buffer) / FLUSH_BYTES; i++)
    {
        if (write_data_i2c_command(device_spec, &display_buffer[i * FLUSH_BYTES], FLUSH_BYTES))
        {
            handle_i2c_write_data_failure(device_spec);
            return;
        }
    }
}

// int write_pixel(const uint8_t row, const uint8_t col, const uint8_t value)
// {
//     uint8_t page = row / 8;
//     uint8_t bit = (1 << (row % 8));

//     if (value)
//         display_buffer[page][col] |= bit;
//     else
//         display_buffer[page][col] &= ~bit;
// }

void draw_bitmap(const uint8_t *bitmap, uint8_t width, uint8_t height, uint8_t bytes_per_row)
{
    if (width > OLED_WIDTH)
    {
        printk("Failed to draw bitmap onto OLED!");
        return;
    }

    for (uint8_t page = 0; page < OLED_PAGES; page++)
    {
        for (uint8_t col = 0; col < width; col++)
        {
            uint8_t byte = 0;

            // Construct vertical byte across 8 rows for the same column
            // - Assuming bitmap is ROW major
            // - Must convert to COLUMN major fit for our OLED
            for (uint8_t bit = 0; bit < 8; bit++)
            {
                uint8_t row = page * 8 + bit;
                uint8_t bitmap_byte = bitmap[row * bytes_per_row + (col / 8)];
                uint8_t bitmap_bit = (bitmap_byte >> (7 - (col % 8))) & 0x1;

                byte |= (bitmap_bit << bit);
            }

            display_buffer[page * OLED_WIDTH + col] = byte;
        }
    }
}
