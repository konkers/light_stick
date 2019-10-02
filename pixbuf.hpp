#ifndef __pixbuf_hpp__
#define __pixbuf_hpp__

#include <utility>

#include <stddef.h>
#include <stdint.h>

struct color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Display
{
public:
    virtual void set(unsigned int x, unsigned int y, const color &c) = 0;
    virtual const color &get(unsigned int x, unsigned int y) = 0;
};

static const size_t side_table[4]{
    0, 2, 3, 1};

// 0 = normal, 1 == reversed
static const size_t dir_table[4]{
    0, 1, 1, 0};

template <template <unsigned int> typename LED, unsigned int LEDS_PER_SIDE, unsigned int SIDES = 4, unsigned int LOG_GAIN = 2>
class Pixbuf : public Display
{
public:
    static constexpr unsigned int NUM_LEDS = LEDS_PER_SIDE * SIDES;

    // Forwards arguments to LED class constructor.
    template <typename... Args>
    Pixbuf(Args &&... args) : leds_(std::forward<Args>(args)...) {}

    void init()
    {
        leds_.init();
    }

    void send()
    {
        size_t i = 0;
        for (size_t x = 0; x < SIDES; x++)
        {
            for (size_t y = 0; y < LEDS_PER_SIDE; y++)
            {
                // TODO (side translation)
                auto side = side_table[x];
                auto c = buf_[side][y];
                auto strip_pos = dir_table[side] ? LEDS_PER_SIDE - y - 1 : y;
                leds_.set(x * LEDS_PER_SIDE + strip_pos,
                          c.r >> LOG_GAIN,
                          c.g >> LOG_GAIN,
                          c.b >> LOG_GAIN);
            }
        }
        leds_.send();
    }

    virtual void set(unsigned int x, unsigned int y, const color &c) override
    {
        // TODO: assert x, y limits... or runtime check... or something.
        buf_[x][y] = c;
    }

    virtual const color &get(unsigned int x, unsigned int y) override
    {
        // TODO: see set()
        return buf_[x][y];
    }

private:
    LED<NUM_LEDS> leds_;
    color buf_[SIDES][LEDS_PER_SIDE];
};
#endif // __pixbuf_hpp__
