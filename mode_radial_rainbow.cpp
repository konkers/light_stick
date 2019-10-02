#include "mode_radial_rainbow.hpp"

#include "hsv.hpp"

void ModeRadialRainbow::init()
{
  hsv_index_ = 0;
}

void ModeRadialRainbow::step(Display &display)
{
  auto cur_index = hsv_index_;
  for (size_t side = 0; side < 4; side++)
  {
    auto pix_index = cur_index;
    for (size_t i = 0; i < leds_per_side_; i++)
    {
      auto color = hsv_pixel(pix_index);
      display.set(side, i, color);
      pix_index = hsv_inc(pix_index, 0x100 * 4 / leds_per_side_);
    }
    cur_index = hsv_inc(cur_index, hsv_period / 4);
  }
#if 0
  auto color = hsv_pixel(cur_index);
  leds.set(3 * LEDS_PER_SIDE, color.r, color.g, color.b);
#endif
  hsv_index_ = hsv_inc(hsv_index_, inc_frame_);
}
