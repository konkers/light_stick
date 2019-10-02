#ifndef __mode_rain_hpp__
#define __mode_rain_hpp__
#include "mode.hpp"

#include "Arduino.h"

class ModeRain : public Mode
{
public:
    ModeRain(size_t leds_per_side) : leds_per_side_(leds_per_side) { init(); }
    virtual void init() override;
    virtual void step(Display &display) override;

private:
    size_t leds_per_side_;
    int next_active_;
    color cur_color_[4];
    color next_color_;
    size_t drop_column_;
    float drop_position_;
    float drop_velocity_;

};
#endif // __mode_rain_hpp__
