#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "Button.h"

class ofApp : public ofBaseApp{

	public:
    
    //class methods
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        float getSpectralCentroid(float* amplitudeSpectrum);
        float* hanning(int bufferSize);
        void audioRequested (float * input, int bufferSize, int nChannels);
        void audioReceived (float * input, int bufferSize, int nChannels);
    
    //class variables
        int	initialBufferSize;
        int	sampleRate;
        double sample,outputs[2];
        ofxMaxiMix mymix;
        maxiOsc sine;
        ofxMaxiSample beat;
        ofxMaxiFFT fft;
        float screenRatio;
        int numSpectrum;
        float** spectrums;
        float* buffer;
        Button* buttons;
        int numButtons;
        int sineFreq, mousePressedY;
        float* hannedWindow;
};
