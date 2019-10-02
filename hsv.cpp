#include "hsv.hpp"

uint32_t hsv_inc(uint32_t index, int16_t inc)
{
    int32_t signed_index = index + inc;
    while (signed_index >= 0x600)
        signed_index -= 0x600;
    while (signed_index < 0)
        signed_index += 0x600;
    return signed_index;
}

color hsv_pixel(uint32_t index)
{
    uint8_t pos = index & 0xff;
    uint8_t neg = 0xff - (index & 0xff);
    uint8_t phase = (index >> 8) & 0x7;

    switch (phase)
    {
    case 0:
        return color{pos, 0x00, 0xff};

    case 1:
        return color{0xff, 0x00, neg};

    case 2:
        return color{0xff, pos, 0x00};

    case 3:
        return color{neg, 0xff, 0x00};

    case 4:
        return color{0x00, 0xff, pos};

    case 5:
    default:
        return color{0x00, neg, 0xff};
    }
}
