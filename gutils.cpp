//
// Created by jj15 on 1/29/23.
//
#include "stdafx.h"
#include "Game.h"
#include "gutils.h"

using namespace std;


float mousex = 0, mousey = 0;
int width, height;
int fps = 0;
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

vector <Gobj> gobjs;

void grc_debug(float x, float y){
    G_circle c = G_circle(x,y,10,RGBA(0,1,0,1));
    setGobjsSize(gobjs.size()+1);
    gobjs[gobjs.size()-1] = c;
    cout << x << " " << y << endl;
}

pair <float, float> axb_calc(float x1, float y1, float x2, float y2){
    float a = (y2 - y1)/(x2 - x1);
    float b = y1 - a * x1;
    return make_pair(a,b);
}

pair <float,float> line_line_intersection(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
    if(x1 == x2 && x3 == x4){
        return make_pair(NPOS,NPOS);
    }
    if(y1 == y2 && y3 == y4){
        return make_pair(NPOS,NPOS);
    }
    if(x1>x2){
        swap(x1,x2);
        swap(y1,y2);
    }
    if(x3>x4){
        swap(x3,x4);
        swap(y3,y4);
    }

    if(x1 != x2 && x3 != x4) {
        pair<float, float> axb1 = axb_calc(x1, y1, x2, y2);
        pair<float, float> axb2 = axb_calc(x3, y3, x4, y4);
        float xod = (axb2.second - axb1.second) / (axb2.first - axb1.first);

        if (xod <= x4 && xod <= x2 && xod >= x3 && xod >= x1) {
            return make_pair(xod/SCREEN_PROP_CONST, axb1.first * xod + axb1.second);
        } else {
            return make_pair(NPOS, NPOS);
        }
    }
    else if(x1 == x2 && x3 != x4){
        pair<float, float> axb2 = axb_calc(x3, y3, x4, y4);
        float xod = x1;
        float yod = axb2.first * xod + axb2.second;
        if(yod <= y4 && yod <= y2 && yod >= y3 && yod >= y1 && x1 <= x4 && x1 >= x3){
            return make_pair(xod/SCREEN_PROP_CONST, yod);
        }
        else{
            return make_pair(NPOS,NPOS);
        }
    }
    else if(x1 != x2 && x3 == x4){
        pair<float, float> axb1 = axb_calc(x1, y1, x2, y2);
        float xod = x3;
        float yod = axb1.first * xod + axb1.second;
        if(yod <= y4 && yod <= y2 && yod >= y3 && yod >= y1 && x3 >= x1 && x3 <= x2){
            return make_pair(xod/SCREEN_PROP_CONST, yod);
        }
        else{
            return make_pair(NPOS,NPOS);
        }
    }
    else{
        return make_pair(NPOS,NPOS);
    }
}

void G_physic::update() {
    for(auto g : gobjs){
        if(&g.physic != this){
            if (g.physic.colidesWith(this->colider)) {
                //objects are coliding !!!
            }
        }
    }
    this->dxdy_tick();
}

Gobj gobj = Gobj();

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
    if(elapsed_for_couts.count() > 0.05){
        //cout << "fps: " << (int)(1/elapsed_for_fps.count()) << endl;
        fps = (int)(1/elapsed_for_fps.count());
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