#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
	~ofApp();/* destructor is very useful */
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	double phasor(double frequency, double startphase, double endphase);
	
	string path; //Path of dragged file

	vector <ofVideoPlayer> videos; //Contains videos

	int i, j, u; //iterators

	int red, green, blue, alpha; //pixel values

	double phase;

	int pointer; //Points to place in array

	//Pixel Arrays
	unsigned char * pixelout;
	unsigned char * pixelin;
	unsigned char * pixels;

	int width, height; //Dimensions of image

	ofTexture preview;

	ofxPanel gui;
	ofxIntSlider thre;
	ofxIntSlider tolerence;

	bool play = false; //Plays demo

};

