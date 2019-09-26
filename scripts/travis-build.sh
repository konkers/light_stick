#!/bin/bash
./tools/linux/arduino-cli core update-index || exit 1
./tools/linux/arduino-cli lib update-index || exit 1
./tools/linux/arduino-cli core install SparkFun:apollo3 || exit 1
./tools/linux/arduino-cli compile --fqbn SparkFun:apollo3:amap3nano || exit 1
