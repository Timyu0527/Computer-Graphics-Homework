#include "RGBColor.h"

RGBColor::RGBColor(){
    r = 0;
    g = 0;
    b = 0;
}

RGBColor::RGBColor(float _r, float _g, float _b){
    r = _r;
    g = _g;
    b = _b;
}

RGBColor::RGBColor(int _r, int _g, int _b){
    r = 1.0 * _r / 255.0;
    g = 1.0 * _g / 255.0;
    b = 1.0 * _b / 255.0;
}

float RGBColor::getR(){
    return r;
}

float RGBColor::getG(){
    return g;
}

float RGBColor::getB(){
    return b;
}

float *RGBColor::getRGB(){
    float *rgb = new float[3];
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
    return rgb;
}

void RGBColor::setR(float _r){
    r = _r;
}

void RGBColor::setG(float _g){
    g = _g;
}

void RGBColor::setB(float _b){
    b = _b;
}

void RGBColor::setR(int _r){
    r = 1.0 * _r / 255.0;
}

void RGBColor::setG(int _g){
    g = 1.0 * _g / 255.0;
}

void RGBColor::setB(int _b){
    b = 1.0 * _b / 255.0;
}

void RGBColor::setColor(float _r, float _g, float _b){
    r = _r;
    g = _g;
    b = _b;
}

void RGBColor::setColor(RGBColor _color){
    r = _color.getR();
    g = _color.getG();
    b = _color.getB();
}
