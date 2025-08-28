# Blinky

**Sample:** `blinky`  
**Relevant API:** `gpio_interface`

Blink an LED forever using the GPIO API.

## Overview

The Blinky sample blinks an LED forever using the [GPIO API](https://docs.zephyrproject.org/latest/reference/peripherals/gpio.html).

The source code shows how to:

1. Get a pin specification from the [devicetree](https://docs.zephyrproject.org/latest/guides/dts/index.html) as a `gpio_dt_spec`.
2. Configure the GPIO pin as an output.
3. Toggle the pin forever.

See the [`pwm-blinky`](https://docs.zephyrproject.org/latest/samples/basic/pwm-blinky.html) sample for a similar example that uses the PWM API instead.

## Requirements

Your board must:

1. Have an LED connected via a GPIO pin (these are called "User LEDs" on many of Zephyr's [boards](https://docs.zephyrproject.org/latest/boards/index.html)).
2. Have the LED configured using the `led0` devicetree alias.

## Building and Running

Build and flash Blinky as follows, changing `reel_board` for your board:

```bash
west build -b reel_board samples/basic/blinky
west flash
```
