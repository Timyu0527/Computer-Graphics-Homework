#include "head.h"

Head::Head() : BaseObject(){
    color.setColor(0, 0, 0);
}

Head::Head(float _x, float _y, float _z,
           float _w, float _h, float _len,
           int red, int green, int blue) :
           BaseObject(_x, _y, _z, _w, _h, _len){
    color = RGBColor(red, green, blue);
}

void Head::draw(){
    glPushMatrix();
    float pnt[][3] = {{0.0, 0.0, 0.0}, {ROBOT_HEAD_SIZE, 0.0, 0.0}, 
                      {ROBOT_HEAD_SIZE, 0.0, ROBOT_HEAD_SIZE}, {0.0, 0.0, ROBOT_HEAD_SIZE},
                      {0.0, ROBOT_HEAD_SIZE, 0.0}, {ROBOT_HEAD_SIZE, ROBOT_HEAD_SIZE, 0.0},
                      {ROBOT_HEAD_SIZE, ROBOT_HEAD_SIZE, ROBOT_HEAD_SIZE}, {0.0, ROBOT_HEAD_SIZE, ROBOT_HEAD_SIZE}};
    int face[][4] = {{0, 1, 2, 3}, {7, 6, 5, 4}, {0, 4, 5, 1}, 
                     {1, 5, 6, 2}, {3, 2, 6, 7}, {0, 3, 7, 4}};
    glTranslatef(x, y, z);
    for(int i = 0; i < 6; ++i){/* draw the six faces one by one */
        if(i == 3) glColor3fv(color.getRGB());
        else glColor3f(0.5, 0.5, 0.5);
        glBegin(GL_POLYGON);  /* Draw the face */
            glVertex3fv(pnt[face[i][0]]);
            glVertex3fv(pnt[face[i][1]]);
            glVertex3fv(pnt[face[i][2]]);
            glVertex3fv(pnt[face[i][3]]);
        glEnd();
    }
    glPopMatrix();
}