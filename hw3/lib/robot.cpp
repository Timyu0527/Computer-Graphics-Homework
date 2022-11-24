#include "robot.h"

Robot::Robot() : x(0), y(0), z(0),
                 is_crouch(0), is_sit(0), is_pick(0),
                 item(nullptr){
    body = new Body();
    head = new Head();
    left_arm = new Limbs();
    right_arm = new Limbs();
    left_leg = new Limbs();
    right_leg = new Limbs();
    _init();
}

Robot::Robot(float _x, float _y, float _z) :
             x(_x), y(_y), z(_z),
             is_crouch(0), is_sit(0), is_pick(0),
             item(nullptr){
    body = new Body(_x, _y, _z,
                    ROBOT_BODY_WIDTH, ROBOT_BODY_HEIGHT, ROBOT_BODY_LENGTH,
                    150, 150, 150);
    head = new Head(-ROBOT_BODY_WIDTH / 2, body->getHeight() / 2, -0.5,
                    ROBOT_HEAD_SIZE, ROBOT_HEAD_SIZE, ROBOT_HEAD_SIZE,
                    255, 255, 255);
    left_arm = new Limbs(0, body->getHeight() / 2 - ROBOT_ARM_LENGTH / 4, -body->getLen() / 2 - ROBOT_ARM_WIDTH / 2,
                         ROBOT_ARM_WIDTH, ROBOT_ARM_LENGTH, ROBOT_ARM_WIDTH,
                         100, 100, 100);
    right_arm = new Limbs(0, body->getHeight() / 2 - ROBOT_ARM_LENGTH / 4, body->getLen() / 2 + ROBOT_ARM_WIDTH / 2,
                         ROBOT_ARM_WIDTH, ROBOT_ARM_LENGTH, ROBOT_ARM_WIDTH,
                         100, 100, 100);
    left_leg = new Limbs(0, -body->getHeight() / 2 - ROBOT_ARM_LENGTH / 4, -body->getLen() / 2 + ROBOT_ARM_WIDTH / 2,
                         ROBOT_ARM_WIDTH, ROBOT_ARM_LENGTH, ROBOT_ARM_WIDTH,
                         100, 100, 100);
    right_leg = new Limbs(0, -body->getHeight() / 2 - ROBOT_ARM_LENGTH / 4, body->getLen() / 2 - ROBOT_ARM_WIDTH / 2,
                         ROBOT_ARM_WIDTH, ROBOT_ARM_LENGTH, ROBOT_ARM_WIDTH,
                         100, 100, 100);
    ang[6] = 0; // head angle
    _init();
}

void Robot::_init(){
    memset(left_arm_ang, 0, sizeof(left_arm_ang));
    memset(right_arm_ang, 0, sizeof(right_arm_ang));
    memset(left_leg_ang, 0, sizeof(left_leg_ang));
    memset(right_leg_ang, 0, sizeof(right_leg_ang));

    ang[0] = 6, ang[1] = -6; // left leg
    ang[2] = -6, ang[3] = 6; // right leg
    ang[4] = -6; // left arm
    ang[5] = 6; // right arm

    left_arm->rotateZ(left_arm_ang[2][0], left_arm_ang[2][1]);
    right_arm->rotateZ(right_arm_ang[2][0], right_arm_ang[2][1]);
    right_leg->rotateZ(right_leg_ang[2][0], right_leg_ang[2][1]);
    left_leg->rotateZ(left_leg_ang[2][0], left_leg_ang[2][1]);
}

void Robot::_crouch(void (*func)(void)){
    _init();
    for(; left_leg_ang[2][0] < 60 &&
        right_leg_ang[2][0] < 60 &&
        left_leg_ang[2][1] > -120 &&
        right_leg_ang[2][1] > -120;
        left_leg_ang[2][0] += 6,
        right_leg_ang[2][0] += 6,
        left_leg_ang[2][1] -= 12,
        right_leg_ang[2][1] -= 12){

        right_leg->rotateZ(right_leg_ang[2][0], right_leg_ang[2][1]);
        left_leg->rotateZ(left_leg_ang[2][0], left_leg_ang[2][1]);

        y = body->getHeight() / 2 * cos(left_leg_ang[2][0] * PI / 180) + body->getHeight() / 2 * cos(right_leg_ang[2][0] * PI / 180);
        y += left_leg->getHeight();
        body->setY(y);

        func();
    }
}

void Robot::_stand(void (*func)(void)){
    left_leg_ang[2][0] = 60;
    right_leg_ang[2][0] = 60;
    left_leg_ang[2][1] = -120;
    right_leg_ang[2][1] = -120;

    for(; left_leg_ang[2][0] > 0 &&
        right_leg_ang[2][0] > 0 &&
        left_leg_ang[2][1] < 0 &&
        right_leg_ang[2][1] < 0;
        left_leg_ang[2][0] -= 6,
        right_leg_ang[2][0] -= 6,
        left_leg_ang[2][1] += 12,
        right_leg_ang[2][1] += 12){

        right_leg->rotateZ(right_leg_ang[2][0], right_leg_ang[2][1]);
        left_leg->rotateZ(left_leg_ang[2][0], left_leg_ang[2][1]);

        y = body->getHeight() / 2 * cos(left_leg_ang[2][0] * PI / 180) + body->getHeight() / 2 * cos(right_leg_ang[2][0] * PI / 180);
        y += left_leg->getHeight();
        body->setY(y);

        func();
    }
    _init();
}

float Robot::_distance(float _x, float _y, float _z){
    return sqrt((_x - x) * (_x - x) + (_y - y) * (_y - y) + (_z - z) * (_z - z));
}

float Robot::getX(){
    return body->getX();
}

float Robot::getY(){
    return body->getY();
}

float Robot::getZ(){
    return body->getZ();
}

float Robot::getAng(){
    return ang[6];
}

void Robot::turn(int dir){
    if(is_sit) return;
    if(dir == TURN_DIRECTION::LEFT){
        ang[6] += 4;
    }
    else if(dir == TURN_DIRECTION::RIGHT){
        ang[6] -= 4;
    }
    if(ang[6] <= -360) ang[6] += 360;
    else if(ang[6] >= 360) ang[6] -= 360;
    body->turn(ang[6]);
}

void Robot::move(int dir){
    if(is_sit) return;
    if(!is_crouch){
        if(left_leg_ang[2][0] >= 30) ang[0] = -6, ang[1] = 6;
        else if(left_leg_ang[2][0] <= -30) ang[0] = 6, ang[1] = -6;
        if(left_leg_ang[2][0] <= 0 && ang[0] < 0) ang[1] = 0;

        left_leg_ang[2][0] += ang[0];
        left_leg_ang[2][1] += ang[1]; 
        if(left_leg_ang[2][0] <= 0) left_leg_ang[2][1] = 0;

        if(right_leg_ang[2][0] >= 30) ang[2] = -6, ang[3] = 6;
        else if(right_leg_ang[2][0] <= -30) ang[2] = 6, ang[3] = -6;
        if(right_leg_ang[2][0] <= 0 && ang[2] < 0) ang[3] = 0;

        right_leg_ang[2][0] += ang[2];
        right_leg_ang[2][1] += ang[3]; 
        if(right_leg_ang[2][0] <= 0) right_leg_ang[2][1] = 0;

    }
    else{
        if(left_leg_ang[2][0] >= 120) ang[0] = -6;
        else if(left_leg_ang[2][0] <= 0) ang[0] = 6;

        left_leg_ang[2][0] += ang[0];

        if(right_leg_ang[2][0] >= 120) ang[2] = -6;
        else if(right_leg_ang[2][0] <= 0) ang[2] = 6;

        right_leg_ang[2][0] += ang[2];

    }
    left_leg->rotateZ(left_leg_ang[2][0], left_leg_ang[2][1]);
    right_leg->rotateZ(right_leg_ang[2][0], right_leg_ang[2][1]);

    if(left_arm_ang[2][0] >= 30) ang[4] = -6;
    else if(left_arm_ang[2][0] <= -30) ang[4] = 6;

    left_arm_ang[2][0] += ang[4];

    left_arm->rotateZ(left_arm_ang[2][0], left_arm_ang[2][1]);

    if(!item){
        if(right_arm_ang[2][0] >= 30) ang[5] = -6;
        else if(right_arm_ang[2][0] <= -30) ang[5] = 6;

        right_arm_ang[2][0] += ang[5];

        right_arm->rotateZ(right_arm_ang[2][0], right_arm_ang[2][1]);
    }

    body->move(dir);
    x = body->getX();
    y = body->getY();
    z = body->getZ();
}

void Robot::crouch(void (*func)(void)){
    if(is_sit) return;
    if(!is_crouch){
        _crouch(func);
    }
    else{
        _stand(func);
    }
    is_crouch = !is_crouch;
}

void Robot::pick(BaseObject *obj, void (*func)(void)){
    if(is_sit) return;
    if(_distance(obj->getX(), obj->getY(), obj->getZ()) < 5){
        _init();
        is_pick = 1;
        // std::cout << "1" << std::endl;
        for(; right_arm_ang[2][0] < 90; right_arm_ang[2][0] += ang[5]){
            right_arm->rotateZ(right_arm_ang[2][0], right_arm_ang[2][1]);
            func();
        }
        right_arm_ang[2][0] = 90;
        item = obj;
        item->picked();
        item->setX(right_arm->getX() + right_arm->getHeight() / 2 + 1);
        item->setY(right_arm->getY() - item->getHeight() / 2);
        item->setZ(0);
        right_arm->rotateZ(right_arm_ang[2][0], right_arm_ang[2][1]);
    }
}

void Robot::drop(BaseObject *obj, void (*func)(void)){
    if(is_sit) return;
    if(item){
        is_pick = 0;
        // std::cout << "2" << std::endl;
        for(; right_arm_ang[2][0] > 0; right_arm_ang[2][0] -= ang[5]){
            right_arm->rotateZ(right_arm_ang[2][0], right_arm_ang[2][1]);
            func();
        }
        item->dropped();
        item->setX(body->getX());
        item->setY(body->getY());
        item->setZ(body->getZ());
        item = nullptr;
        _init();
        right_arm->rotateZ(right_arm_ang[2][0], right_arm_ang[2][1]);
    }
}

void Robot::sit(void (*func)(void)){
    float leg_ang = ROBOT_SIT_LEG_ANGLE, hand_ang = 60, tmp_y;
    if(!is_sit){
        tmp_y = y;
        for(float i = 0, j = 0, k = 0; i < leg_ang;
            i += ROBOT_SIT_LEG_SPEED, j += ROBOT_SIT_LEG_SPEED,
            k += ROBOT_SIT_LEG_SPEED * 0.5){
            left_leg->rotateZ(i, -j);
            right_leg->rotateZ(i, -j);
            left_arm->rotateZ(k, 0);
            left_arm->rotateX(0, -k / 0.5 * 0.75);
            right_arm->rotateZ(k, 0);
            right_arm->rotateX(0, k / 0.5 * 0.75);

            if(tmp_y > ROBOT_BODY_HEIGHT / 2 + 1){
                tmp_y -= (ROBOT_BODY_HEIGHT / 2 + 1) * ROBOT_SIT_LEG_SPEED / ROBOT_SIT_LEG_ANGLE;
            }
            else tmp_y = ROBOT_BODY_HEIGHT / 2 + 1;
            body->setY(tmp_y);
            func();
        }
        body->setY(ROBOT_BODY_HEIGHT / 2 + 1);
        func();
    }
    else{
        tmp_y = ROBOT_BODY_HEIGHT / 2 + 1;
        for(float i = leg_ang, j = leg_ang, k = hand_ang; i > 0;
            i -= ROBOT_SIT_LEG_SPEED, j -= ROBOT_SIT_LEG_SPEED,
            k -= ROBOT_SIT_LEG_SPEED * 0.5){
            left_leg->rotateZ(i, -j);
            right_leg->rotateZ(i, -j);
            left_arm->rotateZ(k, 0);
            left_arm->rotateX(0, -k / 0.5 * 0.75);
            right_arm->rotateZ(k, 0);
            right_arm->rotateX(0, k / 0.5 * 0.75);

            if(tmp_y > y){
                tmp_y = y;
            }
            else tmp_y += (ROBOT_BODY_HEIGHT / 2 + 1) * ROBOT_SIT_LEG_SPEED / ROBOT_SIT_LEG_ANGLE;
            body->setY(tmp_y);
            func();
        }
        body->setY(y);
        func();
    }
    is_sit = !is_sit;
}

void Robot::jump(void (*func)(void)){
    if(is_sit) return;
    float tmp = y, g = 0.05, v = ROBOT_JUMP_SPEED;
    if(!is_crouch) _crouch(func);
    _stand(func);
    for(; v > -ROBOT_JUMP_SPEED ; y += v, v -= g){
        body->setY(y);
        func();
    }
    is_crouch = 0;
    y = tmp;
    body->setY(y);
}

void Robot::wave(void (*func)(void)){
    if(is_sit) return;
    float upper_ang = ROBOT_WAVE_ANGLE, lower_ang;
    for(float i = 0, j = 0; i < upper_ang; i += ROBOT_WAVE_SPEED){
        if(i >= 90) j += ROBOT_WAVE_SPEED;
        left_arm->rotateX(i, j);
        right_arm->rotateX(-i, -j);
        lower_ang = j;
        func();

    }
    for(float i = upper_ang, j = lower_ang; i > 0; i -= ROBOT_WAVE_SPEED){
        if(i <= 90 && j > 0) j -= ROBOT_WAVE_SPEED;
        left_arm->rotateX(i, j);
        right_arm->rotateX(-i, -j);
        func();
    }
    left_arm->rotateX(0, 0);
    right_arm->rotateX(0, 0);
    func();
}

void Robot::useItem(void (*func)(void)){
    if(is_sit) return;
    if(item){
        item->use(func);
    }
}

void Robot::draw(){
    glPushMatrix();
    body->draw();

    head->draw();

    glPushMatrix();
    left_arm->draw();
    glPopMatrix();

    glPushMatrix();
    right_arm->draw();
    if(item){
        glRotatef(-90, 0.0, 0.0, 1.0);
        item->draw();
    }
    glPopMatrix();

    glPushMatrix();
    left_leg->draw();
    glPopMatrix();

    glPushMatrix();
    right_leg->draw();
    glPopMatrix();
    glPopMatrix();
}