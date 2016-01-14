#pragma once

#include "ofMain.h"
#include "ofxBullet.h"
#include "ofxGui.h"
#include "ofxMetaballs.h"
#include "ofxAutoReloadedShader.h"
#include "ofxBloom.h"

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofxPanel gui;
    ofxVec3Slider lightPosition, cameraPosition, obstaclePosition, obstacleScale;
    ofxFloatSlider matRoughness, matSpecular, matMetallic, lightRadius, gravitySlider, centerForce, lineWidth;
    ofxToggle refreshButton;
    ofxToggle metaballToggle, traceToggle, curveToggle, sphereToggle, obstacleToggle;
    bool metaballToggleCur, traceToggleCur, curveToggleCur, sphereToggleCur;
    float centerForceCur;
    ofxIntSlider particleNum;

    ofLight pointLight, ambientLight;

    float rotation;

    float radius;
    float sphereRadius;
    int numSpheres;
    ofVec3f center;
    bool bDrawGui;

    ofColor lightColor;
    float colorHue;
    ofColor materialColor;

    ofMaterial material;

    ofxAutoReloadedShader shader;

    ofxBulletWorldRigid world;
    vector<ofxBulletBox> grounds;
    ofPtr<ofxBulletBox> obstacleBox;
    ofCamera camera;

    vector<ofPtr<ofxBulletSphere> > spheres;

    MarchingCubes iso;

    ofxBloom        bloom;

    ofNode scene;

    ofImage skyboxImage;

    vector<ofMesh> traces, curves;

    unsigned int CtextureRad, CtextureIrad;

};
