# C The World

Art Source: https://www.moonbench.xyz/projects/1-bit-oled-art-gallery/

export ZEPHYR_BASE=~/zephyrproject/zephyr

source ~/zephyrproject/.venv/bin/activate

west build -p always -b nucleo_f446re

west flash
