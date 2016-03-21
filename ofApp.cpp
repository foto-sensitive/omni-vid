#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	img[0].loadImage("japan.bmp");
	img[1].loadImage("hades.bmp");

	width = img[0].getWidth();
	height = img[0].getHeight();

	pixelout = new unsigned char[width* height * 3];//Assigns length to array
	pixelin = new unsigned char[width* height * 3];
	pixels = new unsigned char[width* height * 3];


	ofSetVerticalSync(true);

	gui.setup(); // most of the time you don't need a name
	gui.add(thre.setup("Threshold", 254, 0, 256));


	matrixsize = sqrt(sizeof(matrix) / sizeof(*matrix));
	range = floor(matrixsize / 2);

}

//--------------------------------------------------------------
void ofApp::update(){


	for (u = 0; u < 2; u++) {

		pixelin = img[u].getPixels();//Gets pixels from video

		for (int i = range; i < width-range; i++) {
			for (int j = range; j < height-range; j++) {


				pointer[0] = (j*width + i);
				red = pixelin[pointer[0] * 3 + 0];//red
				green = pixelin[pointer[0] * 3 + 1];//green
				blue = pixelin[pointer[0] * 3 + 2];//blue


				if (u == 0 ||  green <= blue || green <= red || green < thre) {


					pixelout[pointer[0] * 3 + 0] = red;
					pixelout[pointer[0] * 3 + 1] = green;
					pixelout[pointer[0] * 3 + 2] = blue;

					//pixelout[pointer[0] * 3 + 2] = convolution(i, j, matrix, matrixsize, 2, pixelin);//blue

				}
			}
		}
	}

	preview.setFromPixels(pixelout, width, height, OF_IMAGE_COLOR);//Writes pixels to preview sequence

}

//--------------------------------------------------------------
void ofApp::draw(){

	preview.draw(0, 0, img[0].getWidth()*0.5, img[0].getHeight()*0.5);

	gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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

int ofApp::convolution(int x, int y, double matrix[25], int matrixsize, int iteration, unsigned char * pixels) {

	float sum = 0; // Kernel sum for this pixel


			for (int ky = -range; ky <= range; ky++) {
				for (int kx = -range; kx <= range; kx++) {

					// Calculate the adjacent pixel for this kernel point
					//int pos = (y + ky) * width + (x + kx) * 3 + iteration;
					//Reads 1D array as 2D
					int pos = ((y + ky)*width + (x + kx))*3 + iteration;

					// Image is grayscale, red/green/blue are identical
					float val = pixels[pos];

					//Reads 1D array as 2D
					int count = j * matrixsize + i;

					// Multiply adjacent pixels based on the kernel values
					sum += matrix[count] * val;
				}
			}
	
	sum = ofConstrain(sum, 0, 255);
	return sum;
}

//--------------------------------------------------------------
float ofApp::ofConstrain(float amt, float low, float high) {
	return (amt < low) ? low : ((amt > high) ? high : amt);
}
