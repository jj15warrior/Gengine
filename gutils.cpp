//
// Created by jj15 on 1/29/23.
//
#include "stdafx.h"
#include "Game.h"
#include "gutils.h"
using namespace std;


float axisX = 0, axisY = 0;
float preMouseX = 0, preMouseY = 0;
int width, height;
int old_width, old_height;
std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> endtime = std::chrono::steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> tick_timer = std::chrono::steady_clock::now(); //timer for game ticks
std::chrono::time_point<std::chrono::steady_clock> custimer = std::chrono::steady_clock::now(); //timer for couts

vector<vector<RGBA>> canvas;
float scale=1;
double deltatime;
float designated_Fps=60;
float designated_Tps=1;
int CCscale = 100;

extern bool on;



/*
 * 1. calculates the delta time in milliseconds (ms)
 * 2. prints the fps
 * 3. regulates fps by sleeping
 */

glist gllist = glist();

void calcDeltaTime(){
    chrono::duration<double> elapsed = chrono::steady_clock::now() - start;
    chrono::duration<double> elapsed_for_couts = chrono::steady_clock::now() - custimer; // it resets every second

    if(1/(elapsed.count()) > 60){
        this_thread::sleep_for(chrono::milliseconds((int)ceil((1000/designated_Fps) - ((elapsed.count() * 1000))))); //regulate fps so it is not melting the cpu
    }

    chrono::duration<double> elapsed_for_fps = chrono::steady_clock::now() - start;
    if(elapsed_for_couts.count() > 1){
        cout << "fps: " << (int)(1/elapsed_for_fps.count()) << endl;
        custimer = chrono::steady_clock::now();
    }

    deltatime = elapsed.count()*1000; // delta time in milliseconds (ms)
}


void timetick() {
    chrono::duration<double> tick_elapsed = chrono::steady_clock::now() - tick_timer;
    if(tick_elapsed.count() > 1/designated_Tps) {
        tick();
        tick_timer = chrono::steady_clock::now();
    }
}

pair<int,int> cast_coords_to_canvas(float x, float y) {
    int x1 = (int)(((1+x)/2) * floor(width/scale));
    int y1 = (int)(((1+y)/2) * floor(height/scale));
    return make_pair(x1,y1);
}

pair<float, float> cast_canvas_to_coords(int x, int y) {
    float x1 = (scale / width) * (float) x * 2 - 1;
    float y1 = (scale / height) * (float) y * 2 - 1;
    return make_pair(x1,y1);
}

pair <int, int> cast_CC_to_canvas(int x, int y) {
    int x1 = (float)x/CCscale;
    int y1 = (float)y/CCscale;
    pair <int,int> r = cast_coords_to_canvas(x1,y1);
    return r;
}

void draw_line(int x1, int y1, int x2, int y2, RGBA color) {
    pair <int,int> p1 = cast_CC_to_canvas(x1,y1);
    x1 = p1.first;
    y1 = p1.second;
    p1 = cast_CC_to_canvas(x2,y2);
    x2 = p1.first;
    y2 = p1.second;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        canvas[x1][y1] = RGBA(1,1,1,1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}