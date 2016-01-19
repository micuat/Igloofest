#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    lattice.setMode(OF_PRIMITIVE_POINTS);
    int n = 5;
    for (int i = -n; i <= n; i++)
    {
        for (int j = -n; j <= n; j++)
        {
            lattice.addVertex(ofVec2f(j / (float)n, i / (float)n));
        }
    }
    lines.setMode(OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update(){
    //int n = floor(ofRandom(0, lattice.getNumVertices()));
    int n = lattice.getNumVertices() / 2;
    int m = floor(ofRandom(0, lattice.getNumVertices() - 1));
    if (n <= m) m = (m + 1) % lattice.getNumVertices();

    auto pn = lattice.getVertex(n);
    auto pm = lattice.getVertex(m);
    auto pk = pn.getInterpolated(pm, 0.5f);
    auto pmn = pn - pm;
    auto pt = pmn.getRotated(90, ofVec3f(0, 0, 1)).getNormalized();
    pk += pt * ofMap(ofRandom(1), 0, 1, -pmn.length() * 0.5f, pmn.length() * 0.5f);
    lines.addVertex(pn);
    lines.addVertex(pk);
    lines.addColor(ofFloatColor(1, 1, 1, 0));
    lines.addColor(ofFloatColor(1, 1, 1, 0.125f));
    lines.addVertex(pk);
    lines.addVertex(pm);
    lines.addColor(ofFloatColor(1, 1, 1, 0.125f));
    lines.addColor(ofFloatColor(1, 1, 1, 0));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0);
    glPointSize(3);

    ofDisableDepthTest();
    ofEnableAlphaBlending();

    ofTranslate(ofGetWidth() * 0.5f, ofGetHeight() * 0.5f);
    ofScale(300, 300);
    lattice.draw();
    lines.draw();
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
