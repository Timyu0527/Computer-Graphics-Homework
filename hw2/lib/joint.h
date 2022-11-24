#ifndef JOINT_H
#define JOINT_H

#include "my_def.h"
#include "baseObject.h"

class Joint : public BaseObject{
    private:
        float radius;
    public:
        Joint();
        Joint(float _x, float _y, float _z, float _radius, int red, int green, int blue);
        void setRadius(float _radius);
        float getRadius();
        void draw();
};

#endif