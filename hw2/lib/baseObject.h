#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "my_def.h"

class BaseObject{
    protected:
        float x, y, z;
        float len, width, height;
        bool is_picked;
        RGBColor color;
    public:
        BaseObject();
        BaseObject(float _x, float _y, float  _z, float  _len, float  _width, float  _height);
        bool isPick();
        float getX();
        float getY();
        float getZ();
        float getLen();
        float getWidth();
        float getHeight();
        void setX(float _x);
        void setY(float _y);
        void setZ(float _z);
        void setLen(float _len);
        void setWidth(float _width);
        void setHeight(float _height);
        void picked();
        void dropped();
        virtual void use(void (*func)(void)){};
        virtual void draw() = 0;
};

#endif