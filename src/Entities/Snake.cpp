#include "Snake.h"
#include "ofMain.h"

Snake::Snake() {
    body.push_back({8, 9});
    body.push_back({9, 9});
    body.push_back({10, 9});
    direction = LEFT;
    crashed = false;
}

Snake::~Snake() {
    // TODO Auto-generated destructor stub
}

void Snake::update() {
    std::vector<std::vector<int>> snake = this->body;
    switch(this->direction) {
        case LEFT: {
            if(snake[0][0] == 0) { this->crashed = true; return; }

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
    this->body = snake;
    checkSelfCrash();

    if(this->getHead()[0] == currentFoodX && this->getHead()[1] == currentFoodY) {
        grow();
        ateFood = true;
    }

}

void Snake::draw() {
    for (int i = 0; i < body.size(); i++) {
        int curX = this->body[i][0];
        int curY = this->body[i][1];
        ofSetColor(ofColor::green);
        ofDrawRectangle(curX * 40+2, curY * 40+2, 36, 36);
    }
    ofSetColor(ofColor::darkGreen);
    ofDrawRectangle(this->getHead()[0] * 40+2, this->getHead()[1] * 40+2, 36, 36);
}

void Snake::changeDirection(Direction d) {

    if(this->direction == LEFT and d == RIGHT)
        return;
    if(this->direction == RIGHT and d == LEFT) 
        return;
    if(this->direction == UP and d == DOWN) 
        return;
    if(this->direction == DOWN and d == UP)
        return;
    
    this->direction = d;
}

void Snake::checkSelfCrash() {
    std::vector<std::vector<int>> snake = this->body;
    vector<int> head = snake[0];
    for(int i = 1; i < snake.size(); i++) {
        if(head[0] == snake[i][0] and head[1] == snake[i][1]) {
            crashed = true;
            return;
        }
    }
}

void Snake::grow() {
    this->body.push_back(this->getTail());
}