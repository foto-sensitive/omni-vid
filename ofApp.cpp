#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	video[0].loadMovie("04.m2t");
	video[1].loadMovie("mandlebulb.avi");

	for (int i = 0; i < 2; i++) {
		video[i].play();
		video[i].setLoopState(OF_LOOP_NORMAL);
	}

	width = (int)video[1].getWidth();
	height = (int)video[1].getHeight();

	pixelout = new unsigned char[width*height * 4];//Assigns length to array
	lastPixels = new unsigned char[width*height * 4];

	//GUI
	gui.setup(); // most of the time you don't need a name
	gui.add(red.setup("Red", false));
	gui.add(green.setup("Green", false));
	gui.add(blue.setup("Blue", false));

}

//--------------------------------------------------------------
void ofApp::update(){

	ofBackground(0,255,0);

	for (int i = 0; i < 2; i++)
	video[i].update();

	//only try and process video when we have a new frame.
	if (video[1].isFrameNew()) {
		pixels = video[1].getPixels();

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				pixelout[(j*width + i) * 4 + 0] = pixels[(j*width + i) * 3 + 0];//red
				pixelout[(j*width + i) * 4 + 1] = pixels[(j*width + i) * 3+ 1];//green
				pixelout[(j*width + i) * 4 + 2] = pixels[(j*width + i) * 3 + 2];//blue
				
				if((pixelout[(j*width + i) * 4 + 0] > 200 && red) ||
					(pixelout[(j*width + i) * 4 + 1] > 200 && green) ||
					(pixelout[(j*width + i) * 4 + 2] > 200 && blue)   )

				pixelout[(j*width + i) * 4 + 3] = 0;

				else pixelout[(j*width + i) * 4 + 3] = 255;

			}
		}


		filter.loadData(pixelout, width, height, GL_RGBA);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	video[0].draw(0, 0, ofGetWidth(), ofGetHeight());
	filter.draw(0, 0, ofGetWidth(), ofGetHeight());

	gui.draw();

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
