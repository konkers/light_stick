#ifndef __mode_slow_rainbow_hpp__
#define __mode_slow_rainbow_hpp__

#include <stdint.h>

#include "mode.hpp"

class ModeSlowRainbow : public Mode
{
public:
    virtual void init() override;
    virtual void step() override;

private:
    uint32_t hsv_index_;
};
#endif // __mode_slow_rainbow_hpp__