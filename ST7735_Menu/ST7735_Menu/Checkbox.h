#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "Colours.h"
#include "Element.h"
#include "Constants.h"

#define CHECKBOX_HEIGHT 12
#define CHECKBOX_SIZE 8
#define CHECKBOX_PADDING 10

#ifndef Checkbox_h
#define Checkbox_h

class Checkbox : public Element
{
public:
    Checkbox(const char *label, const char *id);
    void display() override;
    void displaySelected() override;
    void press() override;
    void moveLeft() override;
    void moveRight() override;
    int getHeight() override;

    void drawCheckbox();
    const char *getId() const { return id; }
    bool getValue() const { return value; }
    void setValue(bool new_value) { value = new_value; }

private:
    const char *label;
    const char *id;
    bool value;
};

#endif