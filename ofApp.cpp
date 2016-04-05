#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//prepare quadric for sphere
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	for (i = 0; i < NWRAPS; i++)
		myWrap[i].setup(quadric);


	img.loadImage("hands.png");

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
	dir.listDir("seq3");

	sequence.loadSequence("seq3/frame", "png", 0, dir.size() - 1, 4);
	sequence.preloadAllFrames();	//this way there is no stutter when loading frames
	sequence.setFrameRate(5); //set to ten frames per second


	bg.loadMovie("ghost_cube.avi");
	bg.setLoopState(OF_LOOP_NORMAL);
	bg.play();

	ofSetVerticalSync(true);


}

//--------------------------------------------------------------
void ofApp::update(){

	for (i = 0; i < NWRAPS; i++)
	myWrap[i].update();

	bg.update();

	v1.x = ofLerp(v1.x, mouseX+translate.x, 0.005);
	v1.y = ofLerp(v1.y, mouseY+translate.y, 0.005);

}

//--------------------------------------------------------------
void ofApp::draw(){

	//wrapSphere(300, tex, 0.5, 0);


	myWrap[0].draw(0, bg, 0.5, 300, v1);
	myWrap[1].draw(1, sequence, 0.75, 200, v1);

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
void ofApp::keyPressed(int key){
	if (key == OF_KEY_LEFT) {
		translate.x -= inc;
		v1.x = mouseX + translate.x;
	}
	if (key == OF_KEY_RIGHT) {
		translate.x += inc;
		v1.x = mouseX + translate.x;
	}
	if (key == OF_KEY_UP) {
		translate.y -= inc;
		v1.y = mouseY + translate.y;
	}
	if (key == OF_KEY_DOWN) {
		translate.y += inc;
		v1.y = mouseY + translate.y;
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

