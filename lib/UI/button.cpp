#include "button.h"

Button::Button(int _x, int _y, int _w, int _h, const char* _text, void (*_func)()):
    Entry(_x, _y, _w, _h, _text),
    func(_func){
    i_col = RGBColor(50, 50, 50);
    h_col = RGBColor(100, 100, 100);
    a_col = RGBColor(200, 200, 200);
    s_col = i_col;
}

void Button::setIdleColor(RGBColor _i_col){
    i_col = _i_col;
}

void Button::setHoverColor(RGBColor _h_col){
    h_col = _h_col;
}

void Button::setAttachColor(RGBColor _a_col){
    a_col = _a_col;
}

int Button::isMouseOn(int mouse_x, int mouse_y){
    if(x <= mouse_x && mouse_x <= x + width
        && y >= mouse_y && mouse_y >= y - height){
        return 1;
    }
    return 0;
}      

void Button::draw(){
    glColor3fv(s_col.getColor());
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_QUADS);
        glVertex2i(x, y - height);
        glVertex2i(x + width, y - height);
        glVertex2i(x + width, y);
        glVertex2i(x, y);
    glEnd();
    int pos_x, pos_y = y - height / 2 - 5;
    if(align == TEXT_ALIGN::LEFT) pos_x = x + 5;
    else if(align == TEXT_ALIGN::CENTER) pos_x = x + width / 2 - text.size() * (1.0 * FONT_WIDTH / 2);
    else if(align == TEXT_ALIGN::RIGHT) pos_x = x + width - text.size() * 9 - FONT_HEIGHT / 2;
    drawText(pos_x, pos_y, text.c_str());
}

void Button::hover(int _x, int _y){
    if(isMouseOn(_x, _y)) setColor(h_col);
    else setColor(i_col);
}

int Button::attach(int _x, int _y){
    if(isMouseOn(_x, _y)){
        setColor(a_col);
        func();
        return 1;
    }
    return 0;
}