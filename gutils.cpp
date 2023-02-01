//
// Created by jj15 on 1/29/23.
//
#include "stdafx.h"
#include "Game.h"
#include "gutils.h"

using namespace std;


float mousex = 0, mousey = 0;
int width, height;
std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> endtime = std::chrono::steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> tick_timer = std::chrono::steady_clock::now(); //timer for game ticks
std::chrono::time_point<std::chrono::steady_clock> custimer = std::chrono::steady_clock::now(); //timer for couts

vector<vector<RGBA>> canvas;
float scale=1;
double deltatime;
float designated_Fps=60;
float designated_Tps=60;
int CCscale = 100;

extern bool on;

pair <float,float> line_line_intersection(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
    float x = -1;
    if((x1*y2-y1*x2)*(x3-x4)-(x1-x2)*(x3*y4-y3*x4) != 0) {
        x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) /
            ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)); //magic
    }
    float y = -1;
    if(((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4)) != 0) {
        y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) /
            ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)); // ._.
    }
    return make_pair(x, y);
}

void G_physic::update() {
    for(auto g : gobjs){
        if(g.physic.colidesWith(this->colider)){
            cout << "colliding" << endl;
        }
    }
    this->dxdy_tick();
}

Gobj gobj = Gobj();
vector <Gobj> gobjs;

void setGobjsSize(int size) {
    if(gobjs.size()>size){
        gobjs.erase(gobjs.begin()+size, gobjs.end());
    }
    else if(gobjs.size()<size){
        gobjs.resize(size);
    }
}

void calcDeltaTime(){
    /*
         * 1. calculates the delta time in milliseconds (ms)
         * 2. prints the fps
         * 3. regulates fps by sleeping
    */
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