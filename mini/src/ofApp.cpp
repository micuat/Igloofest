#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetVerticalSync(true);
    ofSetFrameRate(15);
    ofBackground(10, 10, 10);
    ofEnableDepthTest();

    gui.setup();
    gui.add(lightPositionSlider.setup("light", ofVec3f(), ofVec3f(-10), ofVec3f(10)));
    gui.add(matRoughness.setup("roughness", 0.5f, 0, 1));
    gui.add(matSpecular.setup("specular", 0.5f, 0, 1));
    gui.add(matMetallic.setup("metallic", 0.5f, 0, 1));
    gui.loadFromFile("settings.xml");

    // turn on smooth lighting //
    ofSetSmoothLighting(true);

    // lets make a sphere with more resolution than the default //
    // default is 20 //
    ofSetSphereResolution(32);

    radius = 300.f;
    center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);

    // Point lights emit light in all directions //
    // set the diffuse color, color reflected from the light source //
    pointLight.setDiffuseColor(ofColor(0.f, 255.f, 0.f));

    // specular color, the highlight/shininess color //
    pointLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
    pointLight.setPosition(center.x, center.y, 0);

    ambientLight.setDirectional();
    ambientLight.setAmbientColor(ofColor(155.f, 155.f, 155.f));

    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess(16);


    sphereRadius = 140;
    numSpheres = 1;
    rotation = 0.f;
    bDrawWireframe = false;

    colorHue = ofRandom(0, 250);

    lightColor.setBrightness(180.f);
    lightColor.setSaturation(150.f);

    materialColor.setBrightness(250.f);
    materialColor.setSaturation(200);

    shader.load("shaders_gl3/PBR");

    world.setup();
    world.enableGrabbing();
    world.enableDebugDraw();
    world.setCamera(&camera);

    for (int i = 0; i < 16; i++)
    {
        auto sphere = ofPtr<ofxBulletSphere>(new ofxBulletSphere());
        sphere->create(world.world, ofVec3f(ofRandomf() * 0.01f, ofMap(i, 0, 16, 2, -2), ofRandomf() * 0.01f), 0.1f, 0.5f);
        sphere->setProperties(1, 0);
        sphere->add();
        spheres.push_back(sphere);
    }

    float rest = 1;
    float fric = 0;
    ofVec3f bounds(4, 4, 4);
    grounds.resize(6);
    grounds.at(0).create(world.world, ofVec3f(0., bounds.y + 0.5, 0.), 0., 100.f, 1.f, 100.f);
    grounds.at(0).setProperties(rest, fric);
    grounds.at(0).add();
    grounds.at(1).create(world.world, ofVec3f(0., -bounds.y - 0.5, 0.), 0., 100.f, 1.f, 100.f);
    grounds.at(1).setProperties(rest, fric);
    grounds.at(1).add();
    grounds.at(2).create(world.world, ofVec3f(bounds.x + 0.5, 0., 0.), 0., 1.f, 100.f, 100.f);
    grounds.at(2).setProperties(rest, fric);
    grounds.at(2).add();
    grounds.at(3).create(world.world, ofVec3f(-bounds.x - 0.5, 0., 0.), 0., 1.f, 100.f, 100.f);
    grounds.at(3).setProperties(rest, fric);
    grounds.at(3).add();
    grounds.at(4).create(world.world, ofVec3f(0., 0., bounds.z + 0.5), 0., 100.f, 100.f, 1.f);
    grounds.at(4).setProperties(rest, fric);
    grounds.at(4).add();
    grounds.at(5).create(world.world, ofVec3f(0., 0., -bounds.z - 0.5), 0., 100.f, 100.f, 1.f);
    grounds.at(5).setProperties(rest, fric);
    grounds.at(5).add();

    camera.setPosition(ofVec3f(0, -3.f, -10.f));
    camera.lookAt(ofVec3f(0, 3, 0), ofVec3f(0, -1, 0));

    iso.setup(32);

    vector<ofVec3f> centers;
    for (int i = 0; i < spheres.size(); i++) {
        centers.push_back(ofVec3f());
    }
    iso.setCenters(centers);
    iso.setRadius(2 / 32., 6 / 32.);
    iso.update();

    bloom.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {
    world.update();

    colorHue += .1f;
    if (colorHue >= 255) colorHue = 0.f;
    lightColor.setHue(colorHue);

    rotation += 1;
    if (rotation >= 360) rotation = 0;

    radius = cos(ofGetElapsedTimef()) * 200.f + 200.f;

    pointLight.setPosition(lightPositionSlider);
    pointLight.setDiffuseColor(lightColor);


    materialColor.setHue(colorHue);
    // the light highlight of the material //
    material.setSpecularColor(materialColor);

    vector<ofVec3f> centers;
    for (int i = 0; i < spheres.size(); i++) {
        auto p = spheres.at(i)->getPosition();
        centers.push_back(ofVec3f(ofMap(p.x, -5, 5, 0, 1, true), ofMap(p.y, -5, 5, 0, 1, true), ofMap(p.z, -5, 5, 0, 1, true)));
        //centers.push_back(ofVec3f(ofNoise(ofGetElapsedTimef() * 0.01f, i / 12.0f), ofNoise(ofGetElapsedTimef() * 0.02f, i / 12.0f), ofNoise(ofGetElapsedTimef() * 0.04f, i / 12.0f)));
    }
    iso.setCenters(centers);
    iso.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

    // enable lighting //
    ofEnableLighting();
    // the position of the light must be updated every frame, 
    // call enable() so that it can update itself //
    pointLight.enable();
    ambientLight.enable();

    if (bDrawWireframe) ofNoFill();
    else ofFill();

    glEnable(GL_DEPTH_TEST);
    camera.begin();

    //ofSetLineWidth(1.f);
    //ofSetColor(255, 0, 200);
    //world.drawDebug();

    //ofSetColor(100, 100, 100);
    //ground.draw();

    material.begin();

    //ofSetColor(255, 255, 255);
    //sphere->draw();
    //shader.begin();
    //for (int i = 0; i < spheres.size(); i++) spheres.at(i)->draw();
    //shader.end();

    ofPushMatrix();
    ofScale(10, 10, 10);
    ofTranslate(-.5, -.5, -.5);
    shader.begin();
    shader.setUniform3fv("uLightPosition", pointLight.getPosition().getPtr());
    shader.setUniform3fv("uLightColor", pointLight.getSpecularColor().v);
    shader.setUniform1f("uLightRadius", 1000);
    shader.setUniform3fv("uBaseColor", material.getSpecularColor().v);
    shader.setUniform1f("uSpecular", matSpecular);
    shader.setUniform1f("uExposure", 10);
    shader.setUniform1f("uGamma", 2.2f);
    shader.setUniform1f("uRoughness", matRoughness);
    shader.setUniform1f("uMetallic", matMetallic);
    iso.getMesh().draw();
    shader.end();
    ofPopMatrix();

    camera.end();

    material.end();
    // turn off lighting //
    ofDisableLighting();

    //ofSaveFrame();

    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Draw Wireframe (w) : " + ofToString(bDrawWireframe, 0), 20, 20);

    ofDisableDepthTest();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
    case 'w':
        bDrawWireframe = !bDrawWireframe;
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    pointLight.setPosition(x, y, -10);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}