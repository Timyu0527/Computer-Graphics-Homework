#include "lib/my_gl_lib.h"

int wnd_width = 800, wnd_height = 600;

enum VIEW_MODE{
    GOD,
    FIRST,
    SECOND,
    THIRD,
};

int view_mode = VIEW_MODE::GOD;
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

void display(){
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(view_mode != VIEW_MODE::GOD) gluPerspective(60, 1.0,1,75);
    else glOrtho(-20.0, 20.0 , -15.0, 15.0, -50.0, 150.0);

    /*----Define the current eye position and the eye-coordinate system---*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();           /* Initialize modelview matrix */    

    float ang = (90 - robot->getAng()) * PI / 180;
    float robot_x = robot->getX() * ROBOT_SIZE;
    float robot_y = (robot->getY() + (ROBOT_BODY_HEIGHT + ROBOT_HEAD_SIZE) / 2)* ROBOT_SIZE;
    float robot_z = robot->getZ() * ROBOT_SIZE;
    float dist = 20 * ROBOT_SIZE;

    if(view_mode == VIEW_MODE::GOD){
        gluLookAt(50 + robot_x, 20 + robot_y, 50 + robot_z,
                  robot_x, robot_y, robot_z,
                  0.0, 1.0, 0.0);
    }
    else if(view_mode == VIEW_MODE::FIRST){
        glRotatef(90-robot->getAng(), 0.0, 1.0, 0.0);
        glTranslatef(-robot_x, -robot_y - ROBOT_SIZE, -robot_z);
    }
    else if(view_mode == VIEW_MODE::SECOND){
        glTranslatef(0, 0, -dist);
        glRotatef(270-robot->getAng(), 0.0, 1.0, 0.0);
        glTranslatef(-robot_x, -robot_y, -robot_z);
    }
    else if(view_mode == VIEW_MODE::THIRD){
        glTranslatef(0, 0, -dist);
        glRotatef(90-robot->getAng(), 0.0, 1.0, 0.0);
        glTranslatef(-robot_x, -robot_y, -robot_z);
    }
    // gluLookAt(50.0, 20.0, 50.0, 0.0, 0.0, 0.0 , 0.0, 1.0, 0.0);

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
    // std::cout << "display" << std::endl;

    glutSwapBuffers();
    glFlush();/*Enforce window system display the results*/
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
        view_mode = (view_mode + 1) % 4;
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

    glViewport(0, 0, wnd_width, wnd_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(new_w > new_h)
        glOrtho(-20.0, 20.0, -20.0*(float)wnd_height/(float)wnd_width, 20.0*(float)wnd_height/(float)wnd_width, 
                -10.5, 150.0);
    else
        glOrtho(-20.0*(float)wnd_width/(float)wnd_height, 20.0*(float)wnd_width/(float)wnd_height, -20.0, 20.0, 
                -10.5, 150.0);
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
    glutKeyboardUpFunc(keyboardUp);

    glutMainLoop();
}