#include "navbar.h"

Navbar::Navbar(int _x, int _y, int _h) : Entry(_x, _y, 800, _h, ""){
    s_col = RGBColor(50, 50, 50);
}

void Navbar::addEntry(Entry *_entry){
    // std::cout << y << std::endl;
    // std::cout << y - _entry->getY() - _entry->getHeight() << std::endl;
    resize(width, std::max(y - _entry->getY() + _entry->getHeight(), height));
    entry.push_back(_entry);
}

int Navbar::isMouseOn(int mouse_x, int mouse_y){
    int ret = 0;
    for(Entry *ent:entry){
        ret = ent->isMouseOn(mouse_x, mouse_y);
    }
    if(x <= mouse_x && mouse_x <= x + width
        && y >= mouse_y && mouse_y >= y - height){
        ret = 1;
    }
    return ret;
}

void Navbar::reshape(int _x, int _y, int _w, int _h){
    int delta = _y - y;
    x = _x;
    y = _y;
    width = _w;
    for(Entry *ent:entry){
        ent->reshape(ent->getX(), ent->getY() + delta, ent->getWidth(), ent->getHeight());
        // std::cout << ent->getText() << ": " << ent->getY() << " delta: " << delta << std::endl;
    }
}

void Navbar::hover(int _x, int _y){
    for(Entry *ent:entry){
        ent->hover(_x, _y);
    }
}

int Navbar::attach(int _x, int _y){
    int ret = 0;
    for(Entry *ent:entry){
        ret |= ent->attach(_x, _y);
    }
    return ret;
}

void Navbar::drag(int _x, int _y){
    for(Entry *ent : entry){
        ent->drag(_x, _y);
    }
}

void Navbar::draw(){
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_QUADS);
        glColor3fv(s_col.getColor());
        glVertex2i(x, y - height);
        glVertex2i(x + width, y - height);
        glVertex2i(x + width, y);
        glVertex2i(x, y);
    glEnd();

    for(Entry *ent:entry){
        ent->draw();
    }
}

