#pragma once

#include "ofMain.h"
#include "ofxImageSequence.h"
#include "ofxImageSequenceRecorder.h"
#include "ofxFirstPersonCamera.h"

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
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo info);
	void gotMessage(ofMessage msg);
	double phasor(double frequency, double startphase, double endphase);
	void wrapSphere();
	void addNewFrame();
	void cycle();
	void exit();

	string path; //Path of dragged file

				 //Contain videos
	vector <ofVideoPlayer> videos;
	ofImage preview;

	unsigned char * pixelout;
	unsigned char * pixelin;
	unsigned char * pixels;

	int i, j, u; //Iterators
	int s; //size
	int width, height;
	int thre; //Threshold for chroma

	bool skip[9]; //Skips updates
	bool write = false;//writes frames to preview

	ofxImageSequence sequence;
	double phase;

	//Recorder
	ofxImageSequenceRecorder recorder;
	bool rec = false;
	bool allocate = false;
	bool sequenced = false;
	bool newFrame = false;
	bool cycleOn = false;
	bool preLoad = false;
	bool toggle = false;


	ofDirectory dir;


	//360 Vision
	GLUquadricObj *quadric;
	ofxFirstPersonCamera cam;
};