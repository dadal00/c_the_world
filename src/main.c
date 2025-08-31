#include <zephyr/kernel.h>

#include "display.h"
#include "utils.h"

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
