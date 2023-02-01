//
// Created by jj15 on 2/1/23.
//

#ifndef FMS_2_GOBJ_H
#define FMS_2_GOBJ_H
#pragma once
#include "gutils.h"


struct Gobj{
    string selected;
    G_bmp bmp;
    G_text text;
    G_Button button;
    G_triangle triangle;
    G_quad quad;
    G_line line;
    G_circle circle;
    G_physic physic;

    Gobj(G_bmp bmp){
        this->selected = "bmp";
        this->bmp = bmp;
        this->physic = G_physic(G_colider(bmp));
    }
    Gobj(G_text text){
        this->selected = "text";
        this->text = text;
        this->physic = G_physic(G_colider(text));
    }
    Gobj(G_Button button){
        this->selected = "button";
        this->button = button;
        this->physic = G_physic(G_colider(button));
    }
    Gobj(G_triangle triangle){
        this->selected = "triangle";
        this->triangle = triangle;
        this->physic = G_physic(G_colider(triangle));
    }
    Gobj(G_quad quad){
        this->selected = "quad";
        this->quad = quad;
        this->physic = G_physic(G_colider(quad));
    }
    Gobj(G_line line){
        this->selected = "line";
        this->line = line;
        this->physic = G_physic(G_colider(line));
    }
    Gobj(G_circle circle){
        this->selected = "circle";
        this->circle = circle;
        this->physic = G_physic(G_colider(circle));
    }

    Gobj(){
        this->selected = "none";
    }

    void rotate(float angle){
        if(this->selected == "quad"){
            this->quad.rotate(angle);
        }
        /*
        if(this->selected == "triangle"){
            this->triangle.rotate(angle);
        }
        if(this->selected == "line"){
            this->line.rotate(angle);
        }
        if(this->selected == "circle"){
            this->circle.rotate(angle);
        }
        */
        this->physic.rotate(angle);
    }

    void f_render(){
        if(this->selected == "bmp"){
            this->bmp.f_render();
        }
        if(this->selected == "text"){
            this->text.f_render();
        }
        if(this->selected == "button"){
            this->button.f_render();
        }
        if(this->selected == "triangle"){
            this->triangle.f_render();
        }
        if(this->selected == "quad"){
            this->quad.f_render();
        }
        if(this->selected == "line"){
            this->line.f_render();
        }
        if(this->selected == "circle"){
            this->circle.f_render();
        }
    }

    void clear(){
        this->selected = "none";
        bmp = G_bmp();
        text = G_text();
        button = G_Button();
        triangle = G_triangle();
        quad = G_quad();
        line = G_line();
        circle = G_circle();
    }

    void move(float xm, float ym){
        if(this->selected == "bmp"){
            this->bmp.xpos += xm;
            this->bmp.ypos += ym;
        }
        if(this->selected == "text"){
            this->text.xpos += xm;
            this->text.ypos += ym;
        }
        if(this->selected == "button"){
            this->button.bmp.xpos += xm;
            this->button.bmp.xpos += ym;
        }
        if(this->selected == "triangle"){
            this->triangle.x1 += xm;
            this->triangle.y1 += ym;
            this->triangle.x2 += xm;
            this->triangle.y2 += ym;
            this->triangle.x3 += xm;
            this->triangle.y3 += ym;
        }
        if(this->selected == "quad"){
            this->quad.x1 += xm;
            this->quad.y1 += ym;
            this->quad.x2 += xm;
            this->quad.y2 += ym;
            this->quad.x3 += xm;
            this->quad.y3 += ym;
            this->quad.x4 += xm;
            this->quad.y4 += ym;
        }
        if(this->selected == "line"){
            this->line.x1 += xm;
            this->line.y1 += ym;
            this->line.x2 += xm;
            this->line.y2 += ym;
        }
        if(this->selected == "circle"){
            this->circle.x += xm;
            this->circle.y += ym;
        }
        this->physic.colider.move(xm, ym);
    }

    void physic_tick(){
        this->physic.update();
        this->move(this->physic.dx, this->physic.dy*-1);
    }

    void reColour(RGBA col){
        if(this->selected == "bmp"){
            cerr << "recolouring bmp not supported" << endl;
        }
        if(this->selected == "text"){
            this->text.color = col;
        }
        if(this->selected == "button"){
            cerr << "button graphics are the type bmp, which can not be recoloured. try reassigning the button's bmp" << endl;
        }
        if(this->selected == "triangle"){
            this->triangle.color = col;
        }
        if(this->selected == "quad"){
            this->quad.color = col;
        }
        if(this->selected == "line"){
            this->line.color = col;
        }
        if(this->selected == "circle"){
            this->circle.color = col;
        }
    }
};
extern vector <Gobj> gobjs;
#endif //FMS_2_GOBJ_H
