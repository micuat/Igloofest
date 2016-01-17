#pragma once

#include "ofMain.h"
#include "ofxBullet.h"
#include "ofxMetaballs.h"
#include "ofxAutoReloadedShader.h"
#include "ofxBloom.h"
#include "ofxImgui.h"

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

    ofxImgui gui;
    ofVec3f lightPosition, cameraPosition, cameraLookat, obstaclePosition, obstacleScale;
    float matRoughness, matSpecular, matMetallic, lightRadius, gravitySlider, centerForce, lineWidth;
    bool refreshButton;
    bool obstacleToggle;
    bool rotateToggle, rotateToggleCur;
    enum MeshMode {
        None, Wireframe, Points, Normal, Mesh
    } meshMode, meshModeCur;
    enum RenderMode {
        Metaball, Sphere, Trace, Curve, Center, MeshAssign
    } renderMode, renderModeCur;
    float centerForceCur;
    int particleNum;

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

    vector<ofMesh> traces;

    unsigned int CtextureRad, CtextureIrad;

    ofVboMesh recordedMesh;

};
