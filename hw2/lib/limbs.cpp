#include "limbs.h"

Limbs::Limbs() : BaseObject(), joint(nullptr){
    color = RGBColor(0, 0, 0);
    memset(ang, 0, sizeof(ang));
}

Limbs::Limbs(float  _x, float  _y, float  _z,
              float  _width, float  _height, float  _len,
              int red, int green, int blue):
              BaseObject(_x, _y, _z, _width, _height, _len),
              joint(new Joint(0, -height / 4 - _len / 2, 0, _len/2, 200, 200, 200)){
    color = RGBColor(red, green, blue);
    memset(ang, 0, sizeof(ang));
}

void Limbs::rotateX(float ang1, float ang2){
    ang[0][0] = ang1;
    ang[0][1] = ang2;
}

void Limbs::rotateY(float ang1, float ang2){
    ang[1][0] = ang1;
    ang[1][1] = ang2;
}

void Limbs::rotateZ(float ang1, float ang2){
    ang[2][0] = ang1;
    ang[2][1] = ang2;
}

void Limbs::draw(){
    // static int ang = 0;
    glTranslatef(x, y, z);
    glTranslatef(0, height / 4, 0);
    // std::cout << ang << std::endl;
    // if(ang <= 90) glRotatef(ang++, 0.0, 0.0, 1.0);
    glRotatef(ang[0][0], 1.0, 0.0, 0.0);
    glRotatef(ang[1][0], 0.0, 1.0, 0.0);
    glRotatef(ang[2][0], 0.0, 0.0, 1.0);
    // glRotatef(90, 0.0, 0.0, 1.0);
    glTranslatef(0, -height / 4, 0);
    glScalef(width, height / 2, len);
    glColor3fv(color.getRGB());

    glutSolidCube(1);

    glScalef(1 / width, 2 / height, 1 / len);

    glPushMatrix();

    joint->draw();

    glPushMatrix();
    // if(ang <= 90) glRotatef(ang++, 0.0, 0.0, 1.0);
    glRotatef(ang[0][1], 1.0, 0.0, 0.0);
    glRotatef(ang[1][1], 0.0, 1.0, 0.0);
    glRotatef(ang[2][1], 0.0, 0.0, 1.0);
    glTranslatef(0, -height / 4 - len / 2, 0);
    glScalef(width, height / 2, len);
    glColor3fv(color.getRGB());

    glutSolidCube(1);

    glPopMatrix();
    glPopMatrix();
}