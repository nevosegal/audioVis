//
//  Button.h
//  audioVis
//
//  Created by Nevo Segal on 06/01/2015.
//
//

#ifndef __audioVis__Button__
#define __audioVis__Button__
#include <stdio.h>
#include "ofMain.h"

class Button{
public:
    Button();
    Button(int x,int y, string type);
    
    void draw();
    bool isInBounds(int x, int y);
    void activate();
    void deactivate();
    bool isActivated();
    
    int x,y,w,h;
    bool active;
    string type;
    ofImage img;
};

#endif /* defined(__audioVis__Button__) */