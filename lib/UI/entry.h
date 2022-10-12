#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include <iostream>

#include "../RGBColor.h"
#include "../text_function.h"
#include "../constant.h"

class Entry{
    protected:
        int x, y, width, height, align, margin;
        RGBColor i_col, h_col, a_col, s_col;
        std::string text;
    public:
        Entry(int _x, int _y, int _w, int _h, const char *_text);
        std::string getText(){
            return text;
        }
        int getX();
        int getY();
        int getWidth();
        int getHeight();
        void resize(int _w, int _h);
        void setX(int _x);
        void setY(int _y);
        void setAlign(int _align);
        void setColor(int r, int g, int b);
        void setColor(RGBColor color);
        virtual int isMouseOn(int mouse_x, int mouse_y) = 0;
        virtual void reshape(int _x, int _y, int _w, int _h);
        virtual void hover(int _x, int _y) = 0;
        virtual int attach(int _x, int _y) = 0;
        virtual void drag(int _x, int _y);
        virtual void draw() = 0;
};

#endif