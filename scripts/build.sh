#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
source ${DIR}/common.sh

${CLI} compile --fqbn SparkFun:apollo3:amap3nano "$@" || exit 1
