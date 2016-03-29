#pragma once

#include "ofMain.h"
#include "ofxImageSequence.h"
#include "ofxImageSequenceRecorder.h"

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
		void wrapSphere(int s, ofTexture tex, float mag, int i);
		double phasor(double frequency, double startphase, double endphase);
		float ofLerp(float start, float stop, float amt);

		ofVideoPlayer bg;

		ofTexture tex, tex2;
		ofImage img;

		int incX = 0;
		int incY = 0;

		int x, y;
	
		//Easing
		float easing = 0.025;
		float targetX, targetY, dx, dy;

		int centerX, centerY;

		int width, height;

		bool dont = false;
		bool doit = false;

		//360 Vision
		GLUquadricObj *quadric;

		unsigned char * pixelout;
		unsigned char * pixelin;

		int thre, pointer, red, green, blue;


		//Sequencing Images
		ofxImageSequence sequence;
		ofDirectory dir;
		double phase;
		
};
