#include "Element.h"

#define BUTTON_HEIGHT 14
#define TRIANGLE_HEIGHT 6
#define TRIANGLE_WIDTH 5
#define TRIANGLE_X_OFFSET 5
#define TRIANGLE_Y_OFFSET 4
#define LABEL_X_OFFSET 16

#ifndef Button_h
#define Button_h

class Button : public Element
{
public:
    Button(const char *label, void (*onClick)());
    void display() override;
    void displaySelected() override;
    void press() override;
    void moveLeft() override{};
    void moveRight() override{};
    int getHeight() override;
    void toDefault() override{};

    bool serialize(uint8_t *buffer, int *index) override{};
    bool deserialize(uint8_t *buffer, int *index) override{};

private:
    const char *label;
    void (*onClick)();
};

#endif