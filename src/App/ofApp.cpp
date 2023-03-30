#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    snake = new Snake();
	crashed = false;
    foodSpawned = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    if(!playing) { return; }
    
    foodSpawner();
    if(ofGetFrameNum() % 20 == 0) {
        snake->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    // START SCREEN
    if (!playing && !snake->isCrashed()) {
        drawStartScreen();
        return;
    }

    // LOST SCREEN
    if(snake->isCrashed()) {
        drawLostScreen();
        playing = false;
        return;
    }

    drawBoardGrid();
    snake->draw();
    drawFood();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key != OF_KEY_LEFT && key != OF_KEY_RIGHT && key != OF_KEY_UP && key != OF_KEY_DOWN) { return; }

    if(!playing) { 
        playing = true;
    }

    if(snake->isCrashed()) {
        delete snake;
        setup();
    }

    switch(key) {
        case OF_KEY_LEFT:
            snake->changeDirection(Snake::LEFT);
            break;
        case OF_KEY_RIGHT:
            snake->changeDirection(Snake::RIGHT);
            break;
        case OF_KEY_UP:
            snake->changeDirection(Snake::UP);
            break;
        case OF_KEY_DOWN:
            snake->changeDirection(Snake::DOWN);
            break;
    }
}
//--------------------------------------------------------------
void ofApp::foodSpawner() {
    if(snake->ateFood) {
        foodSpawned = false;
    }

    if(!foodSpawned) {
        bool isInSnakeBody;
        do {
            isInSnakeBody = false;
            currentFoodX = ofRandom(0, 20);
            currentFoodY = ofRandom(0, 20);
            for(int i = 0; i < snake->getBody().size(); i++) {
                if(currentFoodX == snake->getBody()[i][0] and currentFoodY == snake->getBody()[i][1]) {
                    isInSnakeBody = true;
                }
            }
        } while(isInSnakeBody || currentFoodX == 1 || currentFoodY == 18);
        foodSpawned = true;
        snake->currentFoodX = currentFoodX;
        snake->currentFoodY = currentFoodY;
        snake->ateFood = false;
    }
}
//--------------------------------------------------------------
void ofApp::drawFood() {
    ofSetColor(ofColor::red);
    if(foodSpawned && !snake->ateFood) {
        ofDrawRectangle(currentFoodX*40, currentFoodY*40, 40, 40);
    }
}
//--------------------------------------------------------------
void ofApp::drawStartScreen() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "Press any arrow key to start.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    return;
}
//--------------------------------------------------------------
void ofApp::drawLostScreen() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "You lost! Press any arrow key to play again";
    string text2 = "or press ESC to exit.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    ofDrawBitmapString(text2, ofGetWidth()/2-8*text2.length()/2, ofGetHeight()/2+2);
    return;
}
//--------------------------------------------------------------
void ofApp::drawBoardGrid() {
    ofSetColor(ofColor::white);
    for(int i = 0; i <= 20; i++) {
        ofDrawLine(i*40, 0, i*40, ofGetHeight());
        ofDrawLine(0, i*40, ofGetWidth(), i*40);
    }
}
//--------------------------------------------------------------