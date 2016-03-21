#pragma once

#include "ofMain.h"
#include "ofxGui.h"

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
		int convolution(int x, int y, double matrix[9], int matrixsize, int iteration, unsigned char * pixels);
		float ofConstrain(float amt, float low, float high);



		unsigned char * pixelout;
		unsigned char * pixelin;
		unsigned char * pixels[2];

		ofImage img[2];
		ofImage preview;

		int i, j, u;
		int width, height;

		int pointer[3];

		int w = 80;

		float v = 1.0 / 25.0;

		// The convolution matrix for a "sharpen" effect stored as a 3 x 3 two-dimensional array.
		
		
		double matrix[25] = { v, v, v, v, v, 
			                 v, v, v, v, v,
		                   	 v, v, v, v, v,
		                     v, v, v, v, v,
		                     v, v, v, v, v};
						
				/*
		double matrix[9] = {0, -1, 0,
		                    -1, 5, -1,
		                    0, -1, 0};
			
		*/	

		ofxIntSlider thre;
		ofxPanel gui;

		int red, green, blue;

		int matrixsize, range;

};
