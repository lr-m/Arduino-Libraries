#include "Button.h"

Button::Button(const char *label, void (*onClick)()) : label(label), onClick(onClick), Element(BUTTON) {}

// Displays the button when its not hovered over/selected
void Button::display()
{
    getScreen()->fillRoundRect(MENU_SEP, (getTop() + getDisplayOffset()), getWidth() - 2 * MENU_SEP, BUTTON_HEIGHT, 2, NOT_SELECTED_COLOUR);
    getScreen()->drawTriangle(MENU_SEP + 5, getTop() + 4, MENU_SEP + 10, getTop() + 7, MENU_SEP + 5, getTop() + 10, SELECTED_TEXT_COLOUR);
    getScreen()->setCursor(MENU_SEP + 15, (getTop() + getDisplayOffset()) + (BUTTON_HEIGHT - 8) / 2);
    getScreen()->setTextColor(SELECTED_TEXT_COLOUR);
    getScreen()->print(label);
}

// Displays the button when it is hovered over/selected
void Button::displaySelected()
{
    getScreen()->fillRoundRect(MENU_SEP, (getTop() + getDisplayOffset()), getWidth() - 2 * MENU_SEP, BUTTON_HEIGHT, 2, SELECTED_COLOUR);
    getScreen()->drawTriangle(MENU_SEP + 5, getTop() + 4, MENU_SEP + 10, getTop() + 7, MENU_SEP + 5, getTop() + 10, NOT_SELECTED_TEXT_COLOUR);
    getScreen()->setCursor(MENU_SEP + 15, (getTop() + getDisplayOffset()) + (BUTTON_HEIGHT - 8) / 2);
    getScreen()->setTextColor(NOT_SELECTED_TEXT_COLOUR);
    getScreen()->print(label);
}

// Presses the button, and triggers action function
void Button::press()
{
    if (onClick != nullptr)
    {
        onClick();
    }
}

// Moves left within the button (might add a help button within)
void Button::moveLeft()
{
}

// Moves right within the button (might add a help button within)
void Button::moveRight()
{
}

// Gets the height of the button in the menu
int Button::getHeight()
{
    return BUTTON_HEIGHT + MENU_SEP;
}