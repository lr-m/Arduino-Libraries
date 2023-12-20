#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "Colours.h"
#include "Element.h"
#include "Constants.h"

#define SLIDER_TITLE_HEIGHT 13
#define SLIDER_HEIGHT 11
#define SLIDER_PADDING 10
#define SLIDER_TOP_PADDING 2
#define SLIDER_MIN_MAX_LABEL_HEIGHT 12
#define SLIDER_BOTTOM_PADDING 2

#ifndef Slider_h
#define Slider_h

class Slider : public Element
{
public:
    Slider(const char *label, int low, int high, int step, int start, const char *id);

    void display() override;
    void displaySelected() override;
    void press() override;
    void moveLeft() override;
    void moveRight() override;
    int getHeight() override;

    void drawSlider();
    void drawRangeLabels(bool highlighted);
    
    const char *getId() const { return id; }
    int getValue() const { return value; }

private:
    const char *label;
    const char *id;
    int value;
    int high;
    int low;
    int step;
};

#endif