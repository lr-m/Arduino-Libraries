#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Colours.h>
#include <IR_Codes.h>
#include <IRremote.h>
#include <ST7735_Menu.h>

// Define PIN config
#define TFT_SCL   D1
#define TFT_SDA   D2
#define TFT_RES   D3
#define RECV_PIN  D4
#define TFT_DC    D5
#define TFT_CS    D6

// For ST7735-based displays, we will use this call
Adafruit_ST7735 tft =
    Adafruit_ST7735(TFT_CS, TFT_DC, TFT_SDA, TFT_SCL, TFT_RES);

// IR remote
IRrecv irrecv(RECV_PIN);
decode_results results;

// Instantiate menu
Menu* menu;

const char* selector_test_labels[] = {"Option 1", "Option 2", "Option 3", "Option 4", "Option 5"};
int selector_test_options[] = {0, 1, 2, 3, 4};

Button *test_button_1, *test_button_2, *test_button_3, *test_button_4, *mix_button;
Selector *test_selector_1, *test_selector_2, *test_selector_3, *test_selector_4, *mix_selector;
Slider *test_slider_1, *test_slider_2, *test_slider_3, *test_slider_4, *mix_slider;
Checkbox *test_checkbox_1, *test_checkbox_2, *test_checkbox_3, *test_checkbox_4, *mix_checkbox;
Submenu *button_submenu, *selector_submenu, *slider_submenu, *checkbox_submenu, *mix_submenu;

// Custom page example
class TestPage : public Page
{
  public:
    TestPage(const char* label);
    void pageMoveUp() override;
    void pageMoveDown() override;
    void pageMoveLeft() override;
    void pageMoveRight() override;
    void pagePress() override;
    void pageBack() override;
    void pageDisplay() override;
};

TestPage::TestPage(const char* label) {setLabel(label);}

void TestPage::pageMoveUp(){
  getScreen()->fillRect(0, 0, SCREEN_WIDTH, 20, RED);
  getScreen()->setCursor(0,0);
  getScreen()->setTextColor(BLACK);
  getScreen()->print("Up arrow pressed!");
}

void TestPage::pageMoveDown(){
  getScreen()->fillRect(0, 0, SCREEN_WIDTH, 20, RED);
  getScreen()->setCursor(0,0);
  getScreen()->setTextColor(BLACK);
  getScreen()->print("Down arrow pressed!");
}

void TestPage::pageMoveLeft(){
  getScreen()->fillRect(0, 0, SCREEN_WIDTH, 30, RED);
  getScreen()->setCursor(0,0);
  getScreen()->setTextColor(BLACK);
  getScreen()->print("Left arrow pressed!");
}

void TestPage::pageMoveRight(){
  getScreen()->fillRect(0, 0, SCREEN_WIDTH, 30, RED);
  getScreen()->setCursor(0,0);
  getScreen()->setTextColor(BLACK);
  getScreen()->print("Right arrow pressed!");
}

void TestPage::pagePress(){
  getScreen()->fillRect(0, 0, SCREEN_WIDTH, 30, RED);
  getScreen()->setCursor(0,0);
  getScreen()->setTextColor(BLACK);
  getScreen()->println("OK pressed!");
}

void TestPage::pageBack(){
  getScreen()->fillRect(0, 0, SCREEN_WIDTH, 30, RED);
  getScreen()->setCursor(0,0);
  getScreen()->setTextColor(BLACK);
  getScreen()->print("Hashtag (back) pressed!");
  delay(500);
  setEntered(false);
}

void TestPage::pageDisplay(){
  getScreen()->fillScreen(RED);
  getScreen()->setCursor(0,0);
  getScreen()->setTextColor(BLACK);
  getScreen()->println("Welcome to the demo test page!");

  getScreen()->println("\nSelector Values:");
  int selector_value = 0;
  menu->getSelectorValue("test_selector_1", &selector_value);
  getScreen()->print(selector_value);
  getScreen()->print(' ');
  menu->getSelectorValue("test_selector_2", &selector_value);
  getScreen()->print(selector_value);
  getScreen()->print(' ');
  menu->getSelectorValue("test_selector_3", &selector_value);
  getScreen()->print(selector_value);
  getScreen()->print(' ');
  menu->getSelectorValue("test_selector_4", &selector_value);
  getScreen()->println(selector_value);

  getScreen()->println("\nSlider values:");
  int slider_value = 0;
  menu->getSliderValue("test_slider_1", &slider_value);
  getScreen()->print(slider_value);
  getScreen()->print(' ');
  menu->getSliderValue("test_slider_2", &slider_value);
  getScreen()->print(slider_value);
  getScreen()->print(' ');
  menu->getSliderValue("test_slider_3", &slider_value);
  getScreen()->print(slider_value);
  getScreen()->print(' ');
  menu->getSliderValue("test_slider_4", &slider_value);
  getScreen()->println(slider_value);

  getScreen()->println("\nCheckbox values:");
  bool checkbox_value = false;
  menu->getCheckboxValue("test_checkbox_1", &checkbox_value);
  getScreen()->print(checkbox_value);
  getScreen()->print(' ');
  menu->getCheckboxValue("test_checkbox_2", &checkbox_value);
  getScreen()->print(checkbox_value);
  getScreen()->print(' ');
  menu->getCheckboxValue("test_checkbox_3", &checkbox_value);
  getScreen()->print(checkbox_value);
  getScreen()->print(' ');
  menu->getCheckboxValue("test_checkbox_4", &checkbox_value);
  getScreen()->println(checkbox_value);

  getScreen()->println("\nMixed values:");
  menu->getCheckboxValue("mix_checkbox", &checkbox_value);
  getScreen()->print(checkbox_value);
  getScreen()->print(' ');
  menu->getSliderValue("mix_slider", &slider_value);
  getScreen()->print(slider_value);
  getScreen()->print(' ');
  menu->getSelectorValue("mix_selector", &selector_value);
  getScreen()->println(selector_value);
}

TestPage* test_page;

void init_menu(){
  // init menu
  menu = new Menu(&tft);

  // init submenus
  button_submenu = new Submenu("Button Test", &tft);
  selector_submenu = new Submenu("Selector Test", &tft);
  slider_submenu = new Submenu("Slider Test", &tft);
  checkbox_submenu = new Submenu("Checkbox Test", &tft);
  mix_submenu = new Submenu("Mix Test", &tft);

  // init button test submenu
  test_button_1 = new Button("Test button 1", test);
  test_button_2 = new Button("Test button 2", test);
  test_button_3 = new Button("Test button 3", test);
  test_button_4 = new Button("Test button 4", test);
  button_submenu->addElement(test_button_1);
  button_submenu->addElement(test_button_2);
  button_submenu->addElement(test_button_3);
  button_submenu->addElement(test_button_4);

  // init selector test submenu
  test_selector_1 = new Selector("Test selector 1", selector_test_labels, selector_test_options, 5, "test_selector_1");
  test_selector_2 = new Selector("Test selector 2", selector_test_labels, selector_test_options, 5, "test_selector_2");
  test_selector_3 = new Selector("Test selector 3", selector_test_labels, selector_test_options, 5, "test_selector_3");
  test_selector_4 = new Selector("Test selector 4", selector_test_labels, selector_test_options, 5, "test_selector_4");
  selector_submenu->addElement(test_selector_1);
  selector_submenu->addElement(test_selector_2);
  selector_submenu->addElement(test_selector_3);
  selector_submenu->addElement(test_selector_4);

  // init slider test submenu
  test_slider_1 = new Slider("Test Slider 1", 0, 100, 1, 0, "test_slider_1");
  test_slider_2 = new Slider("Test Slider 2", 0, 100, 5, 33, "test_slider_2");
  test_slider_3 = new Slider("Test Slider 3", 0, 100, 10, 66, "test_slider_3");
  test_slider_4 = new Slider("Test Slider 4", 0, 100, 20, 100, "test_slider_4");
  slider_submenu->addElement(test_slider_1);
  slider_submenu->addElement(test_slider_2);
  slider_submenu->addElement(test_slider_3);
  slider_submenu->addElement(test_slider_4);

  // init checkbox test_submenu
  test_checkbox_1 = new Checkbox("Test Checkbox 1", "test_checkbox_1");
  test_checkbox_2 = new Checkbox("Test Checkbox 2", "test_checkbox_2");
  test_checkbox_3 = new Checkbox("Test Checkbox 3", "test_checkbox_3");
  test_checkbox_4 = new Checkbox("Test Checkbox 4", "test_checkbox_4");
  checkbox_submenu->addElement(test_checkbox_1);
  checkbox_submenu->addElement(test_checkbox_2);
  checkbox_submenu->addElement(test_checkbox_3);
  checkbox_submenu->addElement(test_checkbox_4);

  mix_button = new Button("Mix Button", test);
  mix_selector = new Selector("Mix Selector", selector_test_labels, selector_test_options, 5, "mix_selector");
  mix_slider = new Slider("Mix Slider", 0, 100, 20, 100, "mix_slider");
  mix_checkbox = new Checkbox("Mix Checkbox", "mix_checkbox");
  mix_submenu->addElement(mix_button);
  mix_submenu->addElement(mix_selector);
  mix_submenu->addElement(mix_slider);
  mix_submenu->addElement(mix_checkbox);

  test_page = new TestPage("Test Page");
  menu->addElement(test_page);
  menu->addElement(button_submenu);
  menu->addElement(selector_submenu);
  menu->addElement(slider_submenu);
  menu->addElement(checkbox_submenu);
  menu->addElement(mix_submenu);
}


void setup(void) { 
  Serial.begin(115200);

  irrecv.enableIRIn(); // Enable IR reciever

  tft.initR(INITR_BLACKTAB); // Init ST7735S chip
  tft.setRotation(1);

  tft.fillScreen(BLACK);

  init_menu();

  menu->display();
}

void test(){
  Serial.println("button pressed");
}

int hello = 0;
int hello2 = 0;
int hello3 = 0;

void loop() {
    // IR receive loop
      if (irrecv.decode()) {
          if (irrecv.decodedIRData.decodedRawData == IR_UP){
            menu->moveUp();
          }

          if (irrecv.decodedIRData.decodedRawData == IR_DOWN){
            menu->moveDown();
          }

          if (irrecv.decodedIRData.decodedRawData == IR_LEFT){
            menu->moveLeft();
          }

          if (irrecv.decodedIRData.decodedRawData == IR_RIGHT){
            menu->moveRight();
          }

          if (irrecv.decodedIRData.decodedRawData == IR_OK){
            menu->press();
          }

          if (irrecv.decodedIRData.decodedRawData == IR_HASHTAG){
            menu->back();
          }
          
          irrecv.resume();
    }
}
