#ifndef BLOCK_H
#define BLOCK_H

#include "my_def.h"
#include "baseObject.h"
#include "robot.h"

class Block : public BaseObject{
    public:
        Block();
        Block(float _x, float _y, float _z, float _w, float _h, float _len, int red, int green, int blue);
        bool isCollide(Robot *robot);
        void draw();
};

#endif