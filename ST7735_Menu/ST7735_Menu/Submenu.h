#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "Colours.h"
#include "Constants.h"
#include "Button.h"
#include "Selector.h"
#include "Checkbox.h"
#include "Slider.h"
#include "Page.h"
#include <climits>

#define SUBMENU_HEIGHT 14

#define SUBMENU_LINE_COUNT 3
#define SUBMENU_LINE_SEP 3
#define SUBMENU_LINE_H_OFFSET 6
#define SUBMENU_LINE_V_OFFSET 3
#define SUBMENU_LINE_H_LENGTH 8

#define SCROLLBAR_WIDTH 5
#define SCROLLBAR_PADDING 2

#ifndef Submenu_h
#define Submenu_h

class Submenu : public Element
{
public:
    Submenu(const char *label, Adafruit_ST7735 *screen);
    void addElement(Element *element);

    bool isDrawn() const { return drawn; }
    bool isInSubmenu() const { return entered; }
    void setDrawn(bool draw) { drawn = draw; }

    void display() override;
    void displaySelected() override;
    void press() override;
    void moveLeft() override;
    void moveRight() override;
    int getHeight() override;

    void moveUp();
    void moveDown();
    void back();
    void drawMenu();
    void drawScrollbar(int top, int bottom);

    bool getSelectorValue(const char *, int *);
    bool getCheckboxValue(const char *, bool *);
    bool getSliderValue(const char *, int *);

    void setBaseDisplayHeight(int new_base_display_height) { base_display_height = new_base_display_height; }
    int getBaseDisplayHeight() const { return base_display_height; }
    void setEndDisplayHeight(int new_end_display_height) { end_display_height = new_end_display_height; }
    int getEndDisplayHeight() const { return end_display_height; }
    void setMenuHeight(int new_menu_height) { menu_height = new_menu_height; }
    int getMenuHeight() const { return menu_height; }

    bool getScrollable() const { return scrollable; }
    void setScrollable(bool is_scrollable) { scrollable = is_scrollable; }

private:
    bool drawn;
    bool entered;
    int base_display_height = 0;
    int end_display_height = 0;
    const char *label;
    int menu_height = 0;
    size_t selectedElementIndex;
    bool scrollable = false;
    std::vector<Element *> elements;
};

#endif