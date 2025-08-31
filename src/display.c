#include <zephyr/kernel.h>

#include "display.h"
#include "utils.h"

// Initializing the node we just defined
const struct i2c_dt_spec display_i2c = I2C_DT_SPEC_GET(I2C0_NODE);

// Initializing the display buffer
static uint8_t display_buffer[PAGES][WIDTH];

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
void init_display(const struct i2c_dt_spec *device)
{
    // Ensure power stablized
    k_sleep(K_MSEC(1000));

    for (size_t i = 0; i < sizeof(init_commands); i++)
    {
        write_i2c_command(device, init_commands[i]);
    }

    // Testing if all can be turned on
    // - make sure to turn back to RAM only
    write_i2c_command(device, DISPLAY_ALL_ON);

    // for (uint8_t page = 0; page < PAGES; page++)
    // {
    //     for (uint8_t col = 0; col < WIDTH; col++)
    //     {
    //         // all 8 pixels VERTICAL are now on cause 11111111
    //         display_buffer[page][col] = 0xFF;
    //     }
    // }
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

// void draw_bitmap(const uint8_t *bitmap, uint8_t width, uint8_t height)
// {
//     for (int page = 0; page < height / 8; page++)
//     {
//         for (int col = 0; col < width; col++)
//         {
//             display_buffer[page][col] = bitmap[page * width + col];
//         }
//     }
// }
