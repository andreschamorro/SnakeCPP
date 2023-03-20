#pragma once

#include "ofMain.h"
#include <vector>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		enum DIRECTIONS {
			LEFT,
			RIGHT,
			UP,
			DOWN,
			NONE
		};
		DIRECTIONS currentDirection;
		bool playing = false;
		bool crashed = false;

		std::vector<std::vector<int>> matrix;
		std::vector<std::vector<int>> snake; // i[0] is x and i[1] is y

		bool foodSpawned = false;
		bool foodEaten = false;

		int currentFoodX;
		int currentFoodY;

		
};
