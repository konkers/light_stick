#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
source ${DIR}/common.sh

${CLI} compile --fqbn SparkFun:apollo3:amap3nano || exit 1
${CLI} upload --fqbn SparkFun:apollo3:amap3nano:svl_baud=115200,loader=sparkfun_svl --port=$1 || exit 1
