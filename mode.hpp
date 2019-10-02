#ifndef __mode_hpp__
#define __mode_hpp__

class Mode
{
public:
    virtual void init() = 0;
    virtual void step() = 0;
};

#endif // __mode_hpp__
