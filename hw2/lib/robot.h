#ifndef ROBOT_H
#define ROBOT_H

#include "body.h"
#include "head.h"
#include "limbs.h"

class Robot{
    private:
        float x, y, z;
        float left_arm_ang[3][2], right_arm_ang[3][2];
        float left_leg_ang[3][2], right_leg_ang[3][2];
        float ang[8];
        bool is_crouch, is_jump, is_sit, is_pick;
        Body *body;
        Head *head;
        Limbs *left_arm, *right_arm, *left_leg, *right_leg;
        BaseObject *item;
        void _init();
        void _crouch(void (*func)(void));
        void _stand(void (*func)(void));
        float _distance(float _x, float _y, float _z);
    public:
        Robot();
        Robot(float _x, float _y, float _z);
        float getX();
        float getY();
        float getZ();
        float getAng();
        void crouch(void (*func)(void));
        void pick(BaseObject *obj, void (*func)(void));
        void drop(BaseObject *obj, void (*func)(void));
        void sit(void (*func)(void));
        void jump(void (*func)(void));
        void wave(void (*func)(void));
        void useItem(void (*func)(void));
        void turn(int dir);
        void move(int dir);
        void draw();
};

#endif