
#include "gutils.h"
using namespace std;

/*
void regen_canvas() {
    canvas.clear();
    vector<RGBA> row;
    for (int y = 0; y <= height / scale; y++) {
        RGBA pixel = RGBA(1, 0, 0, 1);
        row.push_back(pixel);
    }
    for (int x = 0; x <= width / scale; x++) {
        canvas.push_back(row);
    }
}
*/

bool st = false;

void render (){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    for (auto g: gllist.bmps) {

        float xpos = (g.xpos / 1000.0) * SCREEN_PROP_CONST;
        float ypos = (g.ypos / 1000.0);
        float w = g.w / 1000.0;
        float h = g.h / 1000.0;
        float xh = (h / g.pixels.size());
        float xw = SCREEN_PROP_CONST * (w / g.pixels[0].size());
        for (int y = 0; y < g.pixels.size(); y++) {
            for (int x = 0; x < g.pixels[y].size(); x++) {
                glColor4f(g.pixels[y][x].r, g.pixels[y][x].g, g.pixels[y][x].b, g.pixels[y][x].a);
                glBegin(GL_QUADS);
                glVertex2f(xpos + xw * x, ypos + xh * y);
                glVertex2f(xpos + xw * x, ypos + xh * (y + 1));
                glVertex2f(xpos + xw * (x + 1), ypos + xh * (y + 1));
                glVertex2f(xpos + xw * (x + 1), ypos + xh * y);
                glEnd();
            }
        }
    }
    for (auto g: gllist.triangles) {
        glColor4f(g.color.r, g.color.g, g.color.b, g.color.a);
        glBegin(GL_TRIANGLES);
            glVertex2f(SCREEN_PROP_CONST * g.x1 / 1000.0, g.y1 / 1000.0);
            glVertex2f(SCREEN_PROP_CONST * g.x2 / 1000.0, g.y2 / 1000.0);
            glVertex2f(SCREEN_PROP_CONST * g.x3 / 1000.0, g.y3 / 1000.0);
        glEnd();
    }
    for (auto g: gllist.texts) {
        glColor4f(g.color.r, g.color.g, g.color.b, g.color.a);
        glRasterPos2f(SCREEN_PROP_CONST * g.xpos / 1000.0, g.ypos / 1000.0);
        for (char c: g.text) {
            glutBitmapCharacter(g.font, c);
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

void onLeftButton(int x, int y){
    axisX += (y - preMouseY);
    axisY += (x - preMouseX);
}

void onRightButton(int x, int y){
    cout << x << endl;
}

void onMouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN){
        if(button == GLUT_RIGHT_BUTTON)
            glutMotionFunc(onRightButton);
        else if(button == GLUT_LEFT_BUTTON)
            glutMotionFunc(onLeftButton);
    }
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
    glutDisplayFunc(display);

    width = glutGet(GLUT_SCREEN_HEIGHT);
    height = glutGet(GLUT_SCREEN_HEIGHT);
    glutMainLoop();
    return 0;
}