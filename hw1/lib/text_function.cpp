#include "text_function.h"

void drawText(int x, int y, char const *text){
    // glColor3f(0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    // std::cout << text << std::endl;
    glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)text);
}

void drawText(int x, int y, char const *text, RGBColor *col){
    glColor3fv(col->getColor());
    glRasterPos2f(x, y);
    // std::cout << text << std::endl;
    glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)text);
}

int getTextWidth(char const *text, int margin){
    int len = strlen(text);
    return len * FONT_WIDTH + margin * 2;
}
