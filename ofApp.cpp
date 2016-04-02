#include "ofApp.h"
#include <string>


//-------------------------------------------------------------
ofApp::~ofApp() {

}

//--------------------------------------------------------------
void ofApp::setup(){
	
	gui.setup();
	gui.add(thre.setup("Threshold", 255, 0, 256));
	gui.add(tolerence.setup("Tolerence", 1, -255, 256));

}

//--------------------------------------------------------------
void ofApp::update(){

	for (u = 0; u < videos.size(); u++) {

		videos[u].update();
		if (videos[u].isFrameNew()) {

			if (play)
				thre = ofMap(phasor(0.01, 0, 255), 0, 255, 255, 0);

			width = videos[u].getWidth();
			height = videos[u].getHeight();

			pixelout = new unsigned char[width * height * 3];//Assigns length to array
			pixelin = new unsigned char[width * height * 3];


			pixelin = videos[u].getPixels();//Gets pixels from video
											
			for (i = 0; i < width; i++) {
				for (j = 0; j < height; j++) {



					pointer = (j*width + i);

					red = pixelin[pointer * 3 + 0];//red
					green = pixelin[pointer * 3 + 1];//green
					blue = pixelin[pointer * 3 + 2];//blue

					if ( green <= blue - tolerence || green <= red - tolerence || green < thre) {

						//Draw Pixel
						pixelout[pointer * 3 + 0] = red;
						pixelout[pointer * 3 + 1] = green;
						pixelout[pointer * 3 + 2] = blue;

					}
					else {
						pixelout[pointer * 3 + 0] = 255;
						pixelout[pointer * 3 + 1] = 255;
						pixelout[pointer * 3 + 2] = 255;
					}
				}
			} 
			preview.loadData(pixelout, width, height, GL_RGB);//Writes pixels to preview sequence
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	if (videos.size() > 0)
		preview.draw(0, 0, ofGetWidth(),ofGetHeight());

	gui.draw();






}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'l') {
		//Creates new video player
		ofVideoPlayer player;
		player.loadMovie("hands.avi");
		player.setLoopState(OF_LOOP_NORMAL);
		player.play();
		videos.push_back(player);
	}

	if (key == 'p')
		play = !play;

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