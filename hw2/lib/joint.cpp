#include "joint.h"

Joint::Joint() : BaseObject(0, 0, 0, 0, 0, 0){
    color = RGBColor(0, 0, 0);
}

Joint::Joint(float _x, float _y, float _z,
             float _radius,
             int red, int green, int blue):
             BaseObject(_x, _y, _z, 0, 0, 0),
             radius(_radius){
    color = RGBColor(red, green, blue);
}

void Joint::setRadius(float _radius){
    radius = _radius;
}

float Joint::getRadius(){
    return radius;
}

void Joint::draw(){
    glTranslatef(x, y, z);
    glColor3fv(color.getRGB());

    glutSolidSphere(radius, 20, 20);
}

