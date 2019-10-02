
if [[ "$OSTYPE" == "linux-gnu" ]]; then
    PLATFORM="linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="mac"
elif [[ "$OSTYPE" == "cygwin" ]]; then
    PLATFORM="windows"
    EXT=".exe"
elif [[ "$OSTYPE" == "msys" ]]; then
    PLATFORM="windows"
    EXT=".exe"
elif [[ "$OSTYPE" == "win32" ]]; then
    PLATFORM="windows"
    EXT=".exe"
else
    echo "Unknown platform $OSTYPE"
    exit 1
fi

CLI=./tools/${PLATFORM}/arduino-cli${EXT}

