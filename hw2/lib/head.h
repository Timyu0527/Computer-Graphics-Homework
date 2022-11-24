#ifndef HEAD_H
#define HEAD_H

#include "baseObject.h"

class Head : public BaseObject{
    private:
    public:
        Head();
        Head(float _x, float _y, float _z, float _w, float _h, float _len, int red, int green, int blue);
        void draw();
};

#endif