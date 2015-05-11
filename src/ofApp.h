#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "Math/MathUtils.h"

#include "Utils/ofTrueTypeFontExt.h"
#include "Utils/Cameras/ofxWalkingFirstPersonCamera.h"

class ofApp : public ofBaseApp
{
	public:
		
		void setup();
		void update();
		void draw();
		void setNormals(ofMesh &mesh);
		void keyPressed(int key);
    
    
    
        ofMesh mesh;
        ofLight light;
        int width = 31;
        int height = 31;
        int depth = 31;
	
		ofxFirstPersonCamera	camera;
    
        ofTrueTypeFontExt		fontSmall;
    
};
