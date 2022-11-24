#ifndef MY_DEFINE_H
#define MY_DEFINE_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <string.h>

#include <GL/glut.h>

#include "RGBColor.h"

#define ROBOT_ARM_LENGTH 3.0
#define ROBOT_ARM_WIDTH 0.5

#define ROBOT_LEG_LENGTH 4.0
#define ROBOT_LEG_WIDTH 0.5

#define ROBOT_HEAD_SIZE 1.0

#define ROBOT_BODY_WIDTH 1.0
#define ROBOT_BODY_HEIGHT 3.0
#define ROBOT_BODY_LENGTH 2.0

#define ROBOT_WIDTH ROBOT_BODY_WIDTH
#define ROBOT_HEIGHT ROBOT_BODY_HEIGHT + ROBOT_HEAD_HEIGHT + ROBOT_LEG_HEIGHT

#define ROBOT_JUMP_SPEED 0.75

#define ROBOT_WAVE_ANGLE 150
#define ROBOT_WAVE_SPEED 6 

#define ROBOT_SIT_LEG_ANGLE 120
#define ROBOT_SIT_LEG_SPEED 6 
// #define ROBOT_LENGTH ROBOT_BODY_LENGTH

#define ROBOT_STEP 0.25

#define ROBOT_SIZE 0.75

const float PI = acos(-1.0);

enum MOVE_DIRECTION{
    FORWARD,
    BACKWARD,
};

enum TURN_DIRECTION{
    LEFT,
    RIGHT,
};

#endif