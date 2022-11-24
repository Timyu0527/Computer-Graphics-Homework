#ifndef LIMBS_H 
#define LIMBS_H 

// #include "my_def.h"
#include "joint.h"

class Limbs : public BaseObject{
    private:
        float ang[3][2];
        Joint *joint;
    public:
        Limbs();
        Limbs(float _x, float _y, float _z, float _len, float _width, float _height, int red, int green, int blue);
        void rotateX(float ang1, float ang2);
        void rotateY(float ang1, float ang2);
        void rotateZ(float ang1, float ang2);
        void draw();
};

#endif