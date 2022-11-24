#include "gun.h"

Gun::Gun() : BaseObject(0, 0, 0, 0, 0, 0), is_shoot(0){
    color = RGBColor(0, 0, 0);
    cylinder = nullptr;
}

Gun::Gun(float _x, float _y, float _z,
         int red, int green, int blue) :
         BaseObject(_x, _y, _z, 0, 0, 0), is_shoot(0){
    width = 0.25;
    height = 0.5;
    len = 0.25;
    x1 = width + width / 4;
    y1 = height / 2;
    z1 = 0;
    cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    color = RGBColor(red, green, blue);
}

void Gun::use(void (*func)(void)){
    std::cout << "Gun is used" << std::endl;
    float tmp = x1;
    is_shoot = 1;
    for(float i = x1; i > tmp - 0.5; i -= 0.05){
        x1 = i;
        func();
    }
    is_shoot = 0;
    for(float i = x1; i < tmp; i += 0.05){
        x1 = i;
        func();
    }
    x1 = tmp;
    func();
}

void Gun::draw(){
    glPushMatrix();
    glTranslatef(x, y, z);
    glPushMatrix();
    glColor3fv(color.getRGB());
    glRotatef(-15.0, 0.0, 0.0, 1.0);
    glScalef(width, height, len);

    glutSolidCube(1);
    glPopMatrix();

    if(is_shoot){
        glPushMatrix();
        glTranslatef(height + 4 * width, y1, z);
        glColor3f(1.0, 0.5, 0.0);
        glutSolidSphere(width, 20, 20);
        glPopMatrix();
    }

    glPushMatrix();
    glColor3fv(color.getRGB());
    glTranslatef(x1, y1, z1);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(width, 2 * height, len);

    glutSolidCube(1);
    glPopMatrix();
    glColor3f(color.getR() - 5, color.getG() - 5, color.getB() - 5);
    glTranslatef(0, y1, -z);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    gluCylinder(cylinder, width / 4, len / 4, /* radius of top and bottom circle */
        2 * height,              /* height of the cylinder */
        12,               /* use 12-side polygon approximating circle*/
        3);               /* Divide it into 3 sections */
    glPopMatrix();
}