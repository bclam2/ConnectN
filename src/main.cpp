//
//  main.cpp
//  fantastic-finale-bclam2
//
//  Created by Benjamin Lam on 11/18/19.
//

#include "ofMain.h"
#include "ofApp.hpp"

//========================================================================
int main( ){
    ofSetupOpenGL(BACKGROUND_SIZE, BACKGROUND_SIZE, OF_WINDOW);            // <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp( new ofApp());

}
