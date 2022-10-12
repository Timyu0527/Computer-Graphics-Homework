#ifndef CIRCLE_H
#define CIRCLE_H

// #include <cmath>
#include <math.h>
#include <vector>

#include <GL/glut.h>

#include "object.h"

class Circle : public Object{
    private:
        int pos_x, pos_y, side;
        std::vector<std::pair<int, int> > vertex;
    public:
        Circle();
        void click(int _x, int _y);
        void drag(int _x, int _y);
        void draw();
};

#endif