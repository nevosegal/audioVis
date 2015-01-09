//
//  Button.cpp
//  audioVis
//
//  Created by Nevo Segal on 06/01/2015.
//
//

#include "Button.h"

Button::Button(){
    
}

Button::Button(int x, int y, string type){
    this->x = x;
    this->y = y;
    w = 40;
    h = 40;
    this->type = type;
    active = false;
    if(type == "osc"){
        img.loadImage("sine.png");
    }
    else if(type == "song"){
        img.loadImage("player.png");
    }
    else{
        img.loadImage("mic.png");
    }
    
}

void Button::draw(){
    ofNoFill();
    if(active){
        ofSetColor(220);
    }else{
        ofSetColor(80);
    }
    ofRect(x,y,w,h);
    img.draw(x, y, w,h);
}

bool Button::isInBounds(int x, int y){
    if(x > this->x && x < this->x+w && y > this->y && y < this->y + h){
        return true;
    }
    return false;
}



void Button::activate(){
    active = true;
}

void Button::deactivate(){
    active = false;
}

bool Button::isActivated(){
    return active;
}