#ifndef MENU_H
#define MENU_H
#include <string>
#include <vector>
#include <algorithm>


#include "button.h"

class Menu : public Entry{
    private:
        // int x, y, width, height;
        int bottom;
        bool show;
        Button *top;
        std::vector<Entry *> opt;
    public:
        Menu(int _x, int _y, const char *_text);
        int isMouseOn(int mouse_x, int mouse_y);
        void setColor(int r, int g, int b);
        void setButtonColor(int idx, int r, int g, int b);
        void addMenuEntry(const char *_text, void (*_func)());
        void reshape(int _x, int _y, int _w, int _h);
        int attach(int _x, int _y);
        void hover(int _x, int _y);
        void draw();
};

#endif