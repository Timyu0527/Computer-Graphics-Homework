#ifndef BODY_H
#define BODY_H
// #include "my_def.h"
#include "baseObject.h"

class Body : public BaseObject{
    private: 
        float angle;
    public:
        Body();
        Body(float _x, float _y, float _z, float _len, float _width, float _height, int red, int green, int blue);
        void turn(float ang);
        void move(int dir);
        void draw();
};

#endif