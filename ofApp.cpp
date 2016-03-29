#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//prepare quadric for sphere
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	centerX = ofGetWidth()*0.5;
	centerY = ofGetHeight()*0.5;

	x = centerX;
	y = centerY;
	targetX = x;
	targetY = y;

	SetCursorPos(centerX, centerY);

	ofHideCursor();

	img.loadImage("forest.bmp");

	tex.loadData(img);



	width = img.getWidth();
	height = img.getHeight();

	pixelout = new unsigned char[width*height * 4];//Assigns length to array
	pixelin = new unsigned char[width*height * 3];

	pixelin = img.getPixels();

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			thre = 50;

			pointer = (j*width + i);

			red = pixelin[pointer * 3 + 0];//red
			green = pixelin[pointer * 3 + 1];//green
			blue = pixelin[pointer * 3 + 2];//blue



			pixelout[(j*width + i) * 4 + 0] = pixelin[(j*width + i) * 3 + 0];//red
			pixelout[(j*width + i) * 4 + 1] = pixelin[(j*width + i) * 3 + 1];//green
			pixelout[(j*width + i) * 4 + 2] = pixelin[(j*width + i) * 3 + 2];//blue

			if (green <= blue || green <= red || green < thre)
				pixelout[(j*width + i) * 4 + 3] = 255;//alpha
			else
				pixelout[(j*width + i) * 4 + 3] = 0;//alpha
		}
	}

	tex2.loadData(pixelout, width, height, GL_RGBA);

	//Get directory size
	dir.listDir("seq2");

	sequence.loadSequence("seq2/frame", "png", 5, dir.size() - 1, 4);
	sequence.preloadAllFrames();	//this way there is no stutter when loading frames
	sequence.setFrameRate(5); //set to ten frames per second


	//bg.loadMovie("cell.avi");
	//bg.setLoopState(OF_LOOP_NORMAL);
	//bg.play();
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
	x = ofLerp(x, targetX, 0.0015);

	//Y easing
	dy = targetY - y;
	y += dy*easing;
	y = ofLerp(y, targetY, 0.0015);

	//bg.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	wrapSphere(300, tex, 1, 0);
	wrapSphere(200, tex, 1, 1);

	targetX += incX*0.75;
	targetY += incY*0.67;

	/*
	//Eased Circle
	ofSetColor(255);
	ofEllipse(x, y, 100, 100);

	//Target
	ofSetColor(255, 0, 0);
	ofEllipse(targetX, targetY, 25, 25);
	*/

	incX = 0;
	incY = 0;

    //Plays image sequence
	sequence.getFrameAtPercent(phasor(0.005, 0, 1))->draw(0, 0, 0, 0);



}

//--------------------------------------------------------------
void ofApp::wrapSphere(int s, ofTexture tex, float mag, int i) {


	ofSetColor(255, 255, 255);

	if (i == 0)
		tex.bind();

	if (i == 1)
	sequence.getTextureReference().bind();

	ofPushMatrix();

	ofTranslate(ofGetWidth() / 2, 360, 650);
	ofRotateX(-y*mag);
	ofRotateZ(x*mag);

	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	ofScale(tex.getWidth(), tex.getHeight());
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST); //enable depth comparisons NEEDED FOR SPHERE DEPTH
	ofDisableArbTex(); //needed for textures to work with gluSphe

	gluSphere(quadric, s, 100, 100);

	glDisable(GL_DEPTH_TEST);//disable depth comparisons NEEDED FOR FLAT MASK
	ofEnableArbTex(); //needed for textures to work with gluSphe


	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	if (i == 0)
		tex.unbind();

	if (i == 1)
	sequence.getTextureReference().unbind();

	ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'c') {
		x = centerX;
		y = centerY;
	}

	if (key == 'r') {

		targetX += ofRandom(0, 100);
		targetY += ofRandom(0, 100);
	}
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

float ofApp::ofLerp(float start, float stop, float amt) {
	return start + (stop - start) * amt;
}
