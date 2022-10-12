#include "object.h"

Object::Object(): width(2), press(0), finish(0), fill_mode(GL_FILL){};

int Object::getX(){
    return x;
}

int Object::getY(){
    return y;
}

bool Object::isFinish(){
    return finish;
}

void Object::setWidth(int _w){
    width = _w;
}

void Object::setFillMode(int _mode){
    fill_mode = _mode;
}

void Object::setColor(RGBColor _s_col){
    s_col = _s_col;
}