#ifndef NAVBAR_H
#define NAVBAR_H

#include <vector>

#include "button.h"
#include "menu.h"

class Navbar : public Entry{
    private:
        std::vector<Entry *> entry;
    public:
        Navbar(int _x, int _y, int _h);
        void addEntry(Entry *_entry);
        int isMouseOn(int mouse_x, int mouse_y);
        void reshape(int _x, int _y, int _w, int _h);
        void hover(int _x, int _y);
        int attach(int _x, int _y);
        void drag(int _x, int _y);
        void draw();
};

#endif