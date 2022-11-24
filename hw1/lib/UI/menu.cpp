#include "menu.h"

Menu::Menu(int _x, int _y, const char* _text):Entry(_x, _y, 0, 0, _text), show(0){
    int len = strlen(_text);
    height = FONT_HEIGHT + margin * 2;
    width = getTextWidth(_text, margin);
    top = new Button(x, y, width, height, _text, nullptr);
    top->setAlign(TEXT_ALIGN::CENTER);
    bottom = y - 2 * height;
    i_col = RGBColor(50, 50, 50);
    h_col = RGBColor(100, 100, 100);
    a_col = RGBColor(200, 200, 200);
}

int Menu::isMouseOn(int mouse_x, int mouse_y){
    if(top->isMouseOn(mouse_x, mouse_y)) return 1;
    if(show){
        for(int i = 0; i < opt.size(); ++i){
            if(opt[i]->isMouseOn(mouse_x, mouse_y)) return i + 2;
        }
    }
    return 0;
}

void Menu::addMenuEntry(const char *_text, void (*_func)()){
    width = std::max(width, getTextWidth(_text, margin));
    Button *newEntry = new Button(x, bottom + height,
                                  width, height,
                                  _text,
                                  _func);
    bottom -= height;
    opt.push_back(newEntry);
    for(Entry *btn:opt) btn->resize(width, height);
}

void Menu::setColor(int r, int g, int b){
    top->setColor(r, g, b);
    for(Entry *btn:opt){
        btn->setColor(r, g, b);
    }
}

void Menu::setButtonColor(int idx, int r, int g, int b){
    if(idx == 1) top->setColor(r, g, b);
    else opt[idx - 2]->setColor(r, g, b);
}

void Menu::reshape(int _x, int _y, int _w, int _h){
    int tmp_y = _y;
    x = _x;
    y = _y;
    top->reshape(x, y, top->getWidth(), top->getHeight());
    for(Entry *entry:opt){
        entry->reshape(x, tmp_y - height, entry->getWidth(), height);
        tmp_y -= height;
    }
}

int Menu::attach(int _x, int _y){
    int btn_id = isMouseOn(_x, _y);
    if(btn_id){
        if(btn_id == 1) setButtonColor(btn_id, 200, 200, 200);
        if(show){
            show = 0;
            if(btn_id != 1) opt[btn_id - 2]->attach(_x, _y);
        }
        else if(top->isMouseOn(_x, _y)){
            show = 1;
        }
        return 1;
    }
    else{
        if(show) show = 0;
    }
    return 0;
}

void Menu::hover(int _x, int _y){
    int btn_id = isMouseOn(_x, _y);
    if(btn_id){
        if(show){
            for(int i = 1; i < opt.size() + 2; ++i){
                if(i == btn_id) setButtonColor(btn_id, 100, 100, 100);
                else setButtonColor(i, 50, 50, 50);
            }
        }
        else{
            for(int i = 1; i < opt.size() + 2; ++i){
                if(i == btn_id) setButtonColor(btn_id, 100, 100, 100);
                else setButtonColor(i, 50, 50, 50);
            }
        }
    }
    else setColor(50, 50, 50);
}

void Menu::draw(){
    top->draw();
    if(show){
        for(Entry *btn:opt){
            btn->draw();
        }
    }
}