#include "line.h"
#include <iostream>

Line::Line(){};

void Line::click(int _x, int _y){
    if(!press && !finish){
        press = 1;
        x = _x, y = _y;
    }
}

void Line::drag(int _x, int _y){
    if(press){
        // std::cout << "Line drag" << std::endl;
        finish = 1;
        pos_x = _x, pos_y = _y;
    }
}

void Line::draw(){
    if(press && finish){
        // std::cout << "test" << std::endl;
        glColor3fv(s_col.getColor());
        glLineWidth(width);     /* Define line width */
        glBegin(GL_LINES);    /* Draw the line */
            glVertex2f(x, y);
            glVertex2f(pos_x, pos_y);
        glEnd();
    }
}