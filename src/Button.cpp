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

    //initial stuff
    this->x = x;
    this->y = y;
    w = 40;
    h = 40;
    this->type = type;
    active = false;
    
    //choosing the right image according to the button type.
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

//drawing the button.
void Button::draw(){
    ofNoFill();
    //checking if its active or not.
    if(active){
        ofSetColor(220);
    }
    else{
        ofSetColor(80);
    }
    ofRect(x,y,w,h);
    img.draw(x,y,w,h);
}


//checking if the button is hovered.
bool Button::isInBounds(int x, int y){
    if(x > this->x && x < this->x+w && y > this->y && y < this->y + h){
        return true;
    }
    return false;
}

//activating (selecting) the button.
void Button::activate(){
    active = true;
}

//deactivating it.
void Button::deactivate(){
    active = false;
}

//checking if it is activated.
bool Button::isActivated(){
    return active;
}