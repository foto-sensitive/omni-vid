#pragma once

#include "ofMain.h"
#include "ofxImageSequence.h"
#include "ofxImageSequenceRecorder.h"

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
	void exit();

	string path; //Path of dragged file

				 //Contain videos
	vector <ofVideoPlayer> videos;
	ofImage preview;
	ofImage test;
	unsigned char * pixelout;
	unsigned char * pixelin;

	int i; //Iterator
	int s; //size
	int width, height;

	bool skip[9]; //Skips updates
	bool write = false;//writes frames to preview

	ofxImageSequence sequence;
	bool playing;
	double phase;

	//Recorder
	ofxImageSequenceRecorder recorder;
	bool rec;
	bool allocate = false;
	bool sequenced = false;
	bool newFrame = false;
	bool cycle = false;
	bool preLoad = false;


	ofDirectory dir;
};