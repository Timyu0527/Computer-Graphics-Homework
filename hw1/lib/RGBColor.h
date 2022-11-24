#ifndef RGBCOLOR_H
#define RGBCOLOR_H

class RGBColor{
    private:
        float color[3];
    public:
        static RGBColor obj_col;
        RGBColor();
        RGBColor(int _r, int _g, int _b);
        void setR(int _r);
        void setG(int _g);
        void setB(int _b);
        void setR(float _r);
        void setG(float _g);
        void setB(float _b);
        void setAll(int _r, int _g, int _b);
        float getR();
        float getG();
        float getB();
        float *getColor();
};

#endif