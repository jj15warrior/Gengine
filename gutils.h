//
// Created by jj15 on 1/29/23.
//
#pragma once
#ifndef FMS_2_GUTILS_H
#define FMS_2_GUTILS_H
#include "stdafx.h"
#include "Game.h"

#define SCREEN_PROP_CONST 0.5625
#define DEG2RAD 0.0174532925
#define NPOS 99999999.0f

using namespace std;

struct Gobj;
extern vector <Gobj> gobjs;
extern double deltatime;
extern void init();
extern void setGobjsSize(int size);
extern int width, height;
extern chrono::time_point<chrono::steady_clock> start;
extern float designated_Fps;
extern float designated_Tps;
extern chrono::time_point<chrono::steady_clock> tick_timer; //timer for game ticks
extern chrono::time_point<chrono::steady_clock> custimer; //timer for couts
extern chrono::time_point<chrono::steady_clock> endtime;

extern bool on;

extern void calcDeltaTime();
extern void timetick();


extern int fps;

struct RGBA{
    RGBA(float r, float g, float b, float a){
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    RGBA() {
        r = 0;
        g = 0;
        b = 0;
        a = 1;
    }

    float r, g, b, a;
    bool operator==(RGBA in)
    {
        if(a == in.a && r == in.r && g == in.g && b == in.b){
            return true;
        }else{
            return false;
        }
    }
    bool operator!=(RGBA in)
    {
        if(a != in.a || r != in.r || g != in.g || b != in.b){
            return true;
        }else{
            return false;
        }
    }

};
struct G_bmp {
    float xpos, ypos, w, h;
    vector <vector<RGBA>> pixels;

    G_bmp(float xpos, float ypos, float w, float h, vector<vector<RGBA>> pixels){
        this->xpos = xpos;
        this->ypos = ypos;
        this->w = w;
        this->h = h;
        this->pixels = pixels;
    }

    G_bmp() {
        xpos = 0;
        ypos = 0;
        w = 0;
        h = 0;
        pixels = {};
    }
    void f_render(){

        float xpos = (this->xpos / 1000.0)*SCREEN_PROP_CONST;
        float ypos = (this->ypos / 1000.0);
        float w = this->w / 1000.0;
        float h = this->h / 1000.0;
        w *= SCREEN_PROP_CONST;
        float xh = (h / this->pixels.size());
        float xw = (w / this->pixels[0].size());
        for (int y = 0; y < this->pixels.size(); y++) {
            for (int x = 0; x < this->pixels[y].size(); x++) {
                if (this->pixels[y][x].a != 0) {
                    glColor4f(this->pixels[y][x].r, this->pixels[y][x].g, this->pixels[y][x].b, this->pixels[y][x].a);
                    glBegin(GL_QUADS);
                    glVertex2f(xpos + xw * x, ypos + xh * y);
                    glVertex2f(xpos + xw * x, ypos + xh * (y + 1));
                    glVertex2f(xpos + xw * (x + 1), ypos + xh * (y + 1));
                    glVertex2f(xpos + xw * (x + 1), ypos + xh * y);
                    glEnd();
                }
            }
        }
    }
};
struct G_text{
    float xpos, ypos;
    string text;
    RGBA color;
    void *font;

    G_text(float xpos, float ypos, string text, RGBA color, void* f){
        this->xpos = xpos;
        this->ypos = ypos;
        this->font = f;
        this->text = text;
        this->color = color;
    }

    G_text() {
        xpos = 0;
        ypos = 0;
        text = "";
        color = RGBA();
        font = nullptr;
    }
    void f_render(){
        if(this->font == nullptr){
            this->font = GLUT_BITMAP_HELVETICA_18;
        }
        if(this->color.a != 0) {
            glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
            glRasterPos2f(this->xpos/1000.0, this->ypos/1000.0);
            for (char c: this->text) {
                glutBitmapCharacter(this->font, c);
            }
        }
    }
};
struct G_Button{
    G_bmp bmp;
    void (*callback)(float x, float y, int btn);

    G_Button(G_bmp b, void (*c)(float x, float y, int btn)){
        this->bmp = b;
        this->callback = *c;
    }

    G_Button() {
        bmp = G_bmp();
        callback = nullptr;
    }

    void f_render(){
        this->bmp.f_render();
    }

};
struct G_triangle{
    float x1, y1, x2, y2, x3, y3;
    RGBA color;

    G_triangle(float x1, float y1, float x2, float y2, float x3, float y3, RGBA color){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x3 = x3;
        this->y3 = y3;
        this->color = color;
    }

    G_triangle() {
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
        x3 = 0;
        y3 = 0;
        color = RGBA();
    }
    void f_render(){
        if(this->color.a != 0) {
            glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
            glBegin(GL_TRIANGLES);
            glVertex2f(SCREEN_PROP_CONST * this->x1 / 1000.0, this->y1 / 1000.0);
            glVertex2f(SCREEN_PROP_CONST * this->x2 / 1000.0, this->y2 / 1000.0);
            glVertex2f(SCREEN_PROP_CONST * this->x3 / 1000.0, this->y3 / 1000.0);
            glEnd();
        }
    }
};
struct G_quad{
    float x1, y1, x2, y2,x3, y3, x4, y4;
    float rot;
    RGBA color;

    G_quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, RGBA color){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x3 = x3;
        this->y3 = y3;
        this->x4 = x4;
        this->y4 = y4;
        this->rot = 0;
        this->color = color;
    }

    G_quad() {
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
        x3 = 0;
        y3 = 0;
        x4 = 0;
        y4 = 0;
        rot = 0;
        color = RGBA();
    }
    void rotate(float r){
        this->rot = r;

    }
    void f_render(){
        if(this->color.a != 0) {
            glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
            glBegin(GL_QUADS);
            glVertex2f((SCREEN_PROP_CONST*x1/1000.0),y1/1000.0);
            glVertex2f((SCREEN_PROP_CONST*x2/1000.0),y2/1000.0);
            glVertex2f((SCREEN_PROP_CONST*x3/1000.0),y3/1000.0);
            glVertex2f((SCREEN_PROP_CONST*x4/1000.0),y4/1000.0);
            glEnd();

        }
    }


};
struct G_line{
    float x1, y1, x2, y2;
    RGBA color;

    G_line(float x1, float y1, float x2, float y2, RGBA color){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->color = color;
    }

    G_line() {
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
        color = RGBA();
    }
    void f_render(){
        if(this->color.a != 0) {
            glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
            glBegin(GL_LINES);
            glVertex2f(SCREEN_PROP_CONST * this->x1 / 1000.0, this->y1 / 1000.0);
            glVertex2f(SCREEN_PROP_CONST * this->x2 / 1000.0, this->y2 / 1000.0);
            glEnd();
        }
    }
};
struct G_circle{
    float x, y, r;
    RGBA color;

    G_circle(float x, float y, float r, RGBA color){
        this->x = x;
        this->y = y;
        this->r = r;
        this->color = color;
    }

    G_circle() {
        x = 0;
        y = 0;
        r = 0;
        color = RGBA();
    }
    void f_render(){
        if(this->color.a != 0) {
            glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
            glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i < 360; i++) {
                float degInRad = i * DEG2RAD;
                glVertex2f(SCREEN_PROP_CONST * (this->x + cos(degInRad) * this->r) / 1000.0,
                           (this->y + sin(degInRad) * this->r) / 1000.0);
            }
            glEnd();
        }
    }
};

extern void grc_debug(float x1,float x2);

extern pair<float,float> line_line_intersection(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);


struct G_colider {
    vector<pair<float, float>> vertices;
    void move(float x, float y) {
        for (int i = 0; i < vertices.size(); i++) {
            vertices[i].first += x;
            vertices[i].second += y;
        }
    }

    bool colides(G_colider other) {
        for (int i = 0; i < vertices.size(); i++) {
            for (int j = 0; j < other.vertices.size(); j++) {

            }
        }
        return false;
    }

    G_colider(G_bmp bmp){
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*bmp.xpos, bmp.ypos)); //bottom left
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*bmp.xpos, bmp.ypos+bmp.h));
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*bmp.xpos+bmp.w, bmp.ypos+bmp.h));
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*bmp.xpos+bmp.w, bmp.ypos));
    }
    G_colider(G_circle circle){
        for (int i = 0; i < 360; i++) {
            float angle = i * 3.14159265 / 180;
            float x = cos(angle) * circle.r + circle.x;
            float y = sin(angle) * circle.r + circle.y;
            this->vertices.push_back(make_pair(x, y));
        }
    }
    G_colider(G_quad quad){
        this->vertices.push_back(make_pair(quad.x1*SCREEN_PROP_CONST, quad.y1));
        this->vertices.push_back(make_pair(quad.x2*SCREEN_PROP_CONST, quad.y2));
        this->vertices.push_back(make_pair(quad.x3*SCREEN_PROP_CONST, quad.y3));
        this->vertices.push_back(make_pair(quad.x4*SCREEN_PROP_CONST, quad.y4));
    }
    G_colider(G_triangle triangle){
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*triangle.x1, triangle.y1));
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*triangle.x2, triangle.y2));
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*triangle.x3, triangle.y3));
    }
    G_colider(G_line line){
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*line.x1, line.y1));
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*line.x2, line.y2));
    }
    G_colider(G_Button button){
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*button.bmp.xpos, button.bmp.ypos));
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*button.bmp.xpos, button.bmp.ypos+button.bmp.h));
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*button.bmp.xpos+button.bmp.w, button.bmp.ypos+button.bmp.h));
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*button.bmp.xpos+button.bmp.w, button.bmp.ypos));
    }
    G_colider(G_text text){
        float w = glutBitmapLength(text.font, (const unsigned char*)text.text.c_str());
        float h = glutBitmapWidth(text.font, 'A');
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*text.xpos, text.ypos));
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*text.xpos+w, text.ypos));
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*text.xpos+w, text.ypos+h));
        this->vertices.push_back(make_pair(SCREEN_PROP_CONST*text.xpos, text.ypos+h));
    }
    G_colider(){
        this->vertices = vector<pair<float, float>>();
    }

    bool colidesWith(G_colider other){
        for(int i = 0; i < vertices.size(); i++){
            for(int j = 0; j < other.vertices.size(); j++){
                if(j+1 <= other.vertices.size() && i+1 <= vertices.size()) {
                    if(vertices!=other.vertices) {
                        cout << vertices[i].first << " " << vertices[i].second << " " << vertices[i + 1].first << " "
                             << vertices[i + 1].second << "\n" << other.vertices[j].first << " "
                             << other.vertices[j].second
                             << " " << other.vertices[j + 1].first << " " << other.vertices[j + 1].second << endl;
                        pair<float, float> intersection = line_line_intersection(
                                vertices[i].first, vertices[i].second,
                                vertices[i + 1].first, vertices[i + 1].second,
                                other.vertices[j].first, other.vertices[j].second,
                                other.vertices[j + 1].first, other.vertices[j + 1].second
                        );
                        if (intersection != make_pair(NPOS, NPOS)) {
                            grc_debug(intersection.first, intersection.second);

                        }
                    }
                }
            }
        }
        return false;
    }
    void rotate(float angle){
        for (int i = 0; i < vertices.size(); i++) {
            float x = vertices[i].first;
            float y = vertices[i].second;
            vertices[i].first = x*cos(angle) - y*sin(angle);
            vertices[i].second = x*sin(angle) + y*cos(angle);
        }
    }
};


extern void onSpecialUp(int key, int x, int y);
extern void onPassiveMouse(int x, int y);
extern void onSpecial(int key, int x, int y);
extern void onMouse(int button, int state, int x, int y);
extern void onKeyboard(unsigned char key, int x, int y);
extern void onKeyboardUp(unsigned char key, int x, int y);

extern float mousey, mousex;

struct G_physic{
    G_colider colider;
    float dx, dy, rot;
    float mass, friction, gravity;
    float ax, ay;

    G_physic(G_colider colider){
        this->colider = colider;
        this->dx = 0;
        this->dy = 0;
        this->ax=0;
        this->ay=0;
        this->rot = 0;
        this->mass = 1;
        this->friction = 0;
        this->gravity = 0;
    }

    G_physic() {
        this->colider = G_colider();
        this->dx = 0;
        this->dy = 0;
        this->ax=0;
        this->ay=0;
        this->rot = 0;
        this->mass = 1;
        this->friction = 0.2;
        this->gravity = 10;
    }
    /*

     a = Δv/Δt
     F= m*a
     F/m = a
     F/m = Δv/Δt
     Δv = F/m * Δt
     Δt = deltatime*(FPS/TPS)*1000
     Δv = F/m * deltatime/1000

     */

    void dxdy_tick(){
        this->dx = this->dx + this->ax - this->dx*this->friction; // dx is taken  by higher struct layers and the obj is moved by dx
        this->dy = this->dy + this->ay - this->dy*this->friction; // same for dy
        ax = 0;
        ay = 0;
        this->dy += this->gravity;
        this->dx/(deltatime*(fps/designated_Tps)*1000);
        this->dy/(deltatime*(fps/designated_Tps)*1000);
        if(dx*dx < 0.000005){
            dx = 0;
        }
        if(dy*dy < 0.000005){
            dy = 0;
        }
    }

    void update();

    void setGravity(float gravity){
        this->gravity = gravity;
    }

    void setFriction(float friction){
        this->friction = friction;
    }

    void applyForce(float x, float y){
        this->ax += x/this->mass;
        this->ay += -y/this->mass;
    }

    bool colidesWith(G_physic other){
        return this->colider.colidesWith(other.colider);
    }

    void setVelocity(float x, float y){
        this->ax = x;
        this->ay = y;
    }
    void rotate(float angle){
        this->rot += angle;
        this->colider.rotate(angle);
    }
};






#include "Gobj.h"
#endif //FMS_2_GUTILS_H
