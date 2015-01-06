#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    numSpectrum = 30;
    sampleRate 			= 44100;
    initialBufferSize	= 512;

    beat.load(ofToDataPath("song1.wav"));
    buffer = new float[initialBufferSize];
    fft.setup(initialBufferSize, initialBufferSize, initialBufferSize);
    spectrums = new float*[numSpectrum];
    for(int i = 0; i < numSpectrum; i++){
        spectrums[i] = new float[fft.bins];
        for(int j = 0; j < fft.bins; j++){
            spectrums[i][j] = 0;
        }
    }

    ofSoundStreamSetup(2,1,this, sampleRate, initialBufferSize, 4);/* Call this last ! */
}

//--------------------------------------------------------------
void ofApp::update(){

}
//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(50);
    ofSetLineWidth(2);
    
    for(int i = numSpectrum-1; i > 0; i--){
        for(int j = 0; j < fft.bins; j++){
            spectrums[i][j] = spectrums[i-1][j];
        }
    }
    
    for(int j = 0; j < fft.bins; j++){
        spectrums[0][j] = fft.magnitudes[j];
    }
    

    for(int i = 0; i < numSpectrum; i++){
        ofSetColor(30,200,30,255/30*(30-i));
        for(int j = 0; j < fft.bins-1; j++){
            screenRatio = ((float)ofGetWidth()-i*20)/fft.bins;
            ofLine(i*10 +screenRatio*j, 2*ofGetHeight()/3 - i*10 - spectrums[i][j],-1*i*30,
                   i*10 +screenRatio*(j+1), 2*ofGetHeight()/3 - i*10 - spectrums[i][j+1] ,-1*i*30);
        }
    }
    ofSetColor(200,50,50);
    
    ofLine(ofGetWidth()*fft.spectralCentroid()/(sampleRate/2) ,2*ofGetHeight()/3, 15, ofGetWidth()*fft.spectralCentroid()/(sampleRate/2), 2*ofGetHeight()/3+20, 15);

}


//--------------------------------------------------------------
void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++){
        
        sample=buffer[i];
        fft.process(sample);
        
        mymix.stereo(sample, outputs, 0.5);
        
        output[i*nChannels    ] = outputs[0];
        output[i*nChannels + 1] = outputs[1];
    }
}

//--------------------------------------------------------------
void ofApp::audioReceived(float * input, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){
        buffer[i] = input[i];
    }
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

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
