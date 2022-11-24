#include "lib/my_gl_lib.h"

int wnd_width = 800, wnd_height = 600;

enum VIEW_MODE{
    GOD,
    FIRST,
    SECOND,
    THIRD,
    X_AXIS,
    Y_AXIS,
    Z_AXIS,
    MIX,
};

int view_mode = VIEW_MODE::MIX;
float roll = 0, yaw = 0, pitch = 0;
float dist = 20 * ROBOT_SIZE;
float eye[3] = {}, focus[3] = {}, vup[3] = {0, 1, 0};
Robot *robot = new Robot(20, ROBOT_LEG_LENGTH + ROBOT_BODY_HEIGHT / 2 - 0.5, 10);
bool keyStates[256] = {};
std::vector<Gun *> guns(3);
std::vector<Block *> blocks(5);

void init(){
    guns[0] = new Gun(20, 5, 25, 50, 50, 50);
    guns[1] = new Gun(5, 5, 5, 50, 50, 50);
    guns[2] = new Gun(10, 5, 30, 50, 50, 50);

    blocks[0] = new Block(40, 0, 40, 5, 10, 5, 127, 127, 0);
    blocks[1] = new Block(25, 0, 15, 3, 4, 3, 127, 127, 0);
    blocks[2] = new Block(5, 0, 15, 3, 5, 3, 127, 127, 0);
    blocks[3] = new Block(30, 0, 10, 3, 6, 3, 127, 127, 0);
    blocks[4] = new Block(30, 0, 30, 3, 6, 5, 127, 127, 0);
    
    eye[1] = focus[1] = (robot->getY() + (ROBOT_BODY_HEIGHT + ROBOT_HEAD_SIZE) / 2)* ROBOT_SIZE;
    focus[0] = dist;

    glClearColor(0.0, 0.0, 0.0, 1.0);      /*set the background color BLACK */
                    /*Clear the Depth & Color Buffers */
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, wnd_width, wnd_height);

    /*-----Set a parallel projection mode-----*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0 , -15.0, 15.0, -50.0, 150.0);
    
    glEnable(GL_DEPTH_TEST);  /*Enable depth buffer for shading computing */

    glutSwapBuffers();
    glFlush();/*Enforce window system display the results*/
}

void draw_axes(){
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(5.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(5.0, 0.0, 0.0);
    glEnd();

    glLineWidth(5.0);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 5.0, 0.0);
    glEnd();

    glLineWidth(5.0);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 5.0);
    glEnd();
}

void draw_floor(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            if((i + j) % 2 == 0) glColor3f(0.9, 0.9, 0.9);
            else glColor3f(0.2, 0.2, 0.2);
            glBegin(GL_POLYGON);
                glVertex3f(i, 0.0, j);
                glVertex3f(i, 0.0, j + 1);
                glVertex3f(i + 1, 0.0, j + 1);
                glVertex3f(i + 1, 0.0, j);
            glEnd();
        }
    }
}

void make_view(int mode, float robot_x, float robot_y, float robot_z){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(mode == VIEW_MODE::FIRST){
        glViewport(wnd_width / 2, 0, wnd_width / 2, wnd_height / 2);
        glRotatef(90-robot->getAng(), 0.0, 1.0, 0.0);
        glTranslatef(-robot_x, -robot_y - ROBOT_SIZE, -robot_z);
    }
    else if(mode == VIEW_MODE::X_AXIS){
        glViewport(0, wnd_height / 2, wnd_width / 2, wnd_height / 2);
        gluLookAt(dist, robot_y, robot_z, 
                  0, robot_y, robot_z,
                  0.0, 1.0, 0.0);
    }
    else if(mode == VIEW_MODE::Y_AXIS){
        glViewport(wnd_width / 2, wnd_height / 2, wnd_width / 2, wnd_height / 2);
        gluLookAt(robot_x, dist, robot_z, 
                  robot_x, 0, robot_z,
                  0.0, 0.0, 1.0);
    }
    else if(mode == VIEW_MODE::Z_AXIS){
        glViewport(0, 0, wnd_width / 2, wnd_height / 2);
        gluLookAt(robot_x, robot_y, dist, 
                  robot_x, robot_y, 0,
                  0.0, 1.0, 0.0);
    }
}

void make_projection(int mode){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (mode == VIEW_MODE::FIRST){
        gluPerspective(90.0, (double)wnd_width / (double)wnd_height, 1.5, 50.0);
    }
    else{
        if (wnd_width > wnd_height)
            glOrtho(-20.0, 20.0, -20.0*(float)wnd_height/(float)wnd_width, 20.0*(float)wnd_height/(float)wnd_width, 
                    -10.5, 150.0);
        else
            glOrtho(-20.0*(float)wnd_width/(float)wnd_height, 20.0*(float)wnd_width/(float)wnd_height, -20.0, 20.0, 
                    -10.5, 150.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

void draw_object(){
    draw_axes();
    draw_floor();

    glScalef(ROBOT_SIZE, ROBOT_SIZE, ROBOT_SIZE);

    robot->draw();
    for(Block *block : blocks){
        glPushMatrix();
        block->draw();
        glPopMatrix();
    }
    for(Gun * gun : guns){
        if(!gun->isPick()){
            glPushMatrix();
            gun->draw();
            glPopMatrix();
        }
    }
}

void fix_coord(float x, float y, float z){
    float tmp_p[4] = {0, 0, 0, 1}, tmp_f[4] = {dist, 0, 0, 1}, tmp_v[4] = {0, 1, 0, 0};
    float _eye[4] = {}, _focus[4] = {}, _vup[4] = {};
    float mat[16] = {};
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(eye[0], eye[1], eye[2]);
    glRotatef(pitch, 1.0, 0.0, 0.0);
    glRotatef(roll, 0.0, 1.0, 0.0);
    glRotatef(yaw, 0.0, 0.0, 1.0);
    // std::cout << "roll:" << roll << std::endl;
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
    for(int i = 0; i < 16; ++i){
        _eye[i % 4] += mat[i] * tmp_p[i / 4];
        _focus[i % 4] += mat[i] * tmp_f[i / 4];
        _vup[i % 4] += mat[i] * tmp_v[i / 4];
        // std::cout << mat[i % 4 * 4 + i / 4] << " ";
        // if(i % 4 == 3) std::cout << std::endl;
    }
    for(int i = 0; i < 3; ++i){
        _eye[i] /= _eye[3];
        _focus[i] /= _focus[3];
        eye[i] = _eye[i];
        focus[i] = _focus[i];
        vup[i] = _vup[i];
        // std::cout << pos[i] << " ";
    }
    // std::cout << std::endl;
    glPopMatrix();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(VIEW_MODE::FIRST <= view_mode  && view_mode <= VIEW_MODE::THIRD)
        gluPerspective(90.0, (double)wnd_width / (double)wnd_height, 1.5, 50.0);
    else glOrtho(-20.0*(float)wnd_width/(float)wnd_height, 20.0*(float)wnd_width/(float)wnd_height,
                 -20.0, 20.0, 
                 -10.5, 150.0);

    /*----Define the current eye position and the eye-coordinate system---*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();           /* Initialize modelview matrix */    

    // float roll = (robot->getAng()) * PI / 180;
    float robot_x = robot->getX() * ROBOT_SIZE;
    float robot_y = (robot->getY() + (ROBOT_BODY_HEIGHT + ROBOT_HEAD_SIZE) / 2)* ROBOT_SIZE;
    float robot_z = robot->getZ() * ROBOT_SIZE;


    if(view_mode == VIEW_MODE::GOD){
        glViewport(0, 0, wnd_width, wnd_height);
        gluLookAt(50 + robot_x, 20 + robot_y, 50 + robot_z,
                  robot_x, robot_y, robot_z,
                  0.0, 1.0, 0.0);
    }
    else if(view_mode == VIEW_MODE::FIRST){
        // roll = robot->getAng();
        glViewport(0, 0, wnd_width, wnd_height);
        fix_coord(robot_x, robot_y, robot_z);
        // std::cout << "eye: " << std::endl;
        // for(int i = 0; i < 3; ++i){
        //     std::cout << eye[i] << " ";
        // }
        // std::cout << std::endl;
        // std::cout << "focus: " << std::endl;
        // for(int i = 0; i < 3; ++i){
        //     std::cout << focus[i] << " ";
        // }
        // std::cout << std::endl;
        // std::cout << "vup: " << std::endl;
        // for(int i = 0; i < 3; ++i){
        //     std::cout << vup[i] << " ";
        // }
        // std::cout << std::endl;
        gluLookAt(eye[0], eye[1], eye[2],
                  focus[0], focus[1], focus[2],
                  vup[0], vup[1], vup[2]);
        // glRotatef(90-robot->getAng(), 0.0, 1.0, 0.0);
        // glTranslatef(-robot_x, -robot_y - ROBOT_SIZE, -robot_z);
    }
    else if(view_mode == VIEW_MODE::SECOND){
        glViewport(0, 0, wnd_width, wnd_height);
        glTranslatef(0, 0, -dist);
        glRotatef(270-robot->getAng(), 0.0, 1.0, 0.0);
        glTranslatef(-robot_x, -robot_y, -robot_z);
    }
    else if(view_mode == VIEW_MODE::THIRD){
        glViewport(0, 0, wnd_width, wnd_height);
        glTranslatef(0, 0, -dist);
        glRotatef(90-robot->getAng(), 0.0, 1.0, 0.0);
        glTranslatef(-robot_x, -robot_y, -robot_z);
    }
    else if(view_mode == VIEW_MODE::X_AXIS){
        glViewport(0, 0, wnd_width, wnd_height);
        gluLookAt(dist, robot_y, robot_z, 
                  0, robot_y, robot_z,
                  0.0, 1.0, 0.0);
    }
    else if(view_mode == VIEW_MODE::Y_AXIS){
        glViewport(0, 0, wnd_width, wnd_height);
        gluLookAt(robot_x, dist, robot_z, 
                  robot_x, 0, robot_z,
                  0.0, 0.0, 1.0);
    }
    else if(view_mode == VIEW_MODE::Z_AXIS){
        glViewport(0, 0, wnd_width, wnd_height);
        gluLookAt(robot_x, robot_y, dist, 
                  robot_x, robot_y, 0,
                  0.0, 1.0, 0.0);
    }
    else{

        make_projection(VIEW_MODE::FIRST);
        make_view(VIEW_MODE::FIRST, robot_x, robot_y, robot_z);
        draw_object();

        make_projection(VIEW_MODE::X_AXIS);
        make_view(VIEW_MODE::X_AXIS, robot_x, robot_y, robot_z);
        draw_object();

        make_projection(VIEW_MODE::Y_AXIS);
        make_view(VIEW_MODE::Y_AXIS, robot_x, robot_y, robot_z);
        draw_object();

        make_projection(VIEW_MODE::Z_AXIS);
        make_view(VIEW_MODE::Z_AXIS, robot_x, robot_y, robot_z);
        draw_object();

        glutSwapBuffers();
        glFlush();/*Enforce window system display the results*/
        return;
    }

    // gluLookAt(50.0, 20.0, 50.0, 0.0, 0.0, 0.0 , 0.0, 1.0, 0.0);

    // std::cout << "display" << std::endl;
    draw_object();

    glutSwapBuffers();
    glFlush();/*Enforce window system display the results*/
}

void special_keys(int key, int x, int y){
    std::cout << "pitch: " << pitch << std::endl;
    std::cout << "key: " << key << std::endl;
    if(key == GLUT_KEY_UP){
        yaw += 4;
    }
    else if(key == GLUT_KEY_DOWN){
        yaw -= 4;
    }
    else if(key == GLUT_KEY_RIGHT){
        roll -= 4;
    }
    else if(key == GLUT_KEY_LEFT){
        roll += 4;
    }
    else if(key == GLUT_KEY_PAGE_UP){
        pitch += 4;
    }
    else if(key == GLUT_KEY_PAGE_DOWN){
        pitch -= 4;
    }
    if(pitch < 0){
        pitch += 360;
    }
    else if(pitch >= 360){
        pitch -= 360;
    }
    if(roll < 0){
        roll += 360;
    }
    else if(roll >= 360){
        roll -= 360;
    }
    if(yaw < 0){
        yaw += 360;
    }
    else if(yaw >= 360){
        yaw -= 360;
    }
    glutPostRedisplay();
}

void update(){
    if(keyStates[27]) exit(0);
    if(keyStates['w'] || keyStates['W']){
        std::cout << "move_forward" << std::endl;
        // std::cout << block->isCollide(robot) << std::endl;
        bool isCollide = false;
        for(Block *block : blocks){
            isCollide |= block->isCollide(robot); 
        }
        if(!isCollide) robot->move(MOVE_DIRECTION::FORWARD); else{
            for(int i = 0; i < 5; ++i){
                robot->move(MOVE_DIRECTION::BACKWARD);
            }
        }

    }
    if(keyStates['s'] || keyStates['S']){
        std::cout << "move_backward" << std::endl;
        bool isCollide = false;
        for(Block *block : blocks){
            isCollide |= block->isCollide(robot); 
        }
        if(!isCollide) robot->move(MOVE_DIRECTION::BACKWARD); else{
            for(int i = 0; i < 5; ++i){
                robot->move(MOVE_DIRECTION::FORWARD);
            }
        }
    }
    if(keyStates['a'] || keyStates['A']){
        std::cout << "turn_left" << std::endl;
        robot->turn(TURN_DIRECTION::LEFT);
    }
    if(keyStates['d'] || keyStates['D']){
        std::cout << "turn_right" << std::endl;
        robot->turn(TURN_DIRECTION::RIGHT);
    }
    if(keyStates[' ']){
        std::cout << "jump" << std::endl;
        robot->jump(display);
    }
    if(keyStates['z'] || keyStates['Z']){
        robot->crouch(display);
    }
    if(keyStates['e'] || keyStates['E']){
        std::cout << "wave" << std::endl;
        robot->wave(display);
    }
    if(keyStates['x'] || keyStates['X']){
        std::cout << "sit" << std::endl;
        robot->sit(display);
    }
    if(keyStates['\t']){
        std::cout << "change view mode" << std::endl;
        view_mode = (view_mode + 1) % 8;
    }
    if(keyStates['p'] || keyStates['P']){
        for(Gun *gun : guns){
            robot->pick(gun, display);
        }
    }
    if(keyStates['q'] || keyStates['Q']){
        for(Gun *gun : guns){
            robot->drop(gun, display);
        }
    }
    if(keyStates['u'] || keyStates['U']){
        robot->useItem(display);
    }
}


void reshape(int new_w, int new_h){
    wnd_width = new_w;
    wnd_height = new_h;


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(new_w > new_h)
        glOrtho(-20.0, 20.0, -20.0*(float)wnd_height/(float)wnd_width, 20.0*(float)wnd_height/(float)wnd_width, 
                -10.5, 150.0);
    else
        glOrtho(-20.0*(float)wnd_width/(float)wnd_height, 20.0*(float)wnd_width/(float)wnd_height, -20.0, 20.0, 
                -10.5, 150.0);
    glViewport(0, 0, wnd_width, wnd_height);
}

void keyboard(unsigned char key, int x, int y){
    keyStates[key] = 1;
    update();
    glutPostRedisplay();
}
void keyboardUp(unsigned char key, int x, int y){
    keyStates[key] = 0;
    update();
    glutPostRedisplay();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(wnd_width, wnd_height);
    glutCreateWindow("Robot");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keys);
    glutKeyboardUpFunc(keyboardUp);

    glutMainLoop();
}