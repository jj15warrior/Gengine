//
// Created by jj15 on 1/29/23.
//
#pragma once
#ifndef FMS_2_GUTILS_H
#define FMS_2_GUTILS_H
#include "stdafx.h"
#include "Game.h"
#define SCREEN_PROP_CONST 0.5625

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

        float xpos = (this->xpos / 1000.0);
        float ypos = (this->ypos / 1000.0);
        float w = this->w / 1000.0;
        float h = this->h / 1000.0;
        float xh = (h / this->pixels.size());
        float xw = (w / this->pixels[0].size());
        for (int y = 0; y < this->pixels.size(); y++) {
            for (int x = 0; x < this->pixels[y].size(); x++) {
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
        glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
        glRasterPos2f(this->xpos, this->ypos);
        for (char c : this->text) {
            glutBitmapCharacter(this->font, c);
        }
    }
};

void onSpecialUp(int key, int x, int y);
void onPassiveMouse(int x, int y);
void onSpecial(int key, int x, int y);
void onMouse(int button, int state, int x, int y);
void onKeyboard(unsigned char key, int x, int y);
void onKeyboardUp(unsigned char key, int x, int y);

extern float mousey, mousex;

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
        glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
        glBegin(GL_TRIANGLES);
        glVertex2f(SCREEN_PROP_CONST * this->x1 / 1000.0, this->y1 / 1000.0);
        glVertex2f(SCREEN_PROP_CONST * this->x2 / 1000.0, this->y2 / 1000.0);
        glVertex2f(SCREEN_PROP_CONST * this->x3 / 1000.0, this->y3 / 1000.0);
        glEnd();
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
};


struct Gobj{
    string selected;
    G_bmp bmp;
    G_text text;
    G_Button button;
    G_triangle triangle;
    G_quad quad;
    G_line line;

    Gobj(G_bmp bmp){
        this->selected = "bmp";
        this->bmp = bmp;
    }
    Gobj(G_text text){
        this->selected = "text";
        this->text = text;
    }
    Gobj(G_Button button){
        this->selected = "button";
        this->button = button;
    }
    Gobj(G_triangle triangle){
        this->selected = "triangle";
        this->triangle = triangle;
    }
    Gobj(G_quad quad){
        this->selected = "quad";
        this->quad = quad;
    }
    Gobj(G_line line){
        this->selected = "line";
        this->line = line;
    }
    Gobj(){
        this->selected = "none";
    }
};

extern vector <Gobj> gobjs;



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
