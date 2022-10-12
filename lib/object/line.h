#ifndef LINE_H
#define LINE_H

#include <GL/glut.h>

#include "object.h"

class Line : public Object{
    private:
        int pos_x, pos_y;
    public:
        Line();
        void click(int _x, int _y);
        void drag(int _x, int _y);
        void draw();
};

#endif