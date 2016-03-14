


#include "ofApp.h"


//-------------------------------------------------------------
ofApp::~ofApp() {


}

//--------------------------------------------------------------
void ofApp::setup() {

	//Initilises recorder as false
	rec = false;

	recorder.setPrefix(ofToDataPath("recording1/frame")); // this directory must already exist
	recorder.setFormat("bmp"); // png is really slow but high res, bmp is fast but big, jpg is just right


}

//--------------------------------------------------------------
void ofApp::update() {

	for (i = 0; i < videos.size(); i++)


			if (!skip[i])//Skips video if update disabled
				videos[i].update();
	

	if (videos.size() > 0) {

		width = videos[0].getWidth();
		height = videos[0].getHeight();

		if (!allocate) {
			pixelout = new unsigned char[width*height * 3];//Assigns length to array
			pixelin = new unsigned char[width*height * 3];
			allocate = true;
		}

		if (cycle) {
			for (i = 0; i < videos.size(); i++) {

				videos[i].nextFrame();
				newFrame = true;

				if (videos[0].getCurrentFrame() >= videos[0].getTotalNumFrames()) {
					videos[i].setFrame(0);
					cycle = false;
					preLoad = true;
				}
			}
		}
		
		if (newFrame) {
			for (int u = 0; u < videos.size(); u++) {
				if (rec) {

					pixelin = videos[u].getPixels();//Gets pixels from video

					for (int i = 0; i < width; i++) {
						for (int j = 0; j < height; j++) { //Writes pixels if chroma trheshold hasn't been reached, otherwise assumes from previous frame
							if (u == 0 || pixelin[(j*width + i) * 3 + 1] < 250 && u > 0) {
								pixelout[(j*width + i) * 3 + 0] = pixelin[(j*width + i) * 3 + 0];//red
								pixelout[(j*width + i) * 3 + 1] = pixelin[(j*width + i) * 3 + 1];//green
								pixelout[(j*width + i) * 3 + 2] = pixelin[(j*width + i) * 3 + 2];//blue

							}
						}
					}
					preview.setFromPixels(pixelout, width, height, OF_IMAGE_COLOR);//Writes pixels to preview sequence
				}

			}
			//Outside of loop to make sure final edit is layered correctly
			recorder.addFrame(preview);
			newFrame = false;
		}
	
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(125);
	ofSetColor(255);


	for (i = 0; i < videos.size(); i++)
		videos[i].draw((ofGetWidth() / videos.size()*i), 0, ofGetWidth() / videos.size(), ofGetHeight() / videos.size());


	if (videos.size() > 0) { //If there are videos preform recording functions


		if (preLoad) { //Stops recording if ran out of frames

			recorder.stopThread();
			rec = false;

			//Get directory size
			dir.listDir("recording1");

			sequence.loadSequence("recording1/frame", "bmp", 0, dir.size() - 1, 4);
			sequence.preloadAllFrames();	//this way there is no stutter when loading frames
			sequence.setFrameRate(5); //set to ten frames per second
			sequenced = true; //Plays sequence when it has been written

			for (int j = 0; j < videos.size(); j++)
				skip[j] = true; //Prevents original videos from playing because composite has loaded, saving memory

			preLoad = false;
		}
	}

	if (sequenced)
		sequence.getFrameAtPercent(phasor(0.005, 0, 1))->draw(ofGetWidth()*0.5, ofGetHeight()*0.5, ofGetWidth()*0.5, ofGetHeight()*0.5);

}

void ofApp::exit() {
	recorder.waitForThread();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (key == 'r') {

		cycle = true;//Cycles through frames individually when recording

		recorder.setCounter(0);
		for (i = 0; i < videos.size(); i++)
			videos[i].setFrame(0);
		rec = true;
		recorder.startThread(false, true);


		for (int j = 0; j < videos.size(); j++)
			skip[j] = false;

		for (i = 0; i < videos.size(); i++)
			videos[i].setPaused(true);
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