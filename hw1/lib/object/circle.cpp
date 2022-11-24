#include "circle.h"
#include <iostream>

Circle::Circle() : side(600){};

void Circle::click(int _x, int _y){
    if(!press && !finish){
        press = 1;
        x = _x, y = _y;
    }
}

void Circle::drag(int _x, int _y){
    if(press){
        finish = 1;
        pos_x = _x, pos_y = _y;
    }
}

void Circle::draw(){
    if(finish){
        // std::cout << "circle draw" << std::endl;
        double offset_x = (x + pos_x) / 2;
        double offset_y = (y + pos_y) / 2;
        double a = fabs(1.0 * pos_x - x) / 2, b = fabs(1.0 * pos_y - y) / 2;
        double inc = -a / (side / 4);
        double tmp_x = a, tmp_y = 0, val;
        // std::cout << fill_mode << std::endl;
        if(fill_mode == GL_LINE) glLineWidth(width);
        glColor3fv(s_col.getColor());
        glPolygonMode(GL_FRONT, fill_mode);
        glBegin(GL_POLYGON);
            for(int i = 0; i < side; ++i){
                if(i == side / 2) inc = -inc;
                glVertex2f(tmp_x + offset_x, tmp_y + offset_y);
                tmp_x += inc;
                val = sqrt(a * a - tmp_x * tmp_x);
                if(isnan(val)) val = 0;
                if(i < side / 2) tmp_y = (b / a) * val; 
                else tmp_y = -(b / a) * val;
            }
        glEnd();
    }
}