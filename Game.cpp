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


void tick() {
    G_bmp test_bmp = G_bmp(-1000, 940, 2000, 60, vector<vector<RGBA>>());
    for (int i = 0; i < 100; i++) {
        vector<RGBA> row = vector<RGBA>();
        for (int j = 0; j < 100; j++) {
            row.push_back(RGBA((i/100.0), 1-(i/100.0), 1, 1));
        }
        test_bmp.pixels.push_back(row);
    }
    G_triangle triangle1 = G_triangle(0, 0, 1000/SCREEN_PROP_CONST, 562.5/SCREEN_PROP_CONST, 0, 940, RGBA(1, 0, 1, 1));
    G_triangle triangle2 = G_triangle(0, 0, -250, 0, 0, -250, RGBA(0, 1, 1, 1));

    Gobj j = Gobj(test_bmp);
    gobjs.push_back(j);
}

