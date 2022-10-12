#ifndef BUTTON_H 
#define BUTTON_H 
#include <iostream>
#include <string>

#include <GL/glut.h>
#include <GL/freeglut.h>

#include "entry.h"


class Button : public Entry{
    private:
        void (*func)();
    public:
        Button(int _x, int _y, int _w, int _h, const char* _text, void (*_func)());
        void setIdleColor(RGBColor _i_col);
        void setHoverColor(RGBColor _h_col);
        void setAttachColor(RGBColor _a_col);
        int isMouseOn(int mouse_x, int mouse_y);
        void hover(int _x, int _y);
        int attach(int _x, int _y);
        void draw();
        // void resize(int _w, int _h);
        // void setAlign(int _align);
};
#endif