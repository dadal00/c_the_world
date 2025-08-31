#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>

#define I2C0_NODE DT_NODELABEL(oled)

static const struct i2c_dt_spec display_i2c = I2C_DT_SPEC_GET(I2C0_NODE);

// Reusabe helper to write commands to i2c devices
void write_i2c_command(const struct i2c_dt_spec *device, char command)
{
	uint8_t prepared_command[2] = {0x00, (uint8_t)command};

	int ret = i2c_write_dt(device, prepared_command, sizeof(prepared_command));

	if (ret != 0)
	{
		printk("Failed to write to I2C device address %x using command %x \n\r",
			   device->addr, prepared_command[1]);
	}
}

// Starts up the display
void init_display(const struct i2c_dt_spec *device)
{
	// Sequence of commands for startup of display
	uint8_t commands[] = {
		0xAE, 0xD5, 0x80, 0xA8, 0x3F,
		0xD3, 0x00, 0x40, 0x8D, 0x14,
		0x20, 0x00, 0xA0, 0xC8,
		0xDA, 0x12, 0x81, 0xCF,
		0xD9, 0xF1, 0xDB, 0x40,
		0xA4, 0xA6, 0xAF};

	for (size_t i = 0; i < sizeof(commands); i++)
	{
		write_i2c_command(device, commands[i]);
	}
}

int main(void)
{
	if (!device_is_ready(display_i2c.bus))
	{
		printk("I2C bus %s is not ready!\n\r", display_i2c.bus->name);
		return 0;
	}

	init_display(&display_i2c);

	return 0;
}
