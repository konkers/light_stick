#!/bin/bash
DIR=$(realpath $(dirname "${BASH_SOURCE[0]}"))
source ${DIR}/common.sh

${CLI} core update-index || exit 1
${CLI} lib update-index || exit 1
${CLI} core install SparkFun:apollo3 || exit 1
${CLI} compile --fqbn SparkFun:apollo3:amap3nano || exit 1
