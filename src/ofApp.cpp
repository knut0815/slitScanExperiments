#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    grabber.initGrabber(640, 480);

    cam.setDistance(800);
    player.loadMovie("Perlin_Noise.mov");
    player.play();
    slitScanImg.allocate(grabber.getWidth(), grabber.getHeight(), OF_IMAGE_COLOR);
    int i = 0;
    while ( i < slitScanImg.getPixelsRef().size() ) {
        slitScanImg.getPixelsRef()[i] = 0;
        i++;
    }
    slitScanImg.update();
    
    shader.load("displacement.vert", "displacement.frag");
    
    firstPass.allocate(grabber.width, grabber.height, GL_RGB, 4);
    firstPass.begin();
    ofClear(0, 0, 0, 255);
    firstPass.end();
    
    secondPass.allocate(grabber.width, grabber.height, GL_RGB, 4);
    secondPass.begin();
    ofClear(0, 0, 0, 255);
    secondPass.end();
    
    ofSetWindowShape(grabber.getWidth(), grabber.getHeight());
    videoSliceX = grabber.getWidth()/2;
    drawPositionX = 0;
    
    vertexResolution = 20;
    numColumnsAdded = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    player.update();
    
    if (drawPositionX % 10 == 0 && drawPositionX > 0) {
        //Every 30 frames...
        float ySpacing = ofGetHeight() / vertexResolution;
        for (int i = 0; i < vertexResolution; i++) {
            mesh.addVertex(ofPoint(drawPositionX, ySpacing * i)); //was adding + (numColumnsAdded) to x
            mesh.addTexCoord(ofVec2f(drawPositionX, ySpacing * i));
        }
        for(int i = 0; i < vertexResolution-1; i++) {
            mesh.addIndex(i + (numColumnsAdded-1) * vertexResolution); //--0
            mesh.addIndex(i + numColumnsAdded * vertexResolution); //--20
            mesh.addIndex(i + 1 + numColumnsAdded * vertexResolution); //--21
            
            mesh.addIndex(i + (numColumnsAdded-1) * vertexResolution); //--0
            mesh.addIndex(i + 1 + (numColumnsAdded-1) * vertexResolution); //--1
            mesh.addIndex(i + 1 + numColumnsAdded * vertexResolution); //--21
        }

        numColumnsAdded++;
        
    }
    
    for (int i = 0; i < mesh.getNumVertices(); i++) {
        ofVec3f displacedVertex = mesh.getVertex(i);
        displacedVertex.z = ofMap(ofNoise(ofGetElapsedTimef()+i), -1, 1, -10, 10);
        mesh.setVertex(i, displacedVertex);
    }
    
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
        int i = 0;
        while ( i < slitScanImg.getPixelsRef().size() ) {
            slitScanImg.getPixelsRef()[i] = 0;
            i++;
        }
        numColumnsAdded = 0;
        mesh.clear();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //----FBOs and Shaders
    firstPass.begin();
    shader.begin();
    shader.setUniformTexture("tex0", slitScanImg.getTextureReference(), 0);
    shader.setUniformTexture("tex1", slitScanImg.getTextureReference(), 1);
    shader.setUniform1f("displacementAmountX", 150.0);
    shader.setUniform1f("displacementAmountY", 150.0);
    slitScanImg.draw(0, 0);
    shader.end();
    firstPass.end();

    secondPass.begin();
    shader.begin();
    shader.setUniformTexture("tex0", firstPass.getTextureReference(), 0);
    shader.setUniformTexture("tex1", firstPass.getTextureReference(), 1);
    shader.setUniform1f("displacementAmountX", 150.0);
    shader.setUniform1f("displacementAmountY", 150.0);
    firstPass.draw(0, 0);
    shader.end();
    secondPass.end();
    
    //----Debug
    ofSetColor(ofColor::red);
    ofRect(drawPositionX, ofGetHeight()-10, 4, 10);
    
    //----Drawing
    cam.begin();
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);

    secondPass.getTextureReference().bind();
    ofSetColor(255);
    mesh.draw();
    secondPass.getTextureReference().unbind();
    //mesh.drawWireframe();
    
    ofPopMatrix();
    cam.end();

    ofSetWindowTitle("" + ofToString(ofGetFrameRate())) ;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's' || key == 'S') {
        ofSaveFrame();
    }
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
