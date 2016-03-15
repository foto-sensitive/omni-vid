#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	img.loadImage("japan.bmp");

	scale = 1;

	width = img.getWidth();
	height = img.getHeight();

	sWidth = (int)width / scale;
	sHeight = (int)height / scale;

	//Assigns length to array
	pixelin = new unsigned char[width* height * 3];
	pixelout = new unsigned char[sWidth* sHeight * 3];
}

//--------------------------------------------------------------
void ofApp::update(){

	pixelin = img.getPixels();


	for (int i = 0; i < width; i+=scale) {
		for (int j = 0; j < height; j+=scale) {

			pointer = (j*width + i);
			sPointer = ((j/scale)*sWidth + (i/scale));

			pixelout[sPointer * 3 + 0] = pixelin[pointer * 3 + 0];//red
			pixelout[sPointer * 3 + 1] = pixelin[pointer * 3 + 1];//green
			pixelout[sPointer * 3 + 2] = pixelin[pointer * 3 + 2];//blue

		}
	}


	scaled.setFromPixels(pixelout, sWidth, sHeight, OF_IMAGE_COLOR);//Writes pixels to preview sequence
}

//--------------------------------------------------------------
void ofApp::draw(){
	img.draw(0, 0);
	scaled.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){


	for (i = 0; i < 7; i++) {
		char myChar = '0' + i;
		if (key == myChar)
			scale = i;
		sWidth = (int)width / scale;
		sHeight = (int)height / scale;
		pixelout = new unsigned char[sWidth* sHeight * 3];
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
