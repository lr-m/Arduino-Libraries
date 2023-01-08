#ifndef RetroController_h
#define RetroController_h

// Button index names
#define B 		0
#define Y 		1
#define SELECT 	2
#define START 	3
#define UP 		4
#define DOWN 	5
#define LEFT 	6
#define RIGHT 	7

class Controller {
	public:
		Controller(int, int, int);
		char* poll();
		bool isPressed(int);
		
	private:
		char pressed[8];
		int pulsePin;
		int latchPin;
		int responsePin;
};

#endif