#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	img[0].loadImage("japan3.bmp");
	img[1].loadImage("mandle3.bmp");

	width = img[0].getWidth();
	height = img[0].getHeight();

	pixelout = new unsigned char[width* height * 3];//Assigns length to array
	pixelin = new unsigned char[width* height * 3];

}
//--------------------------------------------------------------
void ofApp::update(){

	for (u = 0; u < 2; u++) {

		pixelin = img[u].getPixels();//Gets pixels from video

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {


				thre = 254;

				pointer[0] = (j*width + i);
				pointer[u+1] = (loop(j + mouseY * (int)(5 * (u+1)), 0, height - 1)*width + loop(i + mouseX * (int)(5 * (u + 1)), 0, width - 1));
				

				if (u == 0 || pixelin[pointer[2] * 3 + 1] < thre) {

					

					pixelout[pointer[0] * 3 + 0] = pixelin[pointer[u + 1] * 3 + 0];//red
					pixelout[pointer[0] * 3 + 1] = pixelin[pointer[u + 1] * 3 + 1];//green
					pixelout[pointer[0] * 3 + 2] = pixelin[pointer[u + 1] * 3 + 2];//blue
				}

			}
		}
	}


	preview.setFromPixels(pixelout, width, height, OF_IMAGE_COLOR);//Writes pixels to preview sequence
}

//--------------------------------------------------------------
void ofApp::draw(){
	counter+=40;
	preview.draw(0, 0, width*1.55, height*1.55);


	ofDrawBitmapString(loop(mouseX-(ofGetWidth()/2), 0, 50), ofGetWidth()*0.85, ofGetHeight()*0.5);
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

//--------------------------------------------------------------

int ofApp::loop(int current, int start, int end) {

	if (current > end)
		phase = current - (end * (int)(current / end));
	else if(current < start)
		phase = current + (end * (((int)(current / end)*-1)+1));
	else
		phase = current;

	return phase;
}

