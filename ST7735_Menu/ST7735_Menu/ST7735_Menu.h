// ESPIR_Menu.h
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "Colours.h"
#include "Checkbox.h"
#include "Button.h"
#include "Selector.h"
#include "Submenu.h"
#include "Constants.h"
#include "Page.h"
#include "Slider.h"
#include <climits>

#ifndef Menu_h
#define Menu_h

#define SCROLLBAR_WIDTH 5
#define SCROLLBAR_PADDING 2

class Menu
{
public:
    Menu(Adafruit_ST7735 *display);
    void addElement(Element *element);
    
    void display();
    void moveUp();
    void moveDown();
    void press();
    void moveLeft();
    void moveRight();
    void back();

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

    void drawScrollbar(int top, int bottom);

private:
    std::vector<Element *> elements;
    size_t selectedElementIndex;
    bool entered;
    Adafruit_ST7735 *screen;
    int base_display_height = 0;
    int menu_height = 0;
    bool scrollable = false;
    int end_display_height = 0;
};

#endif