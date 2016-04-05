#include "ovWrap.h"
ovWrap::ovWrap() {
}

void ovWrap::setup(GLUquadricObj *_quadric) {
	
	quadric = _quadric;

}

void ovWrap::update() {

}

//--------------------------------------------------------------

void ovWrap::draw(int i, ofVideoPlayer tex, float mag, int s, ofVec2f rot) {
	res.x = tex.getWidth();//Passing resolution to sphere
	res.y = tex.getHeight();
	tex.bind();
	sphere(mag, res, s, rot);
	tex.unbind();
}

//--------------------------------------------------------------

void ovWrap::draw(int i, ofTexture tex, float mag, int s, ofVec2f rot) {
	res.x = tex.getWidth();
	res.y = tex.getHeight();
	tex.bind();
	sphere(mag, res, s, rot);
	tex.unbind();
}

//--------------------------------------------------------------

void ovWrap::draw(int i, ofxImageSequence tex, float mag, int s, ofVec2f rot) {
	res.x = tex.getWidth();
	res.y = tex.getHeight();
	tex.getTextureReference().bind();
	sphere(mag, res, s, rot);
	tex.getTextureReference().unbind();
}


//--------------------------------------------------------------

void ovWrap::sphere(float mag, ofVec2f res, int s, ofVec2f rot) {
	ofSetColor(255, 255, 255);

	ofPushMatrix();

	ofTranslate(ofGetWidth() / 2, 360, 650);
	ofRotateX(rot.y*mag);
	ofRotateZ(rot.x*mag);

	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	ofScale(res.x, res.y);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST); //enable depth comparisons NEEDED FOR SPHERE DEPTH
	ofDisableArbTex(); //needed for textures to work with gluSphe

	gluSphere(quadric, s, 100, 100);

	glDisable(GL_DEPTH_TEST);//disable depth comparisons NEEDED FOR FLAT MASK
	ofEnableArbTex(); //needed for textures to work with gluSphe


	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	ofPopMatrix();
}