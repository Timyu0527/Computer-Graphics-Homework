#ifndef RGB_COLOR_H
#define RGB_COLOR_H

#include "my_def.h"

class RGBColor{
    private:
        float r, g, b;
    public:
        RGBColor();
        RGBColor(float _r, float _g, float _b);
        RGBColor(int _r, int _g, int _b);
        float getR();
        float getG();
        float getB();
        float *getRGB();
        void setR(float _r);
        void setG(float _g);
        void setB(float _b);
        void setR(int _r);
        void setG(int _g);
        void setB(int _b);
        void setColor(float _r, float _g, float _b);
        void setColor(RGBColor _color);
};

#endif