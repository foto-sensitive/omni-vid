#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	centerX = ofGetWidth()*0.5;
	centerY = ofGetHeight()*0.5;

	x = centerX;
	y = centerY;
	targetX = x;
	targetY = y;

	SetCursorPos(centerX, centerY);

	ofHideCursor();

}

//--------------------------------------------------------------
void ofApp::update(){
	
	if (!dont) {
		SetCursorPos(centerX, centerY);
		doit = false;
	}
	else {
		doit = true;
	}

	dont = false;

	//X easing
	dx = targetX - x;
	x += dx*easing;

	//Y easing
	dy = targetY - y;
	y += dy*easing;
}

//--------------------------------------------------------------
void ofApp::draw(){

	targetX += incX*2;
	targetY += incY*2;

	//Eased Circle
	ofSetColor(255);
	ofEllipse(x, y, 100, 100);

	//Target
	ofSetColor(255, 0, 0);
	ofEllipse(targetX, targetY, 25, 25);

	incX = 0;
	incY = 0;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	x = centerX;
	y = centerY;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

	if (doit) {
		incX = mouseX - ofGetPreviousMouseX();
		incY = mouseY - ofGetPreviousMouseY();
	}

	dont = true;
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
