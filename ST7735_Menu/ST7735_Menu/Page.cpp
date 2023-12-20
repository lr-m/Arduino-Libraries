#include "Page.h"

Page::Page(const char *label) : label(label), Element(PAGE) {}
Page::Page() : Element(PAGE) {}

// Displays the button when its not hovered over/selected
void Page::display()
{
    getScreen()->fillRoundRect(MENU_SEP, (getTop() + getDisplayOffset()), getWidth() - 2 * MENU_SEP, PAGE_HEIGHT, 2, NOT_SELECTED_COLOUR);
    getScreen()->fillTriangle(MENU_SEP + 5, getTop() + 4, MENU_SEP + 10, getTop() + 7, MENU_SEP + 5, getTop() + 10, SELECTED_TEXT_COLOUR);
    getScreen()->setCursor(MENU_SEP + 15, (getTop() + getDisplayOffset()) + (PAGE_HEIGHT - 8) / 2);
    getScreen()->setTextColor(SELECTED_TEXT_COLOUR);
    getScreen()->print(label);
}

// Displays the button when it is hovered over/selected
void Page::displaySelected()
{
    getScreen()->fillRoundRect(MENU_SEP, (getTop() + getDisplayOffset()), getWidth() - 2 * MENU_SEP, PAGE_HEIGHT, 2, SELECTED_COLOUR);
    getScreen()->fillTriangle(MENU_SEP + 5, getTop() + 4, MENU_SEP + 10, getTop() + 7, MENU_SEP + 5, getTop() + 10, NOT_SELECTED_TEXT_COLOUR);
    getScreen()->setCursor(MENU_SEP + 15, (getTop() + getDisplayOffset()) + (PAGE_HEIGHT - 8) / 2);
    getScreen()->setTextColor(NOT_SELECTED_TEXT_COLOUR);
    getScreen()->print(label);
}

// Presses the button, and triggers action function
void Page::press()
{
    if (!isEntered())
    {
        entered = true;
        pageDisplay();
    }
    else
    {
        pagePress();
    }
}

// Moves left within the button (might add a help button within)
void Page::moveLeft()
{
    if (isEntered())
    {
        pageMoveLeft();
    }
}

// Moves right within the button (might add a help button within)
void Page::moveRight()
{
    if (isEntered())
    {
        pageMoveRight();
    }
}

// Gets the height of the button in the menu
int Page::getHeight()
{
    return PAGE_HEIGHT + MENU_SEP;
}
