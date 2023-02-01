//
// Created by jj15 on 1/29/23.
//

#include "Game.h"

using namespace std;

void onSpecialUp(int key, int x, int y){};
void onPassiveMouse(int x, int y){};
void onSpecial(int key, int x, int y){};
void onMouse(int button, int state, int x, int y){};
void onKeyboard(unsigned char key, int x, int y){};
void onKeyboardUp(unsigned char key, int x, int y){};

G_text Gfps = G_text(-500, 500,"test",  RGBA(1,0,1,1), GLUT_BITMAP_HELVETICA_18);

void init() {
    G_quad q = G_quad(-100,300, 100, 300, 100, 500, -100, 500, RGBA(0,1,1,1));
    Gobj g = Gobj(q);
    gobjs.push_back(g);

    G_quad q2 = G_quad(0,400, 200, 400, 200, 600, 0, 600, RGBA(1,0,0,1));
    Gobj g2 = Gobj(q2);
    g2.physic.gravity = 0;
    g2.physic.friction = 0;
    gobjs.push_back(g2);
    gobjs[1].physic_tick();

}

void tick() {

}