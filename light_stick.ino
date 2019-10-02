// Copyright (c) 2019 Erik Gilling
// All rights reserved.
//
// Licensed under the MIT Licensed.  See toplevel LICENCE for details.

#include "ws2812b.hpp"
#include "pixbuf.hpp"

#define LEDS_PER_SIDE 6

Pixbuf<a3led::Ws2812b, LEDS_PER_SIDE> leds(SPI);

#define BUTTON 4
bool active = true;

static inline uint32_t hsv_inc(uint32_t index, int16_t inc)
{
  int32_t signed_index = index + inc;
  while (signed_index >= 0x600)
    signed_index -= 0x600;
  while (signed_index < 0)
    signed_index += 0x600;
  return signed_index;
}

static inline color hsv_pixel(uint32_t index)
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

void setup()
{
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
  leds.init();
  if (digitalRead(BUTTON) == 0)
  {
    active = false;
  }
}

uint32_t hsv_index;
#define INC_PATTERN 100
#define INC_FRAME -2
void loop()
{
  if (active)
  {
    auto cur_index = hsv_index;
    for (size_t i = 0; i < LEDS_PER_SIDE; i++)
    {
      auto color = hsv_pixel(cur_index);
      leds.set(0, i, color);
      leds.set(1, i, color);
      leds.set(2, i, color);
      leds.set(3, i, color);
      cur_index = hsv_inc(cur_index, INC_PATTERN);
    }
  }
#if 0
  auto color = hsv_pixel(cur_index);
  leds.set(3 * LEDS_PER_SIDE, color.r, color.g, color.b);
#endif
  hsv_index = hsv_inc(hsv_index, INC_FRAME);

  leds.send();
  delay(10);
}
