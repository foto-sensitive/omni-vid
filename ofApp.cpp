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
		videos[i].setLoopState(OF_LOOP_NONE);


	rec = false;

	

	recorder.setPrefix(ofToDataPath("recording1/frame_")); // this directory must already exist
	recorder.setFormat("bmp"); // png is really slow but high res, bmp is fast but big, jpg is just right


}

//--------------------------------------------------------------
void ofApp::update() {


	for (i = 0; i < videos.size(); i++)
			videos[i].update();

	if (videos.size() > 0) {

		width = videos[0].getWidth();
		height = videos[0].getHeight();

		if (!allocate) {
			pixelout = new unsigned char[width*height * 3];//Assigns length to array
			pixelin = new unsigned char[width*height * 3];
			allocate = true;
		}

		for (int u = 0; u < videos.size(); u++) {
			if (videos[u].isFrameNew() && rec) {

				pixelin = videos[u].getPixels();

				for (int i = 0; i < width; i++) {
					for (int j = 0; j < height; j++) {

						
						if (u == 0 || pixelin[(j*width + i) * 3 + 1]>100 && u > 0) {

							pixelout[(j*width + i) * 3 + 0] = pixelin[(j*width + i) * 3 + 0];//red
							pixelout[(j*width + i) * 3 + 1] = pixelin[(j*width + i) * 3 + 1];//green
							pixelout[(j*width + i) * 3 + 2] = pixelin[(j*width + i) * 3 + 2];//blue

						}

					}
				}



				//Writes our pixels to texture
				//preview.load(pixelout, width, height, GL_RGB);

				
				preview.setFromPixels(pixelout, width, height, OF_IMAGE_COLOR);
				
			}
		}
		//Outside of loop to make sure final rednition gets added
		recorder.addFrame(preview);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(125);

	ofSetColor(255);

	stringstream c;
	c << "Recording: " << rec << "\nThread running: " << recorder.isThreadRunning() << "\nQueue Size: " << recorder.q.size() << "\n\nPress 'r' to toggle recording.\nPress 't' to toggle worker thread." << endl;

	ofDrawBitmapString(c.str(), 650, 10);


	for (i = 0; i < videos.size(); i++)
		videos[i].draw((ofGetWidth() / videos.size()*i), 0, ofGetWidth() / videos.size(), ofGetHeight() / videos.size());


	if (videos.size() > 0) {
		ofDrawBitmapString(videos[0].getPosition(), mouseX, mouseY);
		if (recorder.isThreadRunning() && videos[0].getPosition() > 0.99) {
			recorder.stopThread();
			rec = false;
		}
	}
}

void ofApp::exit() {
	recorder.waitForThread();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	if (key == 'r') {
		rec = true;
		recorder.startThread(false, true);
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