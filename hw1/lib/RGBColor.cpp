#include "RGBColor.h"

RGBColor::RGBColor(){}

RGBColor::RGBColor(int _r, int _g, int _b){
    color[0] = 1.0 * _r / 255;
    color[1] = 1.0 * _g / 255;
    color[2] = 1.0 * _b / 255;
}

void RGBColor::setR(int _r){
    color[0] = 1.0 * _r / 255;
}

void RGBColor::setG(int _g){
    color[1] = 1.0 * _g / 255;
}

void RGBColor::setB(int _b){
    color[2] = 1.0 * _b / 255;
}

void RGBColor::setR(float _r){
    color[0] = _r;
}

void RGBColor::setG(float _g){
    color[1] = _g;
}

void RGBColor::setB(float _b){
    color[2] = _b;
}

void RGBColor::setAll(int _r, int _g, int _b){
    color[0] = 1.0 * _r / 255;
    color[1] = 1.0 * _g / 255;
    color[2] = 1.0 * _b / 255;
}

float RGBColor::getR(){
    return color[0];
}

float RGBColor::getG(){
    return color[1];
}

float RGBColor::getB(){
    return color[2];
}

float *RGBColor::getColor(){
    return color;
}
