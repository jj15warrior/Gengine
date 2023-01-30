//
// Created by jj15 on 1/29/23.
//

#include "stdafx.h"
#include "Game.h"

using namespace std;

void tick() {
    G_bmp test = G_bmp(-1000/SCREEN_PROP_CONST, 900, 2000/SCREEN_PROP_CONST, 60, vector<vector<RGBA>>());
    for (int i = 0; i < 100; i++) {
        vector<RGBA> row = vector<RGBA>();
        for (int j = 0; j < 100; j++) {
            row.push_back(RGBA((i/100.0), 1-(i/100.0), 1, 1));
        }
        test.pixels.push_back(row);
    }
    G_triangle test2 = G_triangle(0, 0, 250, 0, 0, 250, RGBA(1, 0, 1, 1));
    G_triangle test3 = G_triangle(0, 0, -250, 0, 0, -250, RGBA(1, 0, 1, 1));
    G_text test4 = G_text(-1000/SCREEN_PROP_CONST, 970, "Welcome to the CGEngine ", RGBA(1, 1, 1, 1), GLUT_BITMAP_TIMES_ROMAN_24);
    G_triangle test5 = G_triangle(0,0,-250,0,0,250, RGBA(0,1,1,1));
    G_triangle test6 = G_triangle(0,0,0,-250,250,0, RGBA(0,1,1,1));


    gllist.add(test5);
    gllist.add(test6);
    gllist.add(test);
    gllist.add(test2);
    gllist.add(test3);
    gllist.add(test4);

}

