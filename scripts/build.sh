#!/bin/bash
DIR=$(realpath $(dirname "${BASH_SOURCE[0]}"))
source ${DIR}/common.sh

${CLI} compile --fqbn SparkFun:apollo3:amap3nano "$@" || exit 1
