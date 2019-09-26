// Copyright (c) 2019 Erik Gilling
// All rights reserved.
//
// Licensed under the MIT Licensed.  See toplevel LICENCE for details.

#include <stdint.h>

#include "SPI.h"

#include "encoder.hpp"

namespace a3led
{
template <int NUM_LEDS>
class Ws2812b
{
public:
    Ws2812b(SPIClass &spi) : spi_(spi), encoder_(buf_, NUM_LEDS) {}

    void init()
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            encoder_.set(i, 0x00, 0x00, 0x00);
        }

        spi_.begin();
        spi_.beginTransaction(SPISettings(2400000, MSBFIRST, SPI_MODE0));

        // Need to set MOSIINV in order for MOSI to IDLE low.
        IOMn(0)->MSPICFG |= _VAL2FLD(IOM0_MSPICFG_MOSIINV, IOM0_MSPICFG_MOSIINV_INVERT);
    }

    void set(size_t led, uint8_t r, uint8_t g, uint8_t b)
    {
        encoder_.set(led, r, g, b);
    }

    void send()
    {
        spi_.transferOut(buf_, sizeof(buf_));
    }

private:
    SPIClass &spi_;
    // 3 bytes per channel, 3 channels per led, plus 1 byte of padding low
    // before bit stream.
    uint8_t buf_[NUM_LEDS * 9 + 1];
    Encoder encoder_;
};

} // namespace a3led