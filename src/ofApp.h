#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
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
    
    ofVideoGrabber grabber;
    ofVideoPlayer player;
    ofImage slitScanImg;
    
    ofEasyCam cam;
    ofMesh mesh;
    int vertexResolution;
    int numColumnsAdded;
    
    ofShader shader;
    ofFbo firstPass;
    ofFbo secondPass;
    
    int videoSliceX;
    int drawPositionX;
    
    //ofVideoPlayer grabber;
};
