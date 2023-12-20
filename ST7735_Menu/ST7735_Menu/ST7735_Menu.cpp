/*
  ESPIR_Menu.h - Menu for ST7735
  Copyright (c) 2021 Luke Mills.  All right reserved.
*/

#include "ST7735_Menu.h"

int map(int value, int low_val, int high_val, int low_map_val, int high_map_val)
{
	// Ensure that the value is within the specified range
	value = std::max(low_val, std::min(high_val, value));

	// Map the value from the input range to the output range
	int mapped_value = static_cast<int>(low_map_val + static_cast<double>(value - low_val) / (high_val - low_val) * (high_map_val - low_map_val));

	return mapped_value;
}

int strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		++str1;
		++str2;
	}

	return (*str1 - *str2);
}

Menu::Menu(Adafruit_ST7735 *screen) : selectedElementIndex(0), entered(false), screen(screen)
{
}

// Adds an element to the menu
void Menu::addElement(Element *element)
{
	elements.push_back(element);
	element->setScreen(screen);
	element->setTop(getMenuHeight());
	setMenuHeight(getMenuHeight() + element->getHeight());

	// If total menu height overflows screen, make scrollable
	if (getMenuHeight() > SCREEN_HEIGHT)
	{
		setScrollable(true);
	}
}

// displays all elements in the menu
void Menu::display()
{
	if (getScrollable())
	{
		for (int i = 0; i < elements.size(); i++)
		{
			elements[i]->setWidth(SCREEN_WIDTH - SCROLLBAR_WIDTH - SCROLLBAR_PADDING);
		}
	}

	screen->fillScreen(BACKGROUND_COLOUR);
	int current_top = getBaseDisplayHeight();
	int current_bottom = current_top;

	for (int i = 0; i < elements.size(); i++)
	{
		// Check the full element isn't below current view window
		if (elements[i]->getTop() < getBaseDisplayHeight())
		{
			continue;
		}

		// Check the element isn't above the view window
		if ((elements[i]->getTop() + elements[i]->getHeight()) > getBaseDisplayHeight() + SCREEN_HEIGHT)
		{
			continue;
		}

		// if selected, display as selected
		if (i == selectedElementIndex)
		{
			elements[i]->displaySelected();
		}
		else
		{
			elements[i]->display();
		}

		// Adjust current bottom/top based on element height
		current_bottom += elements[i]->getHeight();
		current_top += elements[i]->getHeight();
		setEndDisplayHeight(current_bottom);
	}

	// If menu is scrollable, display the scrollbar
	if (getScrollable())
	{
		drawScrollbar(getBaseDisplayHeight(), getEndDisplayHeight());
	}
}

// Draws the scrollbar based on the amount of the menu being displayed
void Menu::drawScrollbar(int top, int bottom)
{
	// draw the background
	screen->fillRoundRect(SCREEN_WIDTH - SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, SCREEN_HEIGHT, 2, NOT_SELECTED_COLOUR);

	// calculate bar position and height
	int top_y = map(top, 0, getMenuHeight(), 0, SCREEN_HEIGHT);
	int bar_height = map(bottom, 0, getMenuHeight(), 0, SCREEN_HEIGHT) - top_y;
	
	// draw the bar
	screen->fillRoundRect(SCREEN_WIDTH - SCROLLBAR_WIDTH, top_y, SCROLLBAR_WIDTH, bar_height, 2, SELECTED_COLOUR);
}

// gets the selected value from the selector with the target id, if submenu, recursively iterate through them
bool Menu::getSelectorValue(const char *target_id, int *destination)
{
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i]->getType() == SUBMENU)
		{
			// recursively search the submenu
			Submenu *submenu = static_cast<Submenu *>(elements[i]);
			if (submenu->getSelectorValue(target_id, destination))
			{
				return true;
			}
		}
		else if (elements[i]->getType() == SELECTOR)
		{
			Selector *selector = static_cast<Selector *>(elements[i]);
			// check if ID matches
			if (strcmp(selector->getId(), target_id) == 0)
			{
				*destination = selector->getValue();
				return true;
			}
		}
	}
	return false; // not found matching ID
}

// gets the selected value from the checkox with the target id, if submenu, recursively iterate through them
bool Menu::getCheckboxValue(const char *target_id, bool *destination)
{
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i]->getType() == SUBMENU)
		{
			// recursively search the submenu
			Submenu *submenu = static_cast<Submenu *>(elements[i]);
			if (submenu->getCheckboxValue(target_id, destination))
			{
				return true;
			}
		}
		else if (elements[i]->getType() == CHECKBOX)
		{
			Checkbox *checkbox = static_cast<Checkbox *>(elements[i]);
			// check if ID matches
			if (strcmp(checkbox->getId(), target_id) == 0)
			{
				*destination = checkbox->getValue();
				return true;
			}
		}
	}
	return false; // not found matching ID
}

// gets the selected value from the slider with the target id, if submenu, recursively iterate through them
bool Menu::getSliderValue(const char *target_id, int *destination)
{
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i]->getType() == SUBMENU)
		{
			// recursively search the submenu
			Submenu *submenu = static_cast<Submenu *>(elements[i]);
			if (submenu->getSliderValue(target_id, destination))
			{
				return true;
			}
		}
		else if (elements[i]->getType() == SLIDER)
		{
			Slider *slider = static_cast<Slider *>(elements[i]);
			// check if ID matches
			if (strcmp(slider->getId(), target_id) == 0)
			{
				*destination = slider->getValue();
				return true;
			}
		}
	}
	return false; // not found matching ID
}

// Indicates that user has pressed OK on menu and wants to press element that is currently selected
void Menu::press()
{
	if (elements[selectedElementIndex]->getType() == SUBMENU)
	{
		// If we go into a submenu, display the submenu instead of this menu
		entered = true;
		elements[selectedElementIndex]->press();
	}
	else if (elements[selectedElementIndex]->getType() == PAGE)
	{
		// If we are in a page, display the page instead of this menu
		entered = true;
		elements[selectedElementIndex]->press();
	}
	else
	{
		// otherwise pass the press to the sub element
		elements[selectedElementIndex]->press();
	}
}

// Indicates the user wants to go back
void Menu::back()
{
	if (entered && elements[selectedElementIndex]->getType() == SUBMENU)
	{
		// If in a submenu, either make the submenu go back, or exit the submenu
		Submenu *submenu = static_cast<Submenu *>(elements[selectedElementIndex]);
		if (submenu->isInSubmenu())
		{
			submenu->back();
		}
		else
		{
			// also set drawn to false for submenu
			submenu->setDrawn(false);
			entered = false;
			display();
		}
	}
	else if (entered && elements[selectedElementIndex]->getType() == PAGE)
	{
		// If we are in a page, pass to page, and if the page has exited, draw menu
		Page *page = static_cast<Page *>(elements[selectedElementIndex]);
		page->pageBack();
		if (!page->isEntered())
		{
			// also set drawn to false for submenu
			entered = false;
			display();
		}
	}
}

// Indicates the user wants to move to the element above (or wrap to the element below)
void Menu::moveUp()
{	
	if (entered && elements[selectedElementIndex]->getType() == SUBMENU)
	{
		// If in a submenu, navigate this instead of base
		Submenu *submenu = static_cast<Submenu *>(elements[selectedElementIndex]);
		submenu->moveUp();
	}
	else if (entered && elements[selectedElementIndex]->getType() == PAGE)
	{
		// If in a page, navigate this instead of base
		Page *page = static_cast<Page *>(elements[selectedElementIndex]);
		page->pageMoveUp();
	}
	else
	{
		// Stop displaying current element as selected
		elements[selectedElementIndex]->display();
		// Adjust the current selected index
		if (elements.size() > 0)
		{
			if (selectedElementIndex == 0)
			{
				selectedElementIndex = elements.size() - 1; // Wrap around to the bottom

				if (getScrollable())
				{
					// Basically need to simulate moving down until we reach the last page
					while (elements[selectedElementIndex]->getTop() + elements[selectedElementIndex]->getHeight() > getEndDisplayHeight())
					{
						for (int i = 0; i < elements.size(); i++)
						{
							elements[i]->setDisplayOffset(elements[i]->getDisplayOffset() - (getEndDisplayHeight() - getBaseDisplayHeight()));
						}
						setBaseDisplayHeight(getBaseDisplayHeight() + (getEndDisplayHeight() - getBaseDisplayHeight()));
						int current_bottom = getBaseDisplayHeight();
						for (int i = 0; i < elements.size(); i++)
						{
							// Check the full element isn't below current view window
							if (elements[i]->getTop() < getBaseDisplayHeight())
							{
								continue;
							}

							// Check the element isn't above the view window
							if ((elements[i]->getTop() + elements[i]->getHeight()) > getBaseDisplayHeight() + SCREEN_HEIGHT)
							{
								continue;
							}

							current_bottom += elements[i]->getHeight();
							setEndDisplayHeight(current_bottom);
						}
					}
					display();
					return;
				}
			}
			else
			{
				--selectedElementIndex;

				if (elements[selectedElementIndex]->getTop() < getBaseDisplayHeight())
				{
					// Get all the elements above that fit into the screen space
					setBaseDisplayHeight(getBaseDisplayHeight() - SCREEN_HEIGHT);

					// Get the highest point of all the elements that fit on the screen, this needs to be at '0'
					int highest_visible = INT_MAX;
					for (int i = 0; i < elements.size(); i++)
					{
						elements[i]->setDisplayOffset(elements[i]->getDisplayOffset() + SCREEN_HEIGHT);
						if (elements[i]->getTop() > getBaseDisplayHeight())
						{
							if (elements[i]->getTop() < highest_visible)
							{
								highest_visible = elements[i]->getTop();
							}
						}
					}

					// Adjust the display offsets to put the elements in the correct position
					for (int i = 0; i < elements.size(); i++)
					{
						elements[i]->setDisplayOffset(elements[i]->getDisplayOffset() - (highest_visible - getBaseDisplayHeight()));
					}
					setBaseDisplayHeight(getBaseDisplayHeight() + (highest_visible - getBaseDisplayHeight()));
					display();
					return;
				}
			}
		}
		// Show new element selected
		elements[selectedElementIndex]->displaySelected();
	}
}

// Indicates the user wants to move to the element below (or wrap around to the element at the top)
void Menu::moveDown()
{
	if (entered && elements[selectedElementIndex]->getType() == SUBMENU)
	{
		// If in a submenu, navigate this instead of base
		Submenu *submenu = static_cast<Submenu *>(elements[selectedElementIndex]);
		submenu->moveDown();
	}
	else if (entered && elements[selectedElementIndex]->getType() == PAGE)
	{
		// If in a page, navigate this instead of base
		Page *page = static_cast<Page *>(elements[selectedElementIndex]);
		page->pageMoveDown();
	}
	else
	{
		// Stop displaying current element as selected
		elements[selectedElementIndex]->display();
		// Adjust the current selected index
		if (elements.size() > 0)
		{
			if (selectedElementIndex == elements.size() - 1)
			{
				selectedElementIndex = 0; // Wrap around to the top
				if (scrollable)
				{
					setBaseDisplayHeight(0);
					for (int i = 0; i < elements.size(); i++)
					{
						elements[i]->setDisplayOffset(0);
					}
					display();
					return;
				}
			}
			else
			{
				++selectedElementIndex;
				if (elements[selectedElementIndex]->getTop() >= getEndDisplayHeight())
				{
					for (int i = 0; i < elements.size(); i++)
					{
						elements[i]->setDisplayOffset(elements[i]->getDisplayOffset() - (getEndDisplayHeight() - getBaseDisplayHeight()));
					}
					setBaseDisplayHeight(getBaseDisplayHeight() + (getEndDisplayHeight() - getBaseDisplayHeight()));
					display();
					return;
				}
			}
		}
		// Show new element selected
		elements[selectedElementIndex]->displaySelected();
	}
}

// Indicates the user wants to move left within the element
void Menu::moveLeft()
{
	// elements[selectedElementIndex]->moveLeft();
	// make sure not passing into unentered submenu
	if (entered || (elements[selectedElementIndex]->getType() != SUBMENU))
	{
		elements[selectedElementIndex]->moveLeft();
	}
}

// Indicates the user wants to move right within the element
void Menu::moveRight()
{
	// elements[selectedElementIndex]->moveRight();
	// make sure not passing into unentered submenu
	if (entered || (elements[selectedElementIndex]->getType() != SUBMENU))
	{
		elements[selectedElementIndex]->moveRight();
	}
}
