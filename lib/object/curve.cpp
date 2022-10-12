#include "curve.h"
#include <iostream>

Curve::Curve(){};

void Curve::click(int _x, int _y){
    if(!press && !finish){
        press = 1;
        pnt.push_back({_x, _y});
    }
}

void Curve::drag(int _x, int _y){
    if(press){
        // std::cout << "Curve drag" << std::endl;
        finish = 1;
        pnt.push_back({_x, _y});
    }
}

void Curve::draw(){
    if(finish){
        glLineWidth(width);
        glColor3fv(s_col.getColor());
        for(int i = 1; i < pnt.size(); ++i){
            glBegin(GL_LINES);
                glVertex2i(pnt[i - 1].first, pnt[i - 1].second);
                glVertex2i(pnt[i].first, pnt[i].second);
            glEnd();
        }
    }
}