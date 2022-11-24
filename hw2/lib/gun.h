#ifndef GUN_H
#define GUN_H

#include "my_def.h"
#include "baseObject.h"

class Gun : public BaseObject{
    private:
        float x1, y1, z1;
        bool is_shoot;
        GLUquadricObj *cylinder;
    public:
        Gun();
        Gun(float _x, float _y, float _z, int red, int green, int blue);
        void use(void (*func)(void));
        void draw();
};

#endif