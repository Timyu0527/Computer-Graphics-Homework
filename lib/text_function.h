#ifndef TEXT_FUNCTION_H
#define TEXT_FUNCTION_H

#include <string>
// #include <cstring>

#include <GL/freeglut.h>
#include <GL/glut.h>

#include "constant.h"

void drawText(int x, int y, char const *text);
int getTextWidth(char const *text, int margin);

#endif