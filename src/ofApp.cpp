#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    snake.clear();
    snake.push_back({8, 9});
    snake.push_back({9, 9});
    snake.push_back({10, 9});

    currentDirection = LEFT;
	playing = false;
	crashed = false;

    foodSpawned = false;
	foodEaten = false;
}

//--------------------------------------------------------------
void ofApp::update(){

    matrix.clear();
    for(int i = 0; i < 20; i++) {
        std::vector<int> row;
        for(int j = 0; j < 20; j++) {
            row.push_back(0);
        }
        matrix.push_back(row);
    }

    for (vector<int> bodyPart : snake) {
        int curX = bodyPart[0];
        int curY = bodyPart[1];
        matrix[curX][curY] = 1;
    }

    if(!playing) { return; }

    if(foodEaten) {
        foodSpawned = false;
        foodEaten = false;
    }

    if(!foodSpawned) {
        bool isInSnakeBody;
        do {
            isInSnakeBody = false;
            currentFoodX = ofRandom(0, 20);
            currentFoodY = ofRandom(0, 20);
            for(int i = 0; i < snake.size(); i++) {
                if(currentFoodX == snake[i][0] and currentFoodY == snake[i][1]) {
                    isInSnakeBody = true;
                }
            }
        } while(isInSnakeBody || currentFoodX == 1 || currentFoodY == 18);
        foodSpawned = true;
    }

    if(snake[0][0] == currentFoodX && snake[0][1] == currentFoodY) {
        foodEaten = true;
        // get last coord of snake
        vector<int> tail = snake[snake.size()-1];
        snake.push_back({tail[0], tail[1]});
    }

    vector<int> head = snake[0];
    for(int i = 1; i < snake.size(); i++) {
        if(head[0] == snake[i][0] and head[1] == snake[i][1]) {
            crashed = true;
            return;
        }
    }

    if(ofGetFrameNum() % 20 != 0) { return; }

    switch(currentDirection) {
        case LEFT: {
            if(snake[0][0] == 0) { crashed = true; return; }

            int prevX = snake[0][0];
            int prevY = snake[0][1];
            snake[0][0] -= 1;

            for (int i = 1; i < snake.size(); i++) {
                int currX = snake[i][0];
                int currY = snake[i][1];
                snake[i][0] = prevX;
                snake[i][1] = prevY;
                prevX = currX;
                prevY = currY;
            }

            break;
        }
        case DOWN: {
            if(snake[0][1] == 19) { crashed = true; return; }

            int prevX = snake[0][0];
            int prevY = snake[0][1];
            snake[0][1] += 1;

            for (int i = 1; i < snake.size(); i++) {
                int currX = snake[i][0];
                int currY = snake[i][1];
                snake[i][0] = prevX;
                snake[i][1] = prevY;
                prevX = currX;
                prevY = currY;
            }
            
            break;
        }
        case RIGHT: {
            if(snake[0][0] == 19) { crashed = true; return; }

            int prevX = snake[0][0];
            int prevY = snake[0][1];
            snake[0][0] += 1;

            for (int i = 1; i < snake.size(); i++) {
                int currX = snake[i][0];
                int currY = snake[i][1];
                snake[i][0] = prevX;
                snake[i][1] = prevY;
                prevX = currX;
                prevY = currY;
            }
            break;
        }
        case UP: {
            if(snake[0][1] == 0) { crashed = true; return; }

            int prevX = snake[0][0];
            int prevY = snake[0][1];
            snake[0][1] -= 1;

            for (int i = 1; i < snake.size(); i++) {
                int currX = snake[i][0];
                int currY = snake[i][1];
                snake[i][0] = prevX;
                snake[i][1] = prevY;
                prevX = currX;
                prevY = currY;
            }
            
            break;
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    // START SCREEN
    if (!playing) {
        ofSetColor(ofColor::black);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
        ofSetColor(ofColor::white);
        string text = "Press any key to start playing";
        ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
        return;
    }

    // LOST SCREEN
    if(crashed) {
        ofSetColor(ofColor::black);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
        ofSetColor(ofColor::white);
        string text = "You lost! Press Spacebar to play again.";
        ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
        return;
    }

    // DRAW BOARD GRID
    // ofSetColor(ofColor::white);
    // for(int i = 0; i <= 20; i++) {
    //     ofDrawLine(i*40, 0, i*40, ofGetHeight());
    //     ofDrawLine(0, i*40, ofGetWidth(), i*40);
    // }

    // DRAW SNAKE
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix.size(); j++) {

            if(snake[0][0] == i && snake[0][1] == j) {
                ofSetColor(ofColor::darkGreen);
            } else {
                ofSetColor(ofColor::green);
            }

            if(matrix[i][j] == 1) {
                ofDrawRectangle(i*40, j*40, 40, 40);
            }
        }
    }

    // DRAW FOOD
    ofSetColor(ofColor::red);
    if(foodSpawned && !foodEaten) {
        ofDrawRectangle(currentFoodX*40, currentFoodY*40, 40, 40);
    }

    // for (vector<int> coord : snake) {
    //     ofDrawBitmapString(ofToString(coord[0]) + ", " + ofToString(coord[1]), coord[0]*40, coord[1]*40);
    // }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(!playing) { 
        playing = true;
    }

    if(key == ' ' && crashed) {
        setup();
    }

    switch(key) {
        case OF_KEY_LEFT:
            if(currentDirection == RIGHT) { break; }
            currentDirection = LEFT;
            break;
        case OF_KEY_RIGHT:
            if(currentDirection == LEFT) { break; }
            currentDirection = RIGHT;
            break;
        case OF_KEY_UP:
            if(currentDirection == DOWN) { break; }
            currentDirection = UP;
            break;
        case OF_KEY_DOWN:
            if(currentDirection == UP) { break; }
            currentDirection = DOWN;
            break;
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
//--------------------------------------------------------------
