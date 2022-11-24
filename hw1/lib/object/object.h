#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glut.h>

#include "../RGBColor.h"

class Object{
    protected:
        int x, y, width, fill_mode;
        RGBColor s_col;
        bool press, finish;
    public:
        Object();
        int getX();
        int getY();
        bool isFinish();
        void setFillMode(int _mode);
        void setColor(RGBColor _s_col);
        void setWidth(int _w);
        virtual void addChar(char _ch){};
        virtual void click(int _x, int _y) = 0;
        virtual void drag(int _x, int _y) = 0;
        virtual void draw() = 0;
};

#endif