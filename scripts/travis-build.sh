#!/bin/bash

if [[ "$OSTYPE" == "linux-gnu" ]]; then
    PLATFORM="linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="mac"
elif [[ "$OSTYPE" == "cygwin" ]]; then
    PLATFORM="win"
elif [[ "$OSTYPE" == "msys" ]]; then
    PLATFORM="win"
elif [[ "$OSTYPE" == "win32" ]]; then
    PLATFORM="win"
else
    echo "Unknown platform $OSTYPE"
    exit 1
fi

CLI=./tools/${PLATFORM}/arduino-cli

${CLI} core update-index || exit 1
${CLI} lib update-index || exit 1
${CLI} core install SparkFun:apollo3 || exit 1
${CLI} compile --fqbn SparkFun:apollo3:amap3nano || exit 1
