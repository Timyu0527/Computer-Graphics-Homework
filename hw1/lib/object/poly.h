#ifndef POLYGON_H
#define POLYGON_H

#include <cmath>
#include <vector>

#include <GL/glut.h>

#include "object.h"


class Poly : public Object{
    private:
        int pos_x, pos_y;
        std::vector<std::pair<int, int> > vertex;
    public:
        Poly();
        void click(int _x, int _y);
        void drag(int _x, int _y); 
        void draw();
};

#endif