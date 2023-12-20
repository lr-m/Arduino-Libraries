#include "RetroController.h"
#include <Arduino.h>

Controller::Controller(int latchPin, int pulsePin, int responsePin){
	this->pulsePin = pulsePin;
	this->latchPin = latchPin;
	this->responsePin = responsePin;
	
	pinMode(pulsePin, OUTPUT);
	pinMode(latchPin, OUTPUT);
	pinMode(responsePin, INPUT);
	
	this->poll();
}

// Checks if button at index is pressed
bool Controller::isPressed(int btnIndex){
	if (this->pressed[btnIndex] == 1){
		return true;
	} else {
		return false;
	}
}

// Polls controller for pressed buttons
char* Controller::poll(){
	// Set the latch pin high
	digitalWrite(this->latchPin, HIGH);
	digitalWrite(this->latchPin, LOW);

	for (int i = 0; i < 8; i++){   
		// Check if index is low
		if (digitalRead(this->responsePin) == LOW){
		  this->pressed[i] = 1;
		} else {
		  this->pressed[i] = 0;
		}

		// Send pulse
		digitalWrite(this->pulsePin, HIGH);
		digitalWrite(this->pulsePin, LOW);
	}
	
	return this->pressed;
}
