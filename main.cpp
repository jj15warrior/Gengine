
#include "gutils.h"
using namespace std;

bool st = false;

void render (){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    for(Gobj g: gobjs){
        if(g.selected == "bmp") {
            g.bmp.f_render();
        }else if(g.selected == "triangle"){
            g.triangle.f_render();
        }else if(g.selected == "quad"){
            g.quad.f_render();
        }else if(g.selected == "text") {
            g.text.f_render();
        }else if(g.selected == "line"){
            g.line.f_render();
        }else if(g.selected == "button"){
            g.button.f_render();
        }




    }

    glutSwapBuffers();
}

void display() {

    if (width != glutGet(GLUT_WINDOW_WIDTH) || height != glutGet(GLUT_WINDOW_HEIGHT)) {
        if (!st) {
            width = glutGet(GLUT_WINDOW_WIDTH);
            height = glutGet(GLUT_WINDOW_HEIGHT);
            glViewport(0, 0, width, height);
            st = true;
            return;
        }
    }
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    render();
}

void idle() {
    glClear(GL_COLOR_BUFFER_BIT);
    endtime = chrono::steady_clock::now();
    calcDeltaTime();
    start = chrono::steady_clock::now();
    timetick();
    glutPostRedisplay();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutCreateWindow("OpenGL Setup Test");
    glutFullScreen();

    //glViewport( 0, 0, glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    //sleep(3);
    glutIdleFunc(idle);
    glutMouseFunc(onMouse);
    glutPassiveMotionFunc(onPassiveMouse);
    glutDisplayFunc(display);
    glutKeyboardFunc(onKeyboard);
    glutKeyboardUpFunc(onKeyboardUp);
    glutSpecialFunc(onSpecial);
    glutSpecialUpFunc(onSpecialUp);
    width = glutGet(GLUT_SCREEN_HEIGHT);
    height = glutGet(GLUT_SCREEN_HEIGHT);
    glutMainLoop();
    return 0;
}