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




	//File format for the example frames is
	//frame01.png 
	//this creates a method call where the parameters
	//prefix is frame, file type is png, from frame 1 to 11, 2 digits in the number
	sequence.loadSequence("seq/frame", "bmp", 1, 38, 2);
	sequence.preloadAllFrames();	//this way there is no stutter when loading frames
	sequence.setFrameRate(25); //set to ten frames per second for Muybridge's horse.

	playing = false; //controls if playing automatically, or controlled by the mouse

}

//--------------------------------------------------------------
void ofApp::update() {


	if (videos.size() > 0) {
		if (videos.size() > 0) {
			for (i = 0; i < videos.size(); i++) {

				if (!skip[i])//Skips video if update disabled
					videos[i].update();

				//Writes frames to preview
				if (write) {
					//only try and process video when we have a new frame.
					if (videos[0].isFrameNew()) {
						pixelout = videos[0].getPixels();
					}

					width = videos[i].getWidth();
					height = videos[i].getHeight();

					//Writes our pixels to texture
					preview.loadData(pixelout, width, height, GL_RGB);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	//Size of vidoe Array
	s = videos.size();
	
	if (s > 0) {
		for (i = 0; i < s; i++)
			videos[i].draw((ofGetWidth()/s*i), 0, ofGetWidth()/s, ofGetHeight()/s);
	

	//preview.draw(ofGetWidth()*0.5, ofGetHeight()*0.5, ofGetWidth()*0.5, ofGetHeight()*0.5);

	}
	

	sequence.getFrameAtPercent(phasor(0.09, 0, 1))->draw(ofGetWidth()*0.5, ofGetHeight()*0.5, ofGetWidth()*0.5, ofGetHeight()*0.5);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	for (int i = 0; i < 10; i++) {
		char myChar = '0' + i;
		if (key == myChar)
			skip[i] = !skip[i];
	}

	if (key == 'w')
		write = !write;

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

//--------------------------------------------------------------

double ofApp::phasor(double frequency, double startphase, double endphase) {
	//This is a phasor that takes a value for the start and end of the ramp. 
	if (phase<startphase) {
		phase = startphase;
	}
	if (phase >= endphase) phase = startphase;
	phase += ((endphase - startphase) / (1 / (frequency)));
	return(phase);
}
