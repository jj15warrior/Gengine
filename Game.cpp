//
// Created by jj15 on 1/29/23.
//

#include "Game.h"

using namespace std;


void onMouse(int, int, int, int){

}

void onSpecialUp(int key, int x, int y){

}

void onPassiveMouse(int x, int y){

}

void onSpecial(int key, int x, int y){

}

void onKeyboard(unsigned char key, int x, int y){

}

void onKeyboardUp(unsigned char key, int x, int y){

}

void init() {
    G_bmp test_bmp = G_bmp(-1000/SCREEN_PROP_CONST, 940, 2000/SCREEN_PROP_CONST, 60, vector<vector<RGBA>>());
    for (int i = 0; i < 100; i++) {
        vector<RGBA> row = vector<RGBA>();
        for (int j = 0; j < 100; j++) {
            row.push_back(RGBA((i/100.0), 1-(i/100.0), 1, 1));
        }
        test_bmp.pixels.push_back(row);
    }
    G_triangle triangle1 = G_triangle(1000/SCREEN_PROP_CONST, -1000, 1000/SCREEN_PROP_CONST, 1000, -100, 0, RGBA(1, 0, 1, 1));
    G_triangle triangle2 = G_triangle(-1000/SCREEN_PROP_CONST, -1000, -1000/SCREEN_PROP_CONST, 1000, 100, 0, RGBA(0, 1, 1, 1));

    Gobj j = Gobj(test_bmp);

    gobjs.push_back(j);
    Gobj k = Gobj(triangle1);
    Gobj l = Gobj(triangle2);

    gobjs.push_back(l);
    gobjs.push_back(k);
    G_circle circle1 = G_circle(0, 0, 100, RGBA(1, 1, 0, 1));
    Gobj m = Gobj(circle1);
    gobjs.push_back(m);
}

void tick() {

}

