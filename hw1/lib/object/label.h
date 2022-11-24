#ifndef LABEL_H
#define LABEL_H

#include <string>

#include "object.h"
#include "../text_function.h"

class Label : public Object{
    private:
        std::string text;
    public:
        Label();
        void addChar(char _ch);
        void click(int _x, int _y);
        void drag(int _x, int _y);
        void draw();
};

#endif