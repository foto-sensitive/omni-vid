#ifndef _OVWRAP // if this class hasn't been defined, the program can define it
#define _OVWRAP // by using this if statement you prevent the class to be called more than once which would confuse the compiler
#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework
#include "ofxImageSequence.h"
class ovWrap {

public: // place public functions or variables declarations here
	ovWrap();  // constructor - used to initialize an object, if no properties are passed the program sets them to the default value
		// methods, equivalent to specific functions of your class objects
	void setup(GLUquadricObj *_quadric);	// setup method, use this to setup your object's initial state
	void update();  // update method, used to refresh your objects properties
	void draw(int i, ofVideoPlayer tex, float mag, int s, ofVec2f rot);    // draw method, this where you'll do the object's drawing 
	void draw(int i, ofTexture tex, float mag, int s, ofVec2f rot);
	void draw(int i, ofxImageSequence tex, float mag, int s, ofVec2f rot);
	void sphere(float mag, ofVec2f res, int s, ofVec2f rot);
					// variables
	float x;        // position
	float y;
	float speedY;   // speed and direction
	float speedX;
	int dim;        // size
	ofColor color;  // color using ofColor type
	
	ofVec2f res;
	
	GLUquadricObj *quadric;
	
private: // place private functions or variables declarations here
}; // don't forget the semicolon!
#endif