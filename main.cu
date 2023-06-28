#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <chrono>
#include <thread>

#define DEBUG 1

float deltaTime = 0.0;

using namespace std;

void calcDeltaTime(){
    static auto lastTime = chrono::high_resolution_clock::now();
    auto currentTime = chrono::high_resolution_clock::now();
    deltaTime = chrono::duration_cast<chrono::microseconds>(currentTime - lastTime).count() / 1000000.0;
    lastTime = currentTime;
    cout << "fps: " << 1.0/deltaTime << endl;
}
struct color{
    float r, g, b;
    color(float r, float g, float b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
};
class HelperFunctions{
    public:
        static void drawCircle(float x, float y, float radius, color c = color(1.0, 1.0, 1.0)){
            glBegin(GL_POLYGON);
            for(int i = 0; i < 360; i++){
                float degInRad = i * M_PI / 180;
                glColor3f(c.r, c.g, c.b);
                glVertex2f(cos(degInRad) * radius + x, sin(degInRad) * radius + y);
            }
            glEnd();
        }

};
void resize(int width, int height) {
    if (width > height){
        glViewport((width - height) / 2, 0, height, height);
    }
    else{
        glViewport(0, (height-width)/2, width, width);
    }
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 1.0, 0.0);
    HelperFunctions h = HelperFunctions();
    h.drawCircle(0.0, 0.0, 0.5, color(1.0, 0.0, 0.0));
    glFlush();

    calcDeltaTime();
    glutPostRedisplay();
}

void mouse_move(int x, int y){
    cout << "Mouse move: " << x << ", " << y << endl;
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1600, 900);
    glutCreateWindow("OpenGL - First window demo");
    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouse_move);
    glutReshapeFunc(resize);
    glutMainLoop();
    return 0;
}
