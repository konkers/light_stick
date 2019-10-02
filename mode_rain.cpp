#include "mode_rain.hpp"

static const color colors[] = {
    {0xff, 0x00, 0x00},
    {0x00, 0xff, 0x00},
    {0x00, 0x00, 0xff},
    {0xff, 0xff, 0x00},
    {0x00, 0xff, 0xff},
    {0xff, 0x00, 0xff},
};
static constexpr size_t n_colors = sizeof(colors) / sizeof(*colors);
static color randomColor()
{
    return colors[random(n_colors)];
}

static uint8_t mix_channel(uint8_t a, uint8_t b, float ratio)
{
    float a_f = (float)a;
    float b_f = (float)b;

    return (uint8_t)(a_f * (1 - ratio) + b_f * ratio);
}

static color mix_color(const color &a, const color &b, float ratio)
{
    color mixed = {
        mix_channel(a.r, b.r, ratio),
        mix_channel(a.g, b.g, ratio),
        mix_channel(a.b, b.b, ratio),
    };

    return mixed;
}

void ModeRain::init()
{
    for (size_t i = 0; i < 4; i++)
    {
        cur_color_[i] = randomColor();
    }
    next_active_ = 1;
    drop_velocity_ = .2f;
}

void ModeRain::step(Display &display)
{
    next_active_ -= 1;
    if (next_active_ > 0)
    {
        return;
    }
    else if (next_active_ == 0)
    {
        next_color_ = randomColor();
        drop_column_ = random(4);
        drop_position_ = leds_per_side_;
    }

    for (size_t side = 0; side < 4; side++)
    {
        for (size_t i = 0; i < leds_per_side_; i++)
        {
#if 1
            if (next_active_ <= 0 && side == drop_column_)
            {
                float distance = (float)i - drop_position_;
                if (distance > 0)
                {
                    display.set(side, i, next_color_);
                }
                else if (distance > -1)
                {
                    color mixed = mix_color(cur_color_[side], next_color_, 1 + distance);
                    display.set(side, i, mixed);
                }
                else
                {
                    display.set(side, i, cur_color_[side]);
                }
            }
            else
            {
                display.set(side, i, cur_color_[side]);
            }
#else
            display.set(side, i, cur_color_[side]);
#endif
        }
    }

    drop_position_ -= drop_velocity_;
    if (drop_position_ <= 0)
    {
        next_active_ = 10;
        cur_color_[drop_column_] = next_color_;
    }
}