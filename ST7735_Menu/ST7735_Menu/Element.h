#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "Colours.h"
#include "Constants.h"

#ifndef Element_h
#define Element_h

enum ElementType
{
    BUTTON,
    SELECTOR,
    SUBMENU,
    CHECKBOX,
    SLIDER,
    PAGE
};

class Element
{
public:
    virtual void displaySelected() = 0;
    virtual void display() = 0; // Pure virtual function, to be implemented by derived classes
    virtual void press() = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual int getHeight() = 0;
    virtual ~Element() {} // Virtual destructor to support polymorphism

    ElementType getType() const { return type; }

    int getWidth() const { return element_width; }
    int getTop() const { return top; }

    void setTop(int new_top) { top = new_top; }
    void setWidth(int new_width) { element_width = new_width; }

    int getDisplayOffset() { return display_offset; }
    void setDisplayOffset(int new_display_offset) { display_offset = new_display_offset; }

    void setScreen(Adafruit_ST7735 *new_screen) { screen = new_screen; }
    Adafruit_ST7735 *getScreen() const { return screen; }

protected:
    Element(ElementType elementType) : type(elementType) {}

private:
    ElementType type;
    int top;
    int display_offset = 0;
    int element_width = SCREEN_WIDTH;
    Adafruit_ST7735 *screen;
};

#endif