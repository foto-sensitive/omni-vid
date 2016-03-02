/* This is an example of how to integrate maximilain into openFrameworks,
including using audio received for input and audio requested for output.


You can copy and paste this and use it as a starting example.

*/



#include "ofApp.h"


//-------------------------------------------------------------
ofApp::~ofApp() {


}


//--------------------------------------------------------------
void ofApp::setup() {
	for (i = 0; i < videos.size(); i++)
		videos[i].setLoopState(OF_LOOP_PALINDROME);
}

//--------------------------------------------------------------
void ofApp::update() {
	for (i = 0; i < videos.size(); i++)

			if(!skip[i])
		videos[i].update();

	

}

//--------------------------------------------------------------
void ofApp::draw() {

	//Size of vidoe Array
	s = videos.size();


	if (s > 0) {
		for (i = 0; i < s; i++)
			videos[i].draw((ofGetWidth()/s*i), 0, ofGetWidth()/s, ofGetHeight()/s);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	for (int i = 0; i < 10; i++) {
		char myChar = '0' + i;
		if (key == myChar)
			skip[i] = !skip[i];
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {


}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {


}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}



//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo info) {


	//Gets video path
	path = info.files[0];

	//Creates new video player
	ofVideoPlayer player;
	player.loadMovie(path);
	player.setLoopState(OF_LOOP_NORMAL);
	player.play();
	videos.push_back(player);

}