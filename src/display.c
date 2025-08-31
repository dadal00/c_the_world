#include <zephyr/kernel.h>

#include "display.h"
#include "utils.h"

// Defining an I2C node named "oled"
// - "oled" must be mapped in the overlay or device tree
#define I2C0_NODE DT_NODELABEL(oled)

// Initializing the node we just defined
const struct i2c_dt_spec display_i2c = I2C_DT_SPEC_GET(I2C0_NODE);

// Sequence of commands for startup of display
static const uint8_t init_commands[] = {
    // Display off
    0xAE,
    // Display clock
    0xD5,
    // Display ratio
    0x80,
    // Multiplex
    0xA8, 0x1F,
    // Display offset
    0xD3, 0x00,
    // Dtart line
    0x40,
    // Chargepump
    0x8D,
    // Internal VCC
    0x14,
    // Memory Mode
    0x20, 0x00,
    // Horizontal Axis + Vertical Axis
    0xA0, 0xC0,
    // COM pins
    0xDA, 0x02,
    // Contrast
    0x81, 0x8F,
    // Precharge
    0xD9,
    // Internal VCC
    0xF1,
    // COM detect
    0xDB, 0x40,
    // Display all on, resume
    0xA4,
    // Normal display
    0xA6,
    // Display on
    0xAF};

// Starts up the display
void init_display(const struct i2c_dt_spec *device)
{
    for (size_t i = 0; i < sizeof(init_commands); i++)
    {
        write_i2c_command(device, init_commands[i]);
    }
}
