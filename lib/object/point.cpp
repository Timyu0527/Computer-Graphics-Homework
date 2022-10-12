#include "point.h"

Point::Point(){};

void Point::click(int _x, int _y){
    if(!press && !finish){
        x = _x, y = _y;
        press = finish = 1;
    }
}

void Point::drag(int _x, int _y){}

void Point::draw(){
    if(press && finish){
        glPointSize(width);     /*  Define point size */
        glColor3fv(s_col.getColor());
        glBegin(GL_POINTS);     /*  Draw a point */
            glVertex2f(x, y);
        glEnd();
    }
}