// Copyright (c) 2019 Erik Gilling
// All rights reserved.
//
// Licensed under the MIT Licensed.  See toplevel LICENCE for details.

#include "hsv.hpp"
#include "mode_linear_rainbow.hpp"
#include "mode_radial_rainbow.hpp"
#include "mode_rain.hpp"
#include "pixbuf.hpp"
#include "ws2812b.hpp"

#define LEDS_PER_SIDE 6

Pixbuf<a3led::Ws2812b, LEDS_PER_SIDE> leds(SPI);

ModeLinearRainbow linear_rainbow(LEDS_PER_SIDE, 100, -2);
ModeRadialRainbow radial_rainbow(LEDS_PER_SIDE, -2);
ModeRain rain(LEDS_PER_SIDE);

#define BUTTON 4
int button_down;
bool active = true;

uint32_t mode;
Mode *modes[] = {
    &linear_rainbow,
    &radial_rainbow,
    &rain,
};
static constexpr size_t n_modes = sizeof(modes) / sizeof(*modes);

void setup()
{
  randomSeed(analogRead(A0));
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.printf("hello");
  leds.init();
  if (digitalRead(BUTTON) == 0)
  {
    active = false;
  }
  linear_rainbow.init();
  radial_rainbow.init();
  rain.init();
}

#if 0
uint32_t hsv_index;
#define INC_PATTERN 100
#define INC_FRAME -2
#endif
void loop()
{
  if (digitalRead(BUTTON) == 0)
  {
    button_down++;
  }
  else
  {
    button_down = 0;
  }

  if (button_down == 3)
  {
    active = true;
    mode++;
    if (mode >= n_modes)
    {
      mode = 0;
    }

    modes[mode]->init();
  }

  if (active)
  {
    modes[mode]->step(leds);
  }

  leds.send();
  delay(10);
}
