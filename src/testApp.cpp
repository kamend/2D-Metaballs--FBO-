#include "testApp.h"

const int numBalls = 500;

//--------------------------------------------------------------
void testApp::setup(){
	
    ofSetFrameRate(30);
	// setup
	ofSetLogLevel(OF_LOG_VERBOSE);
    
    grid = new MetaBallGrid(640,480,1,1);
    
    for(int i=0;i<numBalls;i++) {
        grid->addBall(round(ofRandom(640)),round(ofRandom(480)),ofRandom(30));
    }
    
    renderTex.allocate(640,480,GL_RGBA);
    
    img.loadImage("metaballTexture.png");
  
}

//--------------------------------------------------------------
void testApp::update(){
      grid->update();
}

//--------------------------------------------------------------
void testApp::draw(){

      
    ofBackground(0, 0, 0);
    
    renderTex.begin();
    ofClear(0,0,0);
    glPushAttrib(GL_ALL_ATTRIB_BITS);  
    glEnable(GL_BLEND);  
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE,GL_ONE,GL_ONE_MINUS_SRC_ALPHA); 
    
    for(int i=0;i<numBalls;i++) {
        ofVec2f pos = grid->getBall(i)->pos;
        float radius = grid->getBall(i)->radius;
        img.getTextureReference().draw(pos.x,pos.y,64,64);
    }
    
    glPopAttrib();
    renderTex.end();
    
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.30);
    renderTex.draw(0,0);
    glDisable(GL_ALPHA_TEST);
    
//    ofDrawBitmapString(ofToString(ofGetFrameRate()), 20,400);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}