#include "Slider.h"

Slider::Slider(const char *label, int low, int high, int step, int start, const char *id) : value(start), label(label), low(low), high(high), id(id), step(step), Element(SLIDER) {}

// Displays the slider when its not hovered over/selected
void Slider::display()
{
    int16_t x, y;
    uint16_t width, height;

    getScreen()->getTextBounds(label, MENU_SEP, (getTop() + getDisplayOffset()), &x, &y, &width, &height);
    getScreen()->setCursor(MENU_SEP + getWidth() / 2 - width / 2, (getTop() + getDisplayOffset()) + SLIDER_TOP_PADDING);
    getScreen()->setTextColor(DARK_GREY);
    getScreen()->print(label);
    drawSlider();
    drawRangeLabels(false);
}

// Displays the slider when it is hovered over/selected
void Slider::displaySelected()
{
    int16_t x, y;
    uint16_t width, height;

    getScreen()->getTextBounds(label, MENU_SEP, (getTop() + getDisplayOffset()), &x, &y, &width, &height);
    getScreen()->setCursor(MENU_SEP + getWidth() / 2 - width / 2, (getTop() + getDisplayOffset()) + SLIDER_TOP_PADDING);
    getScreen()->setTextColor(SELECTED_TEXT_COLOUR);
    getScreen()->print(label);
    drawSlider();
    drawRangeLabels(true);
}

// Display the slider
void Slider::drawSlider()
{
    int16_t x, y;
    uint16_t width, height;
    char charArray[12];

    // Convert the integer to a char array
    itoa(value, charArray, 10);

    getScreen()->getTextBounds(charArray, MENU_SEP, (getTop() + getDisplayOffset()), &x, &y, &width, &height);

    // Calculate the meeting point based on the slider value
    int meeting_point = map(value, low, high, SLIDER_PADDING, getWidth() - SLIDER_PADDING);
    getScreen()->fillRoundRect(SLIDER_PADDING, (getTop() + getDisplayOffset()) + SLIDER_TITLE_HEIGHT, meeting_point - SLIDER_PADDING, SLIDER_HEIGHT, 2, SELECTED_COLOUR);
    getScreen()->fillRoundRect(meeting_point, (getTop() + getDisplayOffset()) + SLIDER_TITLE_HEIGHT, getWidth() - SLIDER_PADDING - meeting_point, SLIDER_HEIGHT, 2, NOT_SELECTED_COLOUR);

    // Draw the slider value, moving to other side if the size of the value overflow the containing slider
    if (width + meeting_point + 4 < getWidth() - SLIDER_PADDING)
    {
        getScreen()->setTextColor(SELECTED_TEXT_COLOUR);
        getScreen()->setCursor(meeting_point + 4, (getTop() + getDisplayOffset()) + SLIDER_TITLE_HEIGHT + 2);
    }
    else
    {
        getScreen()->setTextColor(DARK_GREY);
        getScreen()->setCursor(meeting_point - 4 - width, (getTop() + getDisplayOffset()) + SLIDER_TITLE_HEIGHT + 2);
    }
    getScreen()->print(value);
}

// Draws the slider range labels
void Slider::drawRangeLabels(bool highlighted)
{
    int16_t x, y;
    uint16_t width, height;
    char charArray[12];

    if (highlighted)
    {
        getScreen()->setTextColor(SELECTED_TEXT_COLOUR);
    }
    else
    {
        getScreen()->setTextColor(DARK_GREY);
    }

    getScreen()->setCursor(SLIDER_PADDING, (getTop() + getDisplayOffset()) + SLIDER_TITLE_HEIGHT + SLIDER_HEIGHT + 4);
    getScreen()->print(low);

    itoa(high, charArray, 10);
    getScreen()->getTextBounds(charArray, MENU_SEP, (getTop() + getDisplayOffset()), &x, &y, &width, &height);
    getScreen()->setCursor(getWidth() - width - SLIDER_PADDING, (getTop() + getDisplayOffset()) + SLIDER_TITLE_HEIGHT + SLIDER_HEIGHT + 4);
    getScreen()->print(charArray);
}

// Presses the button, and triggers action function
void Slider::press()
{
}

// moves the slider right by step amount
void Slider::moveLeft()
{
    value = std::max(low, value - step);
    drawSlider();
}

// moves the slider left by step amount
void Slider::moveRight()
{
    value = std::min(high, value + step);
    drawSlider();
}

// Gets the height of the button in the menu
int Slider::getHeight()
{
    return SLIDER_TITLE_HEIGHT + SLIDER_HEIGHT + MENU_SEP + SLIDER_MIN_MAX_LABEL_HEIGHT + SLIDER_BOTTOM_PADDING;
}