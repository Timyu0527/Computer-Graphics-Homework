#ifndef POINT_H
#define POINT_H

#include <GL/glut.h>

#include "object.h"

class Point : public Object{
    public:
        Point();
        void click(int _x, int _y);
        void drag(int _x, int _y);
        void draw();
};

#endif