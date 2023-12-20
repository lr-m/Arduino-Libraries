#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RetroController.h>

// Controller GPIO pins
#define LATCH 17
#define PULSE 16
#define RESPONSE 18 

// Init controller
Controller controller(LATCH, PULSE, RESPONSE);

// Display properties
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// Init display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char* pressed;

void setup() {
  Serial.begin(115200);

  // Check display begin worked
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("Display init failed");
    for(;;);
  }

  display.clearDisplay();
}

void loop() {
  pressed = controller.poll(); // Poll controller for current presses

  printPressed();
}

// Displays the buttons pressed on the screen
void printPressed(){
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.cp437(true);
 
  if (pressed[B])
    display.println("B");
  
  if (pressed[Y])
    display.println("Y");
  
  if (pressed[SELECT])
    display.println("SELECT");
  
  if (pressed[START])
    display.println("START");
  
  if (pressed[UP])
    display.println("UP");
  
  if (pressed[DOWN])
    display.println("DOWN");
  
  if (pressed[LEFT])
    display.println("LEFT");
  
  if (pressed[RIGHT])
    display.println("RIGHT");

  display.display();
}
