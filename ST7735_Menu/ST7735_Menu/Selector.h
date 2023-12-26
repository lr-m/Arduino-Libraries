#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "Colours.h"
#include "Constants.h"
#include "Element.h"

#define SELECTOR_HEIGHT 30
#define SELECTOR_TITLE_OFFSET 2
#define SELECTOR_TITLE_HEIGHT 10
#define SELECTOR_SPACING 10
#define SELECTOR_OPTION_BG_OFFSET 13
#define SELECTOR_OPTION_BG_HEIGHT 14
#define SELECTOR_OPTION_BG_PADDING 6
#define SELECTOR_OPTION_TEXT_OFFSET 16
#define SELECTOR_OPTION_TEXT_BG_OFFSET 3
#define SELECTOR_ROW_HEIGHT 15

#ifndef Selector_h
#define Selector_h

class Selector : public Element
{
public:
    Selector(const char *label, const char **option_labels, int *option_values, int option_count, const char *id, uint8_t starting);

    void display() override;
    void displaySelected() override;
    void press() override{};
    void moveLeft() override;
    void moveRight() override;
    int getHeight() override;

    bool serialize(byte *buffer, int *index) override;
    bool deserialize(byte *buffer, int *index) override;

    void drawItems();
    void drawSingleItem(int index);

    uint8_t getSelectedIndex() const { return selectedOptionIndex; }
    void setSelectedIndex(uint8_t new_selected_option_index) { selectedOptionIndex = new_selected_option_index; }

    int getValue();
    void toDefault() override { selectedOptionIndex = starting; };

    const char *getId() const { return id; }

private:
    const char *label;
    const char **option_labels;
    const char *id;
    int *option_values;
    int *value;
    uint8_t selectedOptionIndex;
    int option_count;
    uint8_t starting;
};

#endif