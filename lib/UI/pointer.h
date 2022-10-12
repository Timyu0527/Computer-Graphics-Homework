#ifndef POINTER_H
#define POINTER_H

#include <GL/glut.h>

class Pointer{
    private:
        int x, y, in_rad, out_rad, side;
        GLUquadricObj *cir_ptr;
    public:
        static Pointer *mouse_ptr;
        Pointer();
        void setPos(int _x, int _y);
        void draw();
};

#endif