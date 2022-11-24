#include <iostream>
#include <string>
#include <vector>

#include <GL/glut.h>
#include <GL/freeglut.h>

#include "lib/UI/UI.h"
#include "lib/object/draw.h"
#include "lib/imageHandler.h"

#define MY_QUIT -1
#define MY_CLEAR -2
#define MY_SAVE -3
#define MY_BLEND -4
#define MY_LOAD -5

#define WHITE 1
#define RED 2
#define GREEN 3
#define BLUE 4

int wnd_height = 500, wnd_width = 500;
int buf_w, buf_h;
unsigned char *image = nullptr;
int obj_type = OBJ_TYPE::NOTHING, fill_mode = GL_FILL;
int isBlend = 0, isAttach = 0;

typedef int menu_t;
menu_t top_menu, color_menu, file_menu, type_menu, size_menu;

Navbar *navbar = new Navbar(0, wnd_height, FONT_HEIGHT + 20);
std::vector<Object *> buffer, back_buffer;
ImageHandler ImageHandler::img_hdr;
Pointer *Pointer::mouse_ptr = new Pointer();
RGBColor RGBColor::obj_col = RGBColor(127, 127, 127);
Adjuster *adjuster = nullptr;


void init_wnd(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (double)wnd_width, 0.0, (double)wnd_height);
    glViewport(0, 0, wnd_width, wnd_height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    buffer.clear();

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void init_func(){
    glReadBuffer(GL_FRONT);
    glDrawBuffer(GL_FRONT);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void drawGrid(){
    int line_len = 10, inv = 30;
    // std::cout << "display" << std::endl;
    int x = 1, y = wnd_height - navbar->getHeight();
    glLineWidth(2);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    for(; x <= wnd_width; x += inv){
        glBegin(GL_LINES);
            glVertex2i(x, y);
            glVertex2i(x, y - line_len);
        glEnd();
    }
    x = 0;
    for(; y >= 0; y -= inv){
        glBegin(GL_LINES);
            glVertex2i(x, y);
            glVertex2i(x + line_len, y);
        glEnd();
    }
}

void drawPalette(){
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3fv(RGBColor::obj_col.getColor());
    glBegin(GL_QUADS);
        glVertex2i(435 + 20, wnd_height - 10);
        glVertex2i(435 + 20, wnd_height - navbar->getHeight() + 10);
        glVertex2i(435 + navbar->getHeight(), wnd_height - navbar->getHeight() + 10);
        glVertex2i(435 + navbar->getHeight(), wnd_height - 10);
    glEnd();
}

void drawObject(){
    for(Object *obj:buffer){
        if(obj) obj->draw();
    }
}

void drawBackBuffer(){
    navbar->draw();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glRasterPos2i(0, 0);
    glDrawPixels(buf_w, buf_h, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glDisable(GL_BLEND);
}

void setBufferAlpha(unsigned char val){
    for(int i = 0; i < buf_w; i++){ /* Assign 0 opacity to black pixels */
        for(int j = 0; j < buf_h; j++){
            if(image[i * buf_h * BYTE_PER_PIXEL + j * BYTE_PER_PIXEL] == 0 &&
                image[i * buf_h * BYTE_PER_PIXEL + j * BYTE_PER_PIXEL + 1] == 0 &&
                image[i * buf_h * BYTE_PER_PIXEL + j * BYTE_PER_PIXEL + 2] == 0){
                image[i * buf_h * BYTE_PER_PIXEL + j * BYTE_PER_PIXEL + 3] = 0;
            }
            else{
                image[i * buf_h * BYTE_PER_PIXEL + j * BYTE_PER_PIXEL + 3] = val;
            }
        }
    }
}

void reshape_func(int new_w, int new_h){
    // std::cout << "reshape" << std::endl;
    wnd_height = new_h;
    wnd_width = new_w;

    buf_w = wnd_width, buf_h = wnd_height - navbar->getHeight();

    if(image) delete image;
    image = new unsigned char[wnd_width * (wnd_height - navbar->getHeight()) * BYTE_PER_PIXEL];


    navbar->reshape(0, wnd_height, wnd_width, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (double)wnd_width, 0.0, (double)wnd_height);
    glViewport(0, 0, wnd_width, wnd_height);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void keyboard_func(unsigned char key, int x, int y){
    if(!buffer.empty()){
        if(obj_type == OBJ_TYPE::TEXT && !buffer.back()->isFinish()){
            buffer.back()->setColor(RGBColor::obj_col);
            buffer.back()->addChar(key);
        }
    }
    glutPostRedisplay();
}

void mouse_func(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        isAttach = navbar->attach(x, wnd_height - y);
        if(!isAttach && !navbar->isMouseOn(x, wnd_height - y)){
            if((buffer.empty() || buffer.back()->isFinish())){
                // std::cout << "add" << std::endl;
                switch(obj_type){
                    case OBJ_TYPE::MY_POINT:
                        buffer.push_back(new Point());
                        break;
                    case OBJ_TYPE::LINE:
                        buffer.push_back(new Line());
                        break;
                    case OBJ_TYPE::POLYGON:
                        buffer.push_back(new Poly());
                        break;
                    case OBJ_TYPE::CIRCLE:
                        buffer.push_back(new Circle());
                        break;
                    case OBJ_TYPE::CURVE:
                        buffer.push_back(new Curve());
                        break;
                    case OBJ_TYPE::TEXT:
                        buffer.push_back(new Label());
                        break;
                    default:
                        break;
                }
            }
            if(!buffer.empty()){
                buffer.back()->setFillMode(fill_mode);
                buffer.back()->setWidth(adjuster->getVal());
                buffer.back()->setColor(RGBColor::obj_col);
            }
            if(!buffer.empty() && !navbar->isMouseOn(x, wnd_height - y)){
                buffer.back()->click(x, wnd_height - y);
            }
        }
    }
    Pointer::mouse_ptr->setPos(x, wnd_height - y);

    glutPostRedisplay();
}

void motion_func(int x, int y){
    if(!buffer.empty() && !isAttach &&
       !navbar->isMouseOn(x, wnd_height - y)){
        if(obj_type == OBJ_TYPE::LINE) buffer.back()->drag(x, wnd_height - y);
        else if(obj_type == OBJ_TYPE::CURVE) buffer.back()->drag(x, wnd_height - y);
        else if(obj_type == OBJ_TYPE::CIRCLE) buffer.back()->drag(x, wnd_height - y);
    }
    Pointer::mouse_ptr->setPos(x, wnd_height - y);
    navbar->drag(x, wnd_height - y);
    glutPostRedisplay();
}

void passive_motion_func(int x, int y){
    if(!buffer.empty() && !isAttach &&
       obj_type == OBJ_TYPE::POLYGON &&
       !navbar->isMouseOn(x, wnd_height - y)){
        if(!buffer.back()->isFinish()) buffer.back()->drag(x, wnd_height - y);
    }
    Pointer::mouse_ptr->setPos(x, wnd_height - y);
    navbar->hover(x, wnd_height - y);
    glutPostRedisplay();
}

void display_func(void){
    glClear(GL_COLOR_BUFFER_BIT);

    if(isBlend) drawBackBuffer();
    drawGrid();
    drawObject();
    navbar->draw();
    drawPalette();
    Pointer::mouse_ptr->draw();

    glFlush();
}

void color_func(int value){
  switch (value){
    case WHITE:
        RGBColor::obj_col.setAll(255, 255, 255);
        break;
    case RED:
        RGBColor::obj_col.setAll(255, 0, 0);
        break;
    case GREEN:
        RGBColor::obj_col.setAll(0, 255, 0);
        break;
    case BLUE:
        RGBColor::obj_col.setAll(0, 0, 255);
        break;
    default:
        break;
  }
}

/*------------------------------------------------------------
 * Callback function for top menu.
 */
void file_func(int value){
    if (value == MY_QUIT) exit(0);
    else if (value == MY_CLEAR){
        isBlend = 0;
        init_wnd();
    }
    else if (value == MY_SAVE){ /* Save current window */
        glClear(GL_COLOR_BUFFER_BIT);

        if(isBlend) drawBackBuffer();
        drawObject();

        glReadPixels(0, 0, buf_w, buf_h, GL_RGBA, GL_UNSIGNED_BYTE, image);
        setBufferAlpha(127);

        back_buffer = buffer;
    }
    else if (value == MY_LOAD) { /* Restore the saved image */
        for(Object *obj:buffer) back_buffer.push_back(obj);
        buffer = back_buffer;
    }
    else if (value == MY_BLEND) { /* Blending current image with the saved image */
        isBlend = 1;
    }
    glutPostRedisplay();
}

void size_func(int value){
    if(value == 1) adjuster->increase();
    else adjuster->decrease();
    glutPostRedisplay();
}

/*---------------------------------------------------------------
 * Callback function for top menu. Do nothing.
 */
void top_menu_func(int value){}

/*-------------------------------------------------------------
 * Callback Func for type_m, define drawing object
 */
void draw_type(int value){
  obj_type = value;
}


void setEntry(){
    int x = 0, y = wnd_height;
    buf_w = wnd_width, buf_h = wnd_height - navbar->getHeight();

    Menu *file_m = new Menu(x, y, "File");
    x += file_m->getWidth();
    Menu *type_m = new Menu(x, y, "Type");
    x += type_m->getWidth();
    Menu *fill_m = new Menu(x, y, "Fill Mode");
    x += fill_m->getWidth();
    adjuster = new Adjuster(x, y, "Size: 2px");
    y -= fill_m->getHeight();
    // std::cout << x << std::endl;
    x = 0;
    Slider *red_slider = new Slider(x, y, "red:", [](Slider *slider) -> void {
        RGBColor::obj_col.setR(slider->getVal());
    });
    x += red_slider->getWidth();
    Slider *green_slider = new Slider(x, y, "green:",[](Slider *slider) -> void {
        RGBColor::obj_col.setG(slider->getVal());
    });
    x += green_slider->getWidth();
    Slider *blue_slider = new Slider(x, y, "blue:", [](Slider *slider) -> void {
        RGBColor::obj_col.setB(slider->getVal());
    });
    x += blue_slider->getWidth();
    // std::cout << x << std::endl;
    
    
    type_m->setColor(50, 50, 50);
    type_m->addMenuEntry("Point", []() -> void {
        obj_type = OBJ_TYPE::MY_POINT;
    });
    type_m->addMenuEntry("Line", []() -> void {
        obj_type = OBJ_TYPE::LINE;
    });
    type_m->addMenuEntry("Polygon", []() -> void {
        obj_type = OBJ_TYPE::POLYGON;
    });
    type_m->addMenuEntry("Circle", []() -> void {
        obj_type = OBJ_TYPE::CIRCLE;
    });
    type_m->addMenuEntry("Curve", []() -> void {
        obj_type = OBJ_TYPE::CURVE;
    });
    type_m->addMenuEntry("Text", []() -> void {
        obj_type = OBJ_TYPE::TEXT;
    });

    fill_m->setColor(50, 50, 50);
    fill_m->addMenuEntry("Fill", []() -> void {
        fill_mode = GL_FILL;
    });
    fill_m->addMenuEntry("No fill", []() -> void {
        fill_mode = GL_LINE;
    });

    image = new unsigned char[wnd_width * (wnd_height - navbar->getHeight()) * BYTE_PER_PIXEL];

    file_m->setColor(50, 50, 50);
    file_m->addMenuEntry("export", []() -> void {
        glClear(GL_COLOR_BUFFER_BIT);

        if(isBlend) drawBackBuffer();
        drawObject();

        glReadPixels(0, 0, buf_w, buf_h, GL_RGBA, GL_UNSIGNED_BYTE, image);
        std::cout << buf_w << " " << buf_h << std::endl;
        ImageHandler::img_hdr.readBuffer(image, buf_w, buf_h);
        ImageHandler::img_hdr.outputImage("picture.bmp");

        glutPostRedisplay();
    });
    file_m->addMenuEntry("save", []() -> void {
        glClear(GL_COLOR_BUFFER_BIT);

        if(isBlend) drawBackBuffer();
        drawObject();

        glReadPixels(0, 0, buf_w, buf_h, GL_RGBA, GL_UNSIGNED_BYTE, image);
        setBufferAlpha(127);

        back_buffer = buffer;
    });
    file_m->addMenuEntry("load", []() -> void {
        for(Object *obj:buffer) back_buffer.push_back(obj);
        buffer = back_buffer;
    });
    file_m->addMenuEntry("blend", []() -> void {
        isBlend = 1;
    });
    file_m->addMenuEntry("clear", []() -> void {
        isBlend = 0;
        init_wnd();
    });
    file_m->addMenuEntry("quit", []() -> void {
        exit(0);
    });

    navbar->setColor(50, 50, 50);
    navbar->addEntry(red_slider);
    navbar->addEntry(green_slider);
    navbar->addEntry(blue_slider);
    navbar->addEntry(adjuster);
    navbar->addEntry(type_m);
    navbar->addEntry(fill_m);
    navbar->addEntry(file_m);

}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(wnd_width, wnd_height);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    init_func();

    glutCreateWindow("Drawing Panel");

    glutDisplayFunc(display_func);
    glutReshapeFunc(reshape_func);

    glutKeyboardFunc(keyboard_func);
    glutMouseFunc(mouse_func);
    glutMotionFunc(motion_func);
    glutPassiveMotionFunc(passive_motion_func);

    color_menu = glutCreateMenu(color_func); /* Create color-menu */
    glutAddMenuEntry("white", WHITE);
    glutAddMenuEntry("red", RED);
    glutAddMenuEntry("green", GREEN);
    glutAddMenuEntry("blue", BLUE);

    file_menu = glutCreateMenu(file_func); /* Create another menu, file-menu */
    glutAddMenuEntry("save", MY_SAVE);
    glutAddMenuEntry("load", MY_LOAD);
    glutAddMenuEntry("blend", MY_BLEND);
    glutAddMenuEntry("clear", MY_CLEAR);
    glutAddMenuEntry("quit", MY_QUIT);

    type_menu = glutCreateMenu(draw_type); /* Create draw-type menu */
    glutAddMenuEntry("Point", OBJ_TYPE::MY_POINT);
    glutAddMenuEntry("Line", OBJ_TYPE::LINE);
    glutAddMenuEntry("Poly", OBJ_TYPE::POLYGON);
    glutAddMenuEntry("Curve", OBJ_TYPE::CURVE);
    glutAddMenuEntry("Circle", OBJ_TYPE::CIRCLE);

    size_menu = glutCreateMenu(size_func);
    glutAddMenuEntry("Bigger", 1);
    glutAddMenuEntry("Smaller", 2);

    top_menu = glutCreateMenu(top_menu_func); /* Create top menu */
    glutAddSubMenu("colors", color_menu);     /* add color-menu as a sub-menu */
    glutAddSubMenu("type", type_menu);
    glutAddSubMenu("Size", size_menu);
    glutAddSubMenu("file", file_menu);    /* add file-menu as a sub-menu */
    glutAttachMenu(GLUT_RIGHT_BUTTON); /* associate top-menu with right but*/


    setEntry();

    glutMainLoop();
    return 0;
}