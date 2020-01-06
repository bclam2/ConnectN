//
//  ofApp.cpp
//  fantastic-finale-bclam2
//
//  Created by Benjamin Lam on 11/18/19.
//

#include "ofApp.hpp"
    
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColorHex(BACKGROUND_COLOR);
}

//--------------------------------------------------------------
void ofApp::exit(){
    
}

//--------------------------------------------------------------
void ofApp::circleResolutionChanged(int & circleResolution){
    
}

//--------------------------------------------------------------
void ofApp::ringButtonPressed(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
    controller.UpdateMessage();
    controller.UpdateEval();
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (controller.IsRenderMenu) {
        controller.RenderMenu();
    }
    
    if (controller.IsRenderBoard) {
        controller.RenderBoard();
    }
    
    if (controller.IsRenderMessage) {
        controller.RenderMessage();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (controller.IsRenderBoard) {
        if (controller.current_eval == Evaluation::NoWinner) {
            controller.board.ProcessKeyPress(key);
        } else {
            controller.ProcessEndPress(key);
        }
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
    controller.ProcessMenuPress(x, y);
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
