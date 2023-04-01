#pragma once
#include <vector>

class Snake {

private:
    std::vector<std::vector<int>> body;
    bool crashed;

public:
    enum Direction {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NONE
    };
    Snake(int segmentSize, int boardSizeW, int boardSizeH);
    ~Snake();

    void update();
    void draw();
    void changeDirection(Direction d);
    void checkSelfCrash();
    void grow();
    bool isCrashed() {
        return this->crashed;
    }
    std::vector<int> getHead() {
        return this->body[0];
    }
    std::vector<int> getTail() {
        return this->body[this->body.size() - 1];
    }
    std::vector<std::vector<int>> getBody() {
        return this->body;
    }

    Direction direction;
    int currentFoodX, currentFoodY;
    int boardSizeWidth, boardSizeHeight;
    int segmentSize;
    bool ateFood;
};
