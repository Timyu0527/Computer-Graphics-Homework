#include "entry.h"
#include <iostream>

Entry::Entry(int _x, int _y, int _w, int _h, const char *_text):
    x(_x),
    y(_y),
    width(_w),
    height(_h),
    margin(10),
    text(_text){
    i_col = RGBColor(0, 0, 0), h_col = RGBColor(0, 0, 0);
    a_col = RGBColor(0, 0, 0), s_col = RGBColor(0, 0, 0);
}

int Entry::getX(){
    return x;
}

int Entry::getY(){
    return y;
}

int Entry::getWidth(){
    return width;
}

int Entry::getHeight(){
    return height;
}

void Entry::resize(int _w, int _h){
    width = _w;
    height = _h;
}

void Entry::setX(int _x){
    x = _x;
}

void Entry::setY(int _y){
    y = _y;
}

void Entry::reshape(int _x, int _y, int _w, int _h){
    x = _x;
    y = _y;
    width = _w;
    height = _h;
}

void Entry::setAlign(int _align){
    align = _align;
}

void Entry::setColor(int r, int g, int b){
    s_col = RGBColor(r, g, b);
}

void Entry::setColor(RGBColor color){
    s_col = color;
}

void Entry::drag(int _x, int _y){}