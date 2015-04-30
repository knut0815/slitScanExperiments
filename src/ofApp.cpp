#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.initGrabber(640, 480);
    player.loadMovie("Perlin_Noise.mov");
    slitScanImg.allocate(grabber.getWidth(), grabber.getHeight(), OF_IMAGE_COLOR);
    int i = 0;
    while ( i < slitScanImg.getPixelsRef().size() ) {
        slitScanImg.getPixelsRef()[i] = 0;
        i++;
    }
    slitScanImg.update();
    
    ofSetWindowShape(grabber.getWidth(), grabber.getHeight());
    videoSliceX = grabber.getWidth()/2;
    drawPositionX = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    
    unsigned char * grabberPixels = grabber.getPixels();
    
    for (int y = 0; y < grabber.getHeight(); y++){
        int red = grabberPixels[(y * grabber.width + videoSliceX) * 3];
        int green = grabberPixels[(y * grabber.width + videoSliceX) * 3 + 1];
        int blue = grabberPixels[ (y * grabber.width + videoSliceX) * 3 + 2];
        slitScanImg.getPixelsRef().setColor(drawPositionX, y, ofColor(red, green, blue));
    }
    slitScanImg.update();
    drawPositionX++;
    if (drawPositionX > grabber.getWidth()) {
        drawPositionX = 0;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    slitScanImg.draw(0, 0);
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
