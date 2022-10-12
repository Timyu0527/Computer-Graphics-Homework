#include "poly.h"
#include <iostream>

Poly::Poly() : Object(){};

void Poly::click(int _x, int _y){
    // std::cout << "click" << std::endl;
    if(vertex.empty()){
        x = _x, y = _y;
        vertex.push_back({x, y});
    }
    else{
        x = _x, y = _y;
        if(abs(vertex[0].first - _x) + abs(vertex[0].second - _y) < 10){
            finish = 1;
        }
        else{
            pos_x = x, pos_y = y;
            vertex.push_back({x, y});
        }
    }
}

void Poly::drag(int _x, int _y){
    if(!vertex.empty()) x = _x, y = _y;
}

void Poly::draw(){
    glColor3fv(s_col.getColor());
    if(finish){
        // std::cout << "Polygon fill mode: " << fill_mode << std::endl;
        // std::cout << "Line fill mode: " << GL_LINE << std::endl;
        if(fill_mode == GL_LINE){
            glLineWidth(width);
            glBegin(GL_LINE_LOOP);
        }
        else{
            glPolygonMode(GL_FRONT, fill_mode);
            glBegin(GL_POLYGON);
        }
        for(std::pair<int, int> pnt : vertex){
            glVertex2i(pnt.first, pnt.second);
        }
        glEnd();
    }
    else{
        if(!vertex.empty()){
        int side = vertex.size();
            for(int i = 2; i <= side; ++i){
                glLineWidth(width);
                glBegin(GL_LINES);
                    glVertex2i(vertex[i - 2].first, vertex[i - 2].second);
                    glVertex2i(vertex[i - 1].first, vertex[i - 1].second);
                glEnd();
            }
            glColor3fv(s_col.getColor());
            glLineWidth(width);
            glBegin(GL_LINES);
                glVertex2i(vertex.back().first, vertex.back().second);
                glVertex2i(x, y);
            glEnd();
        }
    }
}