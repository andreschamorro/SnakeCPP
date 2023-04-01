#pragma once

#include "ofMain.h"
#include "State.h"
#include "GameState.h"
#include "MenuState.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		// void keyReleased(int key);
		// void mouseMoved(int x, int y );
		// void mouseDragged(int x, int y, int button);
		// void mousePressed(int x, int y, int button);
		// void mouseReleased(int x, int y, int button);
		// void mouseEntered(int x, int y);
		// void mouseExited(int x, int y);
		// void windowResized(int w, int h);
		// void dragEvent(ofDragInfo dragInfo);
		// void gotMessage(ofMessage msg);
		void foodSpawner();
		void drawFood();
		void drawStartScreen();
		void drawLostScreen();
		void drawBoardGrid();

		Snake* snake;

		bool playing = false;
		bool crashed = false;
		bool foodSpawned = false;

		int currentFoodX;
		int currentFoodY;

		int boardSizeWidth, boardSizeHeight;
		int cellSize; // Pixels

		State* currentState;
		GameState* gameState;
		MenuState* menuState;
		
};
