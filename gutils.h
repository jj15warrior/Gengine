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
};

extern float axisX, axisY, preMouseY, preMouseX;

struct G_Button{
    G_bmp bmp;
    void (*callback)(float x, float y, int btn);

    G_Button(G_bmp b, void (*c)(float x, float y, int btn)){
        this->bmp = b;
        this->callback = *c;
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
};

struct glist{
    vector<G_bmp> bmps;
    vector<G_text> texts;
    vector<G_Button> buttons;
    vector<G_triangle> triangles;
    vector<G_quad> quads;

    void add(G_bmp bmp){
        bmps.push_back(bmp);
    }
    void add(G_text text){
        texts.push_back(text);
    }
    void add(G_Button button){
        buttons.push_back(button);
    }
    void add(G_triangle triangle){
        triangles.push_back(triangle);
    }
    void add(G_quad quad){
        quads.push_back(quad);
    }
    void clear(){
        bmps.clear();
        texts.clear();
        buttons.clear();
        triangles.clear();
        quads.clear();
    }
};

extern glist gllist;

extern int CCscale;
extern pair<int,int> cast_coords_to_canvas(float x, float y);
extern pair<float, float> cast_canvas_to_coords(int x, int y);
extern void draw_line(int x1, int y1, int x2, int y2, RGBA color);
extern pair <int,int> cast_CC_to_canvas(int x, int y);
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
