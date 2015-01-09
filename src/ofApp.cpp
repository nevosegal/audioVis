#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //number of buttons
    numButtons = 3;
    
    //default frequency of sine wave
    sineFreq = 440;
    sampleRate = 44100;
    initialBufferSize = 512;
    
    //loading the song.
    beat.load(ofToDataPath("song1.wav"));
    //buffer that will be used to store the input.
    buffer = new float[initialBufferSize];
    
    //setting up the fft
    fft.setup(initialBufferSize, initialBufferSize, initialBufferSize);
    
    //number of spectrums
    numSpectrum = 30;
    //creating a new array of spectrums
    spectrums = new float*[numSpectrum];
    
    //filling this array with arrays, hence making it a 2D array (an array of spectrums).
    for(int i = 0; i < numSpectrum; i++){
        spectrums[i] = new float[fft.bins];
        for(int j = 0; j < fft.bins; j++){
            spectrums[i][j] = 0;
        }
    }
    
    //an array storing the hanning window function
    hannedWindow = hanning(initialBufferSize);
    
    //creating buttons for each input type
    buttons = new Button[numButtons];
    buttons[0] = *new Button(20,20,"mic");
    buttons[1] = *new Button(70,20,"song");
    buttons[2] = *new Button(120,20,"osc");
    buttons[0].activate();

    ofSoundStreamSetup(2,1,this, sampleRate, initialBufferSize, 4);/* Call this last ! */
}

//--------------------------------------------------------------
void ofApp::update(){

}
//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(30);
    ofSetLineWidth(2);
    
    //pushing the spectrums backwards to create this spectrum moving effect.
    for(int i = numSpectrum-1; i > 0; i--){
        for(int j = 0; j < fft.bins; j++){
            spectrums[i][j] = spectrums[i-1][j];
        }
    }
    
    //calculating the current spectrum and storing it in the first index of the array.
    for(int j = 0; j < fft.bins; j++){
        spectrums[0][j] = fft.magnitudes[j];
    }
    
    //drawing the lines
    for(int i = 0; i < numSpectrum; i++){
        //changing the alpha value in order to get the fading out effect.
        ofSetColor(30,200,30,255/30*(30-i));
        for(int j = 0; j < fft.bins-1; j++){
            screenRatio = ((float)ofGetWidth()-i*20)/fft.bins;
            ofLine(i*10 +screenRatio*j, 2*ofGetHeight()/3 - i*10 - 2*spectrums[i][j],-1*i*30,
                   i*10 +screenRatio*(j+1), 2*ofGetHeight()/3 - i*10 - 2*spectrums[i][j+1] ,-1*i*30);
        }
    }
    //drawing the spectral centroid
    ofSetColor(200,50,50);
    ofLine(ofGetWidth()*fft.spectralCentroid()/(sampleRate/2) ,2*ofGetHeight()/3, ofGetWidth()*fft.spectralCentroid()/(sampleRate/2), 2*ofGetHeight()/3+40);
    ofDrawBitmapString(ofToString(fft.spectralCentroid()), ofGetWidth()*fft.spectralCentroid()/(sampleRate/2) + 5, 2*ofGetHeight()/3+40);
    
    //drawing the buttons
    for(int i = 0; i < numButtons; i++){
        buttons[i].draw();
    }
}


//--------------------------------------------------------------
void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){
    
    //checking which button is activated and choosing the next sample accordingly
    for (int i = 0; i < bufferSize; i++){
        for(int j = 0 ; j < numButtons; j++) {
            if(buttons[j].isActivated()){
                if(buttons[j].type == "osc"){
                    sample = sine.sinewave(sineFreq);
                }
                else if( buttons[j].type == "song"){
                    sample = beat.play();
                }
                else{
                    sample=buffer[i];
                }
            }
        }

        //processing the fft using a hanned window
        fft.process(hannedWindow[i]*sample);
        
        //making it stereo
        mymix.stereo(sample, outputs, 0.5);
        
        output[i*nChannels    ] = outputs[0];
        output[i*nChannels + 1] = outputs[1];
    }
}

//--------------------------------------------------------------
void ofApp::audioReceived(float * input, int bufferSize, int nChannels){
    //storing the mic input in an array.
    for(int i = 0; i < bufferSize; i++){
        buffer[i] = input[i];
    }
}


//the hanning function (taken from www.rgm.ogalab.net/RGM/R_rdfile?f=GENEAread/man/hanning.window.Rd&d=R_CC)
float* ofApp::hanning(int bufferSize){
    float* hanning = new float[bufferSize];
    for (int i = 0; i < bufferSize; i++) {
        hanning[i] = 0.5 - 0.5*cos(2*PI*i/(bufferSize-1));
    }
    return hanning;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    //changing the frequency of the oscillator when the mouse is changed
    for(int i = 0; i < numButtons; i++){
        if(buttons[i].type == "osc" && buttons[i].isActivated()){
            int deltaY = 5*(mousePressedY - y);
            sineFreq += deltaY;
            mousePressedY = y;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //storing the position of the mouse when clicked
    mousePressedY = y;
    
    //activating/deactivating buttons when clicked.
    for(int i = 0 ; i < numButtons; i++){
        if(buttons[i].isInBounds(x, y)){
            buttons[i].activate();
            for(int j = 0 ; j < numButtons; j++){
                if(i!=j){
                    buttons[j].deactivate();
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
