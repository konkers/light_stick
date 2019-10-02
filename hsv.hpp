#ifndef __hsv_hpp__
#define __hsv_hpp__
#include "pixbuf.hpp"

static constexpr uint32_t hsv_period = 0x600;

uint32_t hsv_inc(uint32_t index, int16_t inc);
color hsv_pixel(uint32_t index);

#endif // __hsv_hpp__
