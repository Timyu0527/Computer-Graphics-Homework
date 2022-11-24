#include "label.h"
#include <iostream>

Label::Label() : text(""){};

void Label::addChar(char _ch){
    // std::cout << (int)_ch << std::endl;
    if(_ch == 27) finish = 1;
    else if(_ch == 8) text.pop_back();
    if(_ch != 8 && press && !finish){
        if(_ch != 13) text += _ch;
        else text += '\n';
    }
}

void Label::click(int _x, int _y){
    if(!press && !finish){
        press = 1;
        x = _x, y = _y;
    }
}

void Label::drag(int _x, int _y){};

void Label::draw(){
    // std::cout << text << std::endl;
    drawText(x, y, text.c_str(), &s_col);
}