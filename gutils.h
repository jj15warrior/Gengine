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


using namespace std;

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
            glRasterPos2f(this->xpos, this->ypos);
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
        color = RGBA();
    }

    void f_render(){
        if(this->color.a != 0) {
            glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
            glBegin(GL_QUADS);
            glVertex2f(SCREEN_PROP_CONST * this->x1 / 1000.0, this->y1 / 1000.0);
            glVertex2f(SCREEN_PROP_CONST * this->x2 / 1000.0, this->y2 / 1000.0);
            glVertex2f(SCREEN_PROP_CONST * this->x3 / 1000.0, this->y3 / 1000.0);
            glVertex2f(SCREEN_PROP_CONST * this->x4 / 1000.0, this->y4 / 1000.0);
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
                pair<float, float> intersect = line_line_intersection(
                        vertices[i].first, vertices[i].second,
                        vertices[(i + 1) % vertices.size()].first, vertices[(i + 1) % vertices.size()].second,
                        other.vertices[j].first, other.vertices[j].second,
                        other.vertices[(j + 1) % other.vertices.size()].first,
                        other.vertices[(j + 1) % other.vertices.size()].second
                );
                cout << intersect.first << " " << intersect.second << endl;
            }
        }
        return false;
    }

    G_colider(G_bmp bmp){
        this->vertices.push_back(make_pair(bmp.ypos, bmp.ypos)); //bottom left
        this->vertices.push_back(make_pair(bmp.ypos, bmp.ypos+bmp.h));
        this->vertices.push_back(make_pair(bmp.ypos+bmp.w, bmp.ypos+bmp.h));
        this->vertices.push_back(make_pair(bmp.ypos+bmp.w, bmp.ypos));
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
        this->vertices.push_back(make_pair(quad.x1, quad.y1));
        this->vertices.push_back(make_pair(quad.x1, quad.y2));
        this->vertices.push_back(make_pair(quad.x2, quad.y2));
        this->vertices.push_back(make_pair(quad.x2, quad.y1));
    }
    G_colider(G_triangle triangle){
        this->vertices.push_back(make_pair(triangle.x1, triangle.y1));
        this->vertices.push_back(make_pair(triangle.x2, triangle.y2));
        this->vertices.push_back(make_pair(triangle.x3, triangle.y3));
    }
    G_colider(G_line line){
        this->vertices.push_back(make_pair(line.x1, line.y1));
        this->vertices.push_back(make_pair(line.x2, line.y2));
    }
    G_colider(G_Button button){
        this->vertices.push_back(make_pair(button.bmp.xpos, button.bmp.ypos));
        this->vertices.push_back(make_pair(button.bmp.xpos, button.bmp.ypos+button.bmp.h));
        this->vertices.push_back(make_pair(button.bmp.xpos+button.bmp.w, button.bmp.ypos+button.bmp.h));
        this->vertices.push_back(make_pair(button.bmp.xpos+button.bmp.w, button.bmp.ypos));
    }
    G_colider(G_text text){
        float w = glutBitmapLength(text.font, (const unsigned char*)text.text.c_str());
        float h = glutBitmapWidth(text.font, 'A');
        this->vertices.push_back(make_pair(text.xpos, text.ypos));
        this->vertices.push_back(make_pair(text.xpos+w, text.ypos));
        this->vertices.push_back(make_pair(text.xpos+w, text.ypos+h));
        this->vertices.push_back(make_pair(text.xpos, text.ypos+h));
    }
    G_colider(){
        this->vertices = vector<pair<float, float>>();
    }

    bool colidesWith(G_colider other){
        for (int i = 0; i < vertices.size(); i++) {
            for (int j = 0; j < other.vertices.size(); j++) {
                pair<float, float> intersect = line_line_intersection(
                        vertices[i].first, vertices[i].second,
                        vertices[(i + 1) % vertices.size()].first, vertices[(i + 1) % vertices.size()].second,
                        other.vertices[j].first, other.vertices[j].second,
                        other.vertices[(j + 1) % other.vertices.size()].first,
                        other.vertices[(j + 1) % other.vertices.size()].second
                );
                if(intersect.first != -1 && intersect.second != -1){
                    return true;
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

    G_physic(G_colider colider){
        this->colider = colider;
        this->dx = 0;
        this->dy = 0;
        this->rot = 0;
        this->mass = 1;
        this->friction = 0.1;
        this->gravity = 0.1;
    }

    G_physic() {
        this->colider = G_colider();
        this->dx = 0;
        this->dy = 0;
        this->rot = 0;
        this->mass = 1;
        this->friction = 0.1;
        this->gravity = 1;
    }

    void update(){

    }

    void applyForce(float x, float y){
        this->dx += x/this->mass;
        this->dy += y/this->mass;
    }

    bool colidesWith(G_physic other){
        return this->colider.colidesWith(other.colider);
    }

    void setVelocity(float x, float y){
        this->dx = x;
        this->dy = y;
    }
    void rotate(float angle){
        this->rot += angle;
        this->colider.rotate(angle);
    }
};


struct Gobj{
    string selected;
    G_bmp bmp;
    G_text text;
    G_Button button;
    G_triangle triangle;
    G_quad quad;
    G_line line;
    G_circle circle;
    G_physic physic;

    Gobj(G_bmp bmp){
        this->selected = "bmp";
        this->bmp = bmp;
        this->physic = G_physic(G_colider(bmp));
    }
    Gobj(G_text text){
        this->selected = "text";
        this->text = text;
        this->physic = G_physic(G_colider(text));
    }
    Gobj(G_Button button){
        this->selected = "button";
        this->button = button;
        this->physic = G_physic(G_colider(button));
    }
    Gobj(G_triangle triangle){
        this->selected = "triangle";
        this->triangle = triangle;
        this->physic = G_physic(G_colider(triangle));
    }
    Gobj(G_quad quad){
        this->selected = "quad";
        this->quad = quad;
        this->physic = G_physic(G_colider(quad));
    }
    Gobj(G_line line){
        this->selected = "line";
        this->line = line;
        this->physic = G_physic(G_colider(line));
    }
    Gobj(G_circle circle){
        this->selected = "circle";
        this->circle = circle;
        this->physic = G_physic(G_colider(circle));
    }

    Gobj(){
        this->selected = "none";
    }

    void f_render(){
        if(this->selected == "bmp"){
            this->bmp.f_render();
        }
        if(this->selected == "text"){
            this->text.f_render();
        }
        if(this->selected == "button"){
            this->button.f_render();
        }
        if(this->selected == "triangle"){
            this->triangle.f_render();
        }
        if(this->selected == "quad"){
            this->quad.f_render();
        }
        if(this->selected == "line"){
            this->line.f_render();
        }
        if(this->selected == "circle"){
            this->circle.f_render();
        }
    }

    void clear(){
        this->selected = "none";
        bmp = G_bmp();
        text = G_text();
        button = G_Button();
        triangle = G_triangle();
        quad = G_quad();
        line = G_line();
        circle = G_circle();
    }

    void move(float xm, float ym){

        if(this->selected == "bmp"){
            this->bmp.xpos += xm;
            this->bmp.ypos += ym;
        }
        if(this->selected == "text"){
            this->text.xpos += xm;
            this->text.ypos += ym;
        }
        if(this->selected == "button"){
            this->button.bmp.xpos += xm;
            this->button.bmp.xpos += ym;
        }
        if(this->selected == "triangle"){
            this->triangle.x1 += xm;
            this->triangle.y1 += ym;
            this->triangle.x2 += xm;
            this->triangle.y2 += ym;
            this->triangle.x3 += xm;
            this->triangle.y3 += ym;
        }
        if(this->selected == "quad"){
            this->quad.x1 += xm;
            this->quad.y1 += ym;
            this->quad.x2 += xm;
            this->quad.y2 += ym;
            this->quad.x3 += xm;
            this->quad.y3 += ym;
            this->quad.x4 += xm;
            this->quad.y4 += ym;
        }
        if(this->selected == "line"){
            this->line.x1 += xm;
            this->line.y1 += ym;
            this->line.x2 += xm;
            this->line.y2 += ym;
        }
        if(this->selected == "circle"){
            this->circle.x += xm;
            this->circle.y += ym;
        }
        this->physic.colider.move(xm, ym);
    }

    void reColour(RGBA col){
        if(this->selected == "bmp"){
            cerr << "recolouring bmp not supported" << endl;
        }
        if(this->selected == "text"){
            this->text.color = col;
        }
        if(this->selected == "button"){
            cerr << "button graphics are the type bmp, which can not be recoloured. try reassigning the button's bmp" << endl;
        }
        if(this->selected == "triangle"){
            this->triangle.color = col;
        }
        if(this->selected == "quad"){
            this->quad.color = col;
        }
        if(this->selected == "line"){
            this->line.color = col;
        }
        if(this->selected == "circle"){
            this->circle.color = col;
        }
    }
};


extern vector <Gobj> gobjs;
extern void init();

extern void setGobjsSize(int size);
extern int CCscale;
extern int width, height;
extern int old_width, old_height;
extern chrono::time_point<chrono::steady_clock> start;
extern chrono::time_point<chrono::steady_clock> endtime;

extern float scale;
extern double deltatime;
extern float designated_Fps;
extern float designated_Tps;
extern chrono::time_point<chrono::steady_clock> tick_timer; //timer for game ticks
extern chrono::time_point<chrono::steady_clock> custimer; //timer for couts

extern bool on;

extern void calcDeltaTime();
extern void timetick();

#endif //FMS_2_GUTILS_H
