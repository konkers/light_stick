// Copyright (c) 2019 Erik Gilling
// All rights reserved.
//
// Licensed under the MIT Licensed.  See toplevel LICENCE for details.

#include "hsv.hpp"
#include "pixbuf.hpp"
#include "ws2812b.hpp"

#define LEDS_PER_SIDE 6

Pixbuf<a3led::Ws2812b, LEDS_PER_SIDE> leds(SPI);

#define BUTTON 4
bool active = true;

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
