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
    G_quad q = G_quad(-100/SCREEN_PROP_CONST,300, 100/SCREEN_PROP_CONST, 300, 100/SCREEN_PROP_CONST, 500, -100/SCREEN_PROP_CONST, 500, RGBA(0,1,1,1));
    G_quad q2 = G_quad(-100/SCREEN_PROP_CONST,-300, 100/SCREEN_PROP_CONST, -300, 100/SCREEN_PROP_CONST, -400, -100/SCREEN_PROP_CONST, -400, RGBA(1,0,1,1));

    Gobj qo = Gobj(q);
    qo.physic.applyForce(0, 20);
    qo.physic.friction = 0.02;
    qo.rotate(1);
    gobjs.push_back(qo);
    gobjs.push_back(q2);

}

void tick() {
    gobjs[0].physic_tick();
}

