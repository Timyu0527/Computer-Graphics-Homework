#include "slider.h"
#include <iostream>

Slider::Slider(int _x, int _y, const char *_text, void (*_func)(Slider *)) :
    Entry(_x, _y, 0, 0, _text),
    bar_width(80),
    bar_height(14),
    val(0.5),
    func(_func){
        width = getTextWidth(_text, margin) + bar_width;
        height = FONT_HEIGHT + 2 * margin;
        btn = new Button(x + getTextWidth(text.c_str(), margin) + bar_width / 2 - bar_height / 2,
                         y - height / 2 + bar_height / 2,
                         bar_height,
                         bar_height, 
                         "", 
                         []() -> void {});

        btn->setColor(100, 100, 100);
        btn->setIdleColor(RGBColor(100, 100, 100));
        btn->setHoverColor(RGBColor(150, 150, 150));
        btn->setAttachColor(RGBColor(200, 200, 200));
        s_col = RGBColor(255, 255, 255);
        // std::cout << btn->red << " " << btn->blue << " " << btn->green << std::endl;
}

float Slider::getVal(){
    return val;
}

int Slider::isMouseOn(int mouse_x, int mouse_y){
    int text_width = getTextWidth(text.c_str(), margin);
    if(x + text_width <= mouse_x && mouse_x <= x + text_width + bar_width
       && y - height / 2 - bar_height / 2 <= mouse_y && mouse_y <= y - height / 2 + bar_height / 2){
        return 1;
    }
    return 0;
}

void Slider::reshape(int _x, int _y, int _w, int _h){
    x = _x;
    y = _y;
    width = _w;
    btn->reshape(btn->getX(), _y - height / 2 + bar_height / 2, btn->getWidth(), btn->getHeight());
    // std::cout << y << std::endl;
}

void Slider::hover(int _x, int _y){
    btn->hover(_x, _y);
}

int Slider::attach(int _x, int _y){
    if(isMouseOn(_x, _y)){
        int text_width = getTextWidth(text.c_str(), margin);
        btn->setX(_x - btn->getWidth() / 2);
        val = ((1.0 * btn->getX() + btn->getWidth() / 2) - x - text_width) / bar_width;
        func(this);
        return 1;
    }
    return 0;
}

void Slider::drag(int _x, int _y){
    // std::cout << "drag" << std::endl;
    if(btn->isMouseOn(_x, _y)){
        int text_width = getTextWidth(text.c_str(), margin);
        // int text_width = 0;
        int pos_x = _x;
        if(x + text_width <= pos_x && pos_x <= x + text_width + bar_width){
            btn->setX(pos_x - btn->getWidth() / 2);
            val = ((1.0 * btn->getX() + btn->getWidth() / 2) - x - text_width) / bar_width;
            func(this);
        }
    }
}

void Slider::draw(){
    int text_width = getTextWidth(text.c_str(), margin);
    glColor3fv(s_col.getColor());
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_QUADS);
        glVertex2i(x + text_width , y - height / 2 - bar_height / 2);        
        glVertex2i(x + text_width + bar_width, y - height / 2 - bar_height / 2);        
        glVertex2i(x + text_width + bar_width, y - height / 2 + bar_height / 2);        
        glVertex2i(x + text_width , y - height / 2 + bar_height / 2);        
    glEnd();

    btn->draw();
    drawText(x + margin, y - height / 2 - 4 , text.c_str());
}