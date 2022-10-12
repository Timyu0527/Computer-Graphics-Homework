#include "adjuster.h"

Adjuster::Adjuster(int _x, int _y, const char *_text) :
    Entry(_x, _y, 0, 0, _text),
    val(2),
    up_b(10),
    low_b(1){
        width = getTextWidth(text.c_str(), margin);
        height = FONT_HEIGHT + 2 * margin;
        i_col = RGBColor(50, 50, 50);
        h_col = RGBColor(100, 100, 100);
        a_col = RGBColor(200, 200, 200);
        int text_width = getTextWidth(text.c_str(), margin);
        inc_btn = new Button(x + text_width, y, 20, height / 2, "+", []() -> void {});
        dec_btn = new Button(x + text_width, y - inc_btn->getHeight(), 20, height / 2, "-", []() -> void {});
}

int Adjuster::getVal(){
    return val;
}

void Adjuster::reshape(int _x, int _y, int _w, int _h){
    int delta = _y - y;
    x = _x, y = _y;
    width = _w;
    inc_btn->reshape(inc_btn->getX(), inc_btn->getY() + delta, inc_btn->getWidth(), inc_btn->getHeight());
    dec_btn->reshape(dec_btn->getX(), dec_btn->getY() + delta, dec_btn->getWidth(), dec_btn->getHeight());
}

int Adjuster::isMouseOn(int mouse_x, int mouse_y){
    return inc_btn->isMouseOn(mouse_x, mouse_y) | dec_btn->isMouseOn(mouse_x, mouse_y);
}

void Adjuster::hover(int _x, int _y){
    inc_btn->hover(_x, _y);
    dec_btn->hover(_x, _y);
}

int Adjuster::attach(int _x, int _y){
    int inc = inc_btn->attach(_x, _y);
    int dec = -dec_btn->attach(_x, _y);
    if(inc && val < up_b) val += inc;
    else if(dec && val > low_b) val += dec;
    std::stringstream ss;
    ss << val;
    ss >> text;
    text = "Size: " + text + "px";
    return inc + dec;
}

void Adjuster::increase(){
    val++;
}

void Adjuster::decrease(){
    val--;
}

void Adjuster::draw(){
    int text_width = getTextWidth(text.c_str(), margin);
    inc_btn->draw();
    dec_btn->draw();
    drawText(x + margin, y - height / 2 - 4 , text.c_str());
}