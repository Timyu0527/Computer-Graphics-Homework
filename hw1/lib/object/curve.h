#ifndef CURVE_H
#define CURVE_H

#include <vector>

#include <GL/glut.h>

#include "object.h"

class Curve : public Object{
    private:
        std::vector<std::pair<int, int> > pnt;
    public:
        Curve();
        void click(int _x, int _y);
        void drag(int _x, int _y);
        void draw();
};

#endif