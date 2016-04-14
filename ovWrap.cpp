#include "ovWrap.h"
ovWrap::ovWrap() {
}

void ovWrap::setup(GLUquadricObj *_quadric) {
	
	quadric = _quadric;

}

void ovWrap::update(ofVec2f *_rot, bool selected){

	if (selected) {
		
		if (once) {
			
			//Doesn't do proper cacheing of coordinates, why
			store.x = x;
			store.y = y;
			previous.x = _rot->x;
			previous.y = _rot->y;
			once = false;
		}
		x = _rot->x - (previous.x - store.x);
		y = _rot->y - (previous.y - store.y);
	}
	else {
		if(!once)
		once = true;
	}

}

//--------------------------------------------------------------

void ovWrap::draw(int i, ofVideoPlayer *tex, float mag, int s) {
	res.x = tex->getWidth();//Passing resolution to sphere
	res.y = tex->getHeight();
	tex->bind();
	sphere(mag, res, s);
	tex->unbind();
}

//--------------------------------------------------------------

void ovWrap::draw(int i, ofTexture *tex, float mag, int s) {
	res.x = tex->getWidth();
	res.y = tex->getHeight();
	tex->bind();
	sphere(mag, res, s);
	tex->unbind();
}

//--------------------------------------------------------------

void ovWrap::draw(int i, ofxImageSequence *tex, float mag, int s) {
	res.x = tex->getWidth();
	res.y = tex->getHeight();
	tex->getTextureReference().bind();
	sphere(mag, res, s);
	tex->getTextureReference().unbind();
}


//--------------------------------------------------------------

void ovWrap::sphere(float mag, ofVec2f res, int s) {
	ofSetColor(255, 255, 255);

	ofPushMatrix();

	ofTranslate(ofGetWidth() / 2, 360, 650);
	ofRotateX(y*mag + ofNoise(1, ofGetFrameNum() / 12.0) * ofGetWidth()*0.001);
	ofRotateZ(x*mag + ofNoise(2, ofGetFrameNum() / 12.0) * ofGetHeight()*0.001);

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