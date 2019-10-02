#ifndef __mode_radial_rainbow_hpp__
#define __mode_radial_rainbow_hpp__

#include <stdint.h>

#include "mode.hpp"

class ModeRadialRainbow : public Mode
{
public:
    ModeRadialRainbow(size_t leds_per_side, int32_t inc_frame)
        : hsv_index_(0),
          leds_per_side_(leds_per_side),
          inc_frame_(inc_frame)
    {
    }
    virtual void init() override;
    virtual void step(Display &display) override;

private:
    uint32_t hsv_index_;
    size_t leds_per_side_;
    int32_t inc_frame_;
};
#endif // __mode_radial_rainbow_hpp__