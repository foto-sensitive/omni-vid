


#include "ofApp.h"


//-------------------------------------------------------------
ofApp::~ofApp() {


}

//--------------------------------------------------------------
void ofApp::setup() {

	//prepare quadric for sphere
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricNormals(quadric, GLU_SMOOTH);


	//Recorder initlisers
	recorder.setPrefix(ofToDataPath("recording1/frame")); // this directory must already exist
	recorder.setFormat("bmp"); // png is really slow but high res, bmp is fast but big, jpg is just right
}

//--------------------------------------------------------------
void ofApp::update() {

	for (i = 0; i < videos.size(); i++)

			if (!skip[i])//Skips video if update disabled
				videos[i].update();


	if (videos.size() > 0) {//Prevents errors if video hasn't been uploaded

		width = videos[0].getWidth();
		height = videos[0].getHeight();

		if (!allocate) {//Allocates memeory to video once it has been uploaded
			pixelout = new unsigned char[width*height * 3];//Assigns length to array
			pixelin = new unsigned char[width*height * 3];
			allocate = true;
		}

		if (cycleOn) {
			cycle();//cycle throguh all the frames starting at 0 for recording
		}
		
		if (newFrame) { //Check if new there is new frame
			addNewFrame(); //Add new frame once passed through the filters
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(125);
	ofSetColor(255);

	if(toggle)//Activated for 360 preview
	cam.begin();

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

	if (sequenced) //Checks if sequence has been created, plays it
		sequence.getFrameAtPercent(phasor(0.005, 0, 1))->draw(ofGetWidth()*0.5, ofGetHeight()*0.5, ofGetWidth()*0.5, ofGetHeight()*0.5);


	if (toggle) { //Activated for 360 preview
		wrapSphere();
		cam.end();
	}

}

void ofApp::exit() {
	recorder.waitForThread();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (key == 'r') { //Recording
		cycleOn = true;//cycleOns through frames individually when recording

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

	if (key == 't') { //Turns on sphere and camera controls
		cam.toggleControl();
		toggle = !toggle;
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


//--------------------------------------------------------------
void ofApp::wrapSphere() {

	ofSetColor(255, 255, 255);

	sequence.getTextureReference().bind();

	ofPushMatrix();

	ofRotateX(90);

	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	ofScale(sequence.getWidth(), sequence.getHeight());
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST); //enable depth comparisons NEEDED FOR SPHERE DEPTH
	ofDisableArbTex(); //needed for textures to work with gluSphe

	gluSphere(quadric, 200, 100, 100);

	glDisable(GL_DEPTH_TEST);//disable depth comparisons NEEDED FOR FLAT MASK
	ofEnableArbTex(); //needed for textures to work with gluSphe


	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	sequence.getTextureReference().unbind();

	ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::addNewFrame() {

	for (u = 0; u < videos.size(); u++) {
		if (rec) {
			pixelin = videos[u].getPixels();//Gets pixels from video

			for (i = 0; i < width; i++) {
				for (j = 0; j < height; j++) { //Writes pixels if chroma trheshold hasn't been reached, otherwise assumes from previous frame


					thre = 254;

					if (u == 0 || pixelin[(j*width + i) * 3 + 1] < thre) {
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

//--------------------------------------------------------------
void ofApp::cycle() { //cycle throguh all the frames starting at 0 for recording
	for (i = 0; i < videos.size(); i++) {

		videos[i].nextFrame();
		newFrame = true;

		if (videos[0].getCurrentFrame() >= videos[0].getTotalNumFrames() || videos[0].getPosition() >= 0.99) {
			videos[i].setFrame(0);
			cycleOn = false;
			preLoad = true;
		}
	}
}