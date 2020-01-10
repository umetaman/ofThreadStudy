#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//スパイク確認用のボール
	position = ofVec2f(
		ofRandom(radius, ofGetWidth() - radius),
		ofRandom(radius, ofGetHeight() - radius));
	add = ofVec2f(ofRandom(-5, 5), ofRandom(-5, 5));
}

//--------------------------------------------------------------
void ofApp::update(){
	if (isLoading == true && csvLoader.isLoaded) {
		csv = &csvLoader.csv;
		isLoading = false;
		cout << csv->getNumCols() << ", " << csv->getNumRows() << "\n";
	}

	cout << "update." << "\n";

	//スパイク確認用のボール
	position += add;
	if (position.x < 0 + radius || position.x > ofGetWidth() - radius) {
		add.x *= -1;
	}

	if (position.y < 0 + radius || position.y > ofGetHeight() - radius) {
		add.y *= -1;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//スパイク確認用のボール
	ofSetColor(255, 0, 0);
	ofDrawCircle(position, radius);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case OF_KEY_RETURN:
		if (isLoading == false) {
			csvLoader.url = "http://your-own-url";
			isLoading = true;
			csvLoader.startThread();
		}
	case OF_KEY_DEL:
		csvLoader.reset();
	}
	
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
