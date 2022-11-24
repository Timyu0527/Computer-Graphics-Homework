#include "body.h"

Body::Body() : BaseObject(0, 0, 0, 0, 0, 0), angle(0){
    color.setColor(0, 0, 0);
}

Body::Body(float _x, float _y, float _z,
           float _width, float _height, float _len,
           int red, int green, int blue):
           BaseObject(_x, _y, _z, _width, _height, _len),
           angle(0){
    color = RGBColor(red, green, blue);
}

void Body::turn(float ang){
    angle = ang;
}

void Body::move(int dir){
    float tmp = 1.0;
    if(dir == MOVE_DIRECTION::FORWARD) tmp = 1.0;
    if(dir == MOVE_DIRECTION::BACKWARD) tmp = -1.0;
    x += tmp * ROBOT_STEP * cos(-angle * PI / 180);
    z += tmp * ROBOT_STEP * sin(-angle * PI / 180);
}

void Body::draw(){
    glColor3fv(color.getRGB());
    glTranslatef(x, y, z);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glScalef(width, height, len);     /* Scale up the axes by 6 times */

    glutSolidCube(1);

    glScalef(1 / width, 1 / height, 1 / len);     /* Scale up the axes by 6 times */
}