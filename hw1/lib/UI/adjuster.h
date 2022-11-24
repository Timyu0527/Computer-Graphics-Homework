#ifndef ADJUSTER_H
#define ADJUSTER_H

#include <sstream>

#include "button.h"

class Adjuster : public Entry{
    private:
        int val, up_b, low_b;
        Button *inc_btn, *dec_btn;
    public:
        Adjuster(int _x, int _y, const char *_text);
        int getVal();
        void reshape(int _x, int _y, int _w, int _h);
        int isMouseOn(int mouse_x, int mouse_y);
        void hover(int _x, int _y);
        int attach(int _x, int _y);
        void increase();
        void decrease();
        void draw();
};

#endif