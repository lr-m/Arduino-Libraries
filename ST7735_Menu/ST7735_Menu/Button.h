#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "Colours.h"
#include "Element.h"
#include "Constants.h"

#define BUTTON_HEIGHT 14

#ifndef Button_h
#define Button_h

class Button : public Element
{
public:
    Button(const char *label, void (*onClick)());
    void display() override;
    void displaySelected() override;
    void press() override;
    void moveLeft() override;
    void moveRight() override;
    int getHeight() override;

private:
    const char *label;
    void (*onClick)();
};

#endif