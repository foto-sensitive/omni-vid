#pragma once

#include "ofMain.h"
#include "ovWrap.h"
#include "ofxImageSequence.h"
#include "ofxImageSequenceRecorder.h"

#define NWRAPS 2

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		double phasor(double frequency, double startphase, double endphase);
		void layers();

		ofVideoPlayer bg;
		ofVideoPlayer *vid;

		int *test;

		ofTexture tex, tex2;
		ofImage img;

		int incX = 0;
		int incY = 0;
		int inc = 10;

		ofVec2f v1, translate; // v1.x is 0, v1.y is 0

		char c; //for integer to character conversion

		bool selected;

		int sel = 0; //Layer Selection

		int width, height;

		bool dont = false;
		bool doit = false;

		//360 Vision
		GLUquadricObj *quadric;

		unsigned char * pixelout;
		unsigned char * pixelin;

		int thre, pointer, red, green, blue;

		int i, j, u; //Iterators


		//Sequencing Images
		ofxImageSequence sequence;
		ofDirectory dir;
		double phase;

		ovWrap myWrap[NWRAPS];
		
};
