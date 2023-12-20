#include "Checkbox.h"

Checkbox::Checkbox(const char *label, const char *id) : label(label), id(id), Element(CHECKBOX), value(false) {}

// Displays the checkbox when its not hovered over/selected
void Checkbox::display()
{
    getScreen()->setCursor(MENU_SEP, (getTop() + getDisplayOffset()));
    getScreen()->setTextColor(DARK_GREY);
    getScreen()->print(label);

    drawCheckbox();
}

// Displays the checkbox when it is hovered over/selected
void Checkbox::displaySelected()
{
    getScreen()->setCursor(MENU_SEP, (getTop() + getDisplayOffset()));
    getScreen()->setTextColor(SELECTED_TEXT_COLOUR);
    getScreen()->print(label);

    drawCheckbox();
}

// Draws the red/green checkbox
void Checkbox::drawCheckbox()
{
    if (value)
    {
        getScreen()->fillRoundRect(getWidth() - MENU_SEP - CHECKBOX_SIZE, (getTop() + getDisplayOffset()), CHECKBOX_SIZE, CHECKBOX_SIZE, 2, GREEN);
    }
    else
    {
        getScreen()->fillRoundRect(getWidth() - MENU_SEP - CHECKBOX_SIZE, (getTop() + getDisplayOffset()), CHECKBOX_SIZE, CHECKBOX_SIZE, 2, RED);
    }
}

// Presses the checkbox, and triggers action function
void Checkbox::press()
{
    value = !value;
    drawCheckbox();
}

// Moves left within the checkbox
void Checkbox::moveLeft()
{
}

// Moves right within the checkbox
void Checkbox::moveRight()
{
}

// Gets the height of the checkbox in the menu
int Checkbox::getHeight()
{
    return CHECKBOX_HEIGHT;
}