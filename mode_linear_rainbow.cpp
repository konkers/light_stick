#include "mode_linear_rainbow.hpp"

#include "hsv.hpp"

void ModeLinearRainbow::init()
{
  hsv_index_ = 0;
}

void ModeLinearRainbow::step(Display &display)
{
  auto cur_index = hsv_index_;
  for (size_t i = 0; i < leds_per_side_; i++)
  {
    auto color = hsv_pixel(cur_index);
    display.set(0, i, color);
    display.set(1, i, color);
    display.set(2, i, color);
    display.set(3, i, color);
    cur_index = hsv_inc(cur_index, inc_pattern_);
  }
#if 0
  auto color = hsv_pixel(cur_index);
  leds.set(3 * LEDS_PER_SIDE, color.r, color.g, color.b);
#endif
  hsv_index_ = hsv_inc(hsv_index_, inc_frame_);
}
