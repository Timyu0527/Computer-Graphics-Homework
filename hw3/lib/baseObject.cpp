#include "baseObject.h"

BaseObject::BaseObject(){
    x = 0;
    y = 0;
    z = 0;
    len = 0;
    width = 0;
    height = 0;
    is_picked = false;
}

BaseObject::BaseObject(float _x, float _y, float _z,
                       float _width, float _height, float _len){
    x = _x;
    y = _y;
    z = _z;
    len = _len;
    width = _width;
    height = _height;
    is_picked = false;
}

float BaseObject::getX(){
    return x;
}

float BaseObject::getY(){
    return y;
}

float BaseObject::getZ(){
    return z;
}

float BaseObject::getLen(){
    return len;
}

float BaseObject::getWidth(){
    return width;
}

float BaseObject::getHeight(){
    return height;
}

void BaseObject::setX(float _x){
    x = _x;
}

void BaseObject::setY(float _y){
    y = _y;
}

void BaseObject::setZ(float _z){
    z = _z;
}

void BaseObject::setLen(float _len){
    len = _len;
}

void BaseObject::setWidth(float _width){
    width = _width;
}

void BaseObject::setHeight(float _height){
    height = _height;
}

bool BaseObject::isPick(){
    return is_picked;
}

void BaseObject::picked(){
    is_picked = true;
}

void BaseObject::dropped(){
    is_picked = false;
}

