#include "pointer.h"

Pointer::Pointer():in_rad(0), out_rad(5), side(32), cir_ptr(nullptr){}

void Pointer::setPos(int _x, int _y){
    x = _x, y = _y;
}

void Pointer::draw(){
    if(!cir_ptr) {
        cir_ptr = gluNewQuadric();
        gluQuadricDrawStyle(cir_ptr, GLU_FILL);
    }
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    gluDisk(cir_ptr,
            in_rad,  /* inner radius=0.0 */
            out_rad, /* outer radius=10.0 */
            side,   /* 16-side polygon */
            3);
    glPopMatrix();
}