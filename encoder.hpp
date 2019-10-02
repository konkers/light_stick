// Copyright (c) 2019 Erik Gilling
// All rights reserved.
//
// Licensed under the MIT Licensed.  See toplevel LICENCE for details.

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#define A3_WS2812_BUFFER(name, num_leds) uint8_t name[(num_leds)*9 + 1]

namespace a3led
{
class Encoder
{
public:
    Encoder(uint8_t *buffer, size_t num_leds) : buffer_(buffer), num_leds_(num_leds){};

    void set(size_t led, uint8_t r, uint8_t g, uint8_t b)
    {
        if (led >= num_leds_)
        {
            return;
        }
        set_channel(led * 9 + 1, g);
        set_channel(led * 9 + 4, r);
        set_channel(led * 9 + 7, b);
    }

    bool print_channel(size_t led, size_t channel, char line1[25], char line2[25])
    {
        if (led >= num_leds_ || channel >= 3)
        {
            line1[0] = '\0';
            line2[0] = '\0';
            return false;
        }

        size_t index = led * 9 + channel * 3;
        uint32_t val = buffer_[index] + (buffer_[index + 1] << 8) + (buffer_[index + 2] << 16);
        for (size_t b = 0; b < 24; b++)
        {
            if (val & (1 << b))
            {
                line1[b] = '_';
                line2[b] = ' ';
            }
            else
            {
                line1[b] = ' ';
                line2[b] = '_';
            }
        }

        line1[24] = '\0';
        line2[24] = '\0';
        return true;
    }

private:
    uint8_t *buffer_;
    size_t num_leds_;

    uint32_t encode(uint8_t val)
    {
        uint32_t encoded = 0;
        for (size_t i = 0; i < 8; i++)
        {
            encoded <<= 3;

            if (val & 0x80)
            {
                encoded |= 0x6; // high, high, low
            }
            else
            {
                encoded |= 0x4; // high, low, low
            }

            val <<= 1;
        }

        return encoded;
    }

    void set_channel(size_t index, uint8_t val)
    {
        uint32_t encoded = encode(val);
        // Assumes little endian.
        uint8_t *data = (uint8_t *)&encoded;
        buffer_[index] = data[2];
        buffer_[index + 1] = data[1];
        buffer_[index + 2] = data[0];
    }
};
} // namespace a3led