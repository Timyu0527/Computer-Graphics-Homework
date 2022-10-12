#ifndef SLIDER_H
#define SLIDER_H

#include "entry.h"
#include "button.h"

class Slider : public Entry{
    private:
        int bar_width, bar_height;
        float val;
        void (*func)(Slider *);
        Button *btn;
    public:
        Slider(int _x, int _y, const char *_text, void (*_func)(Slider *));
        float getVal();
        int isMouseOn(int mouse_x, int mouse_y);
        void reshape(int _x, int _y, int _w, int _h);
        void hover(int _x, int _y);
        int attach(int _x, int _y);
        void drag(int _x, int _y);
        void draw();
};

#endif