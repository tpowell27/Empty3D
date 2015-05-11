#include "ofApp.h"

//-----------------------------------------------------------------------------------------
//
void ofApp::setup()
{
    fontSmall.loadFont("Fonts/DIN.otf", 8 );
    
    //Set the camera to view the plain a an angle.
    camera.setNearClip(0.01f);
    camera.setPosition( 10, 40, 50 );
    camera.lookAt( ofVec3f( 0, 0, 0 ));
    camera.setMovementMaxSpeed( 1 );
    
    //Adds the vertexs for the mesh and initiates the color.
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            mesh.addVertex(
                           ofPoint( (x - width/2), (y - height/2), 0 ) );
            mesh.addColor( ofColor( 0, 0, 0 ) );
        }
    }
    
    //Draws the triangles onto the mesh.
    for (int y=0; y<height-1; y++) {
        for (int x=0; x<width-1; x++) {
            int i1 = x + width * y;
            int i2 = x+1 + width * y;
            int i3 = x + width * (y+1);
            int i4 = x+1 + width * (y+1);
            mesh.addTriangle( i1, i2, i3 );
            mesh.addTriangle( i2, i4, i3 );
        }
    }
    
    float time = ofGetElapsedTimef();

    //Changes the plane according to perlin noise applied to the y value of each vertex.
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            int i = x + width * y;
            ofPoint p = mesh.getVertex( i );
            
            float value = ofNoise( x * 1, y * 15, time * 0.5 );
            
            p.z = value * 15;
            mesh.setVertex( i, p );
            
            mesh.setColor( i,
                            ofColor( (value*y)*101,(value*y)*400,(value*y)*5) );
    
        }
    }
    
    setNormals( mesh );
    light.enable();
}

//-----------------------------------------------------------------------------------------
//
void ofApp::update()
{
    setNormals( mesh );
    
}

//-----------------------------------------------------------------------------------------
//
void ofApp::draw()
{
    ofBackgroundGradient( ofColor(0,0,80), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    
    ofEnableDepthTest();
    
    camera.begin();
    
    //Draws the floor grid below the landscape.
    ofSetColor( ofColor(60) );
    ofPushMatrix();
    ofRotate(90, 0, 0, -1);
    ofDrawGridPlane( 15, 15, false);
    ofPopMatrix();
    
    //Draws and rotates the landscape.
    ofPushMatrix();
    ofRotate( 90, -1, 0, 0 );
    ofTranslate(0, 0, -2.5);
    mesh.draw();
    ofPopMatrix();
    
    camera.end();
    
    ofDisableDepthTest();
}

//--------------------------------------------------------------
//Universal function which sets normals for the triangle mesh
void ofApp::setNormals( ofMesh &mesh ){
    
    //The number of the vertices
    int nV = mesh.getNumVertices();
    
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    
    vector<ofPoint> norm( nV ); //Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}

//-----------------------------------------------------------------------------------------
//
void ofApp::keyPressed(int key)
{
    if( key == 'f' )
    {
        ofToggleFullscreen();
    }
}