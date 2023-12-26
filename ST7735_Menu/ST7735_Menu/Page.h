#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "Colours.h"
#include "Element.h"
#include "Constants.h"

#define PAGE_HEIGHT 14
#define TRIANGLE_HEIGHT 6
#define TRIANGLE_WIDTH 5
#define TRIANGLE_X_OFFSET 5
#define TRIANGLE_Y_OFFSET 4
#define LABEL_X_OFFSET 16

#ifndef Page_h
#define Page_h

class Page : public Element
{
public:
    Page(const char *label);
    Page();

    void display() override;
    void displaySelected() override;
    void press() override;
    void moveLeft() override;
    void moveRight() override;
    int getHeight() override;
    bool serialize(byte *buffer, int *index) override;
    bool deserialize(byte *buffer, int *index) override;
    void toDefault() override;

    virtual void pageMoveUp() = 0;
    virtual void pageMoveDown() = 0;
    virtual void pageMoveLeft() = 0;
    virtual void pageMoveRight() = 0;
    virtual void pagePress() = 0;
    virtual void pageBack() = 0;
    virtual void pageDisplay() = 0;
    virtual bool pageSerialize(byte *buffer, int *index) = 0;
    virtual bool pageDeserialize(byte *buffer, int *index) = 0;
    virtual void pageDefault() = 0;

    bool isEntered() const { return entered; }
    void setEntered(boolean new_entered) { entered = new_entered; }
    void setLabel(const char *new_label) { label = new_label; }

private:
    const char *label;
    bool entered = false;
};

#endif