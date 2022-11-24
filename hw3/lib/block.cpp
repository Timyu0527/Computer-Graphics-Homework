#include "block.h"

Block::Block() : BaseObject() {
    color = RGBColor(0, 0, 0);
}

Block::Block(float _x, float _y, float _z, float _w, float _h, float _len, int red, int green, int blue) : BaseObject(_x, _y, _z, _w, _h, _len) {
    color = RGBColor(red, green, blue);
}

bool Block::isCollide(Robot *robot){
    float body_x = robot->getX();
    float body_z = robot->getZ();

    if(body_x + ROBOT_WIDTH / 2 >= x - width / 2 && body_x + ROBOT_WIDTH <= x + width / 2 &&
       body_z + ROBOT_WIDTH >= z - len / 2 && body_z + ROBOT_WIDTH <= z + len / 2){
        return 1;
    }
    if(body_x + ROBOT_WIDTH / 2 >= x - width / 2 && body_x + ROBOT_WIDTH <= x + width / 2 &&
       body_z - ROBOT_WIDTH >= z - len / 2 && body_z - ROBOT_WIDTH <= z + len / 2){
        return 1;
    }
    if(body_x - ROBOT_WIDTH / 2 >= x - width / 2 && body_x - ROBOT_WIDTH <= x + width / 2 &&
       body_z + ROBOT_WIDTH >= z - len / 2 && body_z + ROBOT_WIDTH <= z + len / 2){
        return 1;
    }
    if(body_x - ROBOT_WIDTH / 2 >= x - width / 2 && body_x - ROBOT_WIDTH <= x + width / 2 &&
       body_z - ROBOT_WIDTH >= z - len / 2 && body_z - ROBOT_WIDTH <= z + len / 2){
        return 1;
    }
    return 0;

}

void Block::draw() {
    glTranslatef(x, y + height / 2, z);
    glColor3fv(color.getRGB());

    glScalef(width, height, len);
    glutSolidCube(1);
}