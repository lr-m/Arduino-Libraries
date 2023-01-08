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
#define OLED_RESET      -1
#define SCREEN_ADDRESS  0x3C
#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   32

// Init display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char* pressed;

// Game properties
const int kScreenWidth = 128, kScreenHeight = 32, kGameWidth = 64, kGameHeight = 16, kMaxLength = 464, kStartLength = 16;

// For storing and comparing positions
struct Position {
  char x, y;  

  // For comparison between positions
  bool operator==(const Position& other) const {
    return x == other.x && y == other.y;
  }

  // For adding positions
  Position& operator+=(const Position& other) {
    x += other.x;
    y += other.y;
    return *this;
  }
};

// Draw a square on the board
void draw_square(Position pos, int color = WHITE) {
  display.fillRect(pos.x * 2, pos.y * 2, 2, 2, color);
}

// Check if a pixel is bad or good
bool test_position(Position pos) {
  return display.getPixel(pos.x * 2, pos.y * 2);
}

// Direction position constants
const Position kDirPos[4] = {
  {0,-1}, {1, 0}, {0, 1}, {-1, 0}
};

// Apple struct
struct Item {
  Position pos;
  
  void spawn() {
    pos.x = random(2, kGameWidth-2);
    pos.y = random(2, kGameHeight-2);
  }
  
  void render() const {
    draw_square(pos);
  }
} item;

// Player struct
struct Player {
  Player() { reset(); }
  Position pos;
  unsigned char tail[kMaxLength];
  unsigned char direction;
  int size, moved;

  // Reset the players position
  void reset() {
    pos = {kGameWidth/2,kGameHeight/2};
    direction = 1;
    size = kStartLength;
    memset(tail, 0, sizeof(tail));
    moved = 0;
  }

  // Turn towards the ceiling
  void face_up(){
    direction = 0;
  }

  // Turn to the right
  void face_right(){
    direction = 1;
  }

  // Turn to face down
  void face_down(){
    direction = 2;
  }

  // Turn to face left
  void face_left(){
    direction = 3;
  }

  // Update the players position on the board
  void update() {
    // Update snake position from back to front
    for(int i = kMaxLength - 1; i > 0; --i) {
      // Move segment to segment in front (2 bits at a time)
      tail[i] = tail[i] << 2 | ((tail[i - 1] >> 6) & 3);
    }

    // Update head (2 bits again)
    tail[0] = tail[0] << 2 | ((direction + 2) % 4);
    pos += kDirPos[direction];
    
    if (moved < size)
      moved++;
  }

  // Draw the player
  void render() const {
    draw_square(pos); // Draw new head
    
    if(moved < size)
      return;

    // Update tail position
    Position tailpos = pos;
    for(int i = 0; i < size; ++i)
      tailpos += kDirPos[(tail[(i >> 2)] >> ((i & 3) * 2)) & 3];
    
    draw_square(tailpos, BLACK); // Cover up tail
  }
} player;

// Render everything onto the screen, and display
void render() {
  player.render();
  item.render();
  display.display();
}

// Draw the intro screen
void intro() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Press START");
  display.display();
}

// Handle the controller input
void input() {
  if(controller.isPressed(UP))
    player.face_up();

  if(controller.isPressed(RIGHT))
    player.face_right();

  if(controller.isPressed(DOWN))
    player.face_down();

  if(controller.isPressed(LEFT))
    player.face_left();
}

// Flash the screen for when the game ends
void flash_screen() {
  display.invertDisplay(true);
  delay(100);
  display.invertDisplay(false);
  delay(200);
}

// Update the game
void updateGame() {
  player.update();

  // Check if player eats apple or game ends
  if(player.pos == item.pos) {
    player.size++;
    item.spawn();
  } else if(test_position(player.pos)) {
    flash_screen();
    resetGame();
  }

  // Slow game down
  delay(75);
}

// Resets the game to start
void resetGame(){
  display.clearDisplay();

  // Draw the game border
  for(char x = 0; x < kGameWidth; ++x) {
    draw_square({x, 0});
    draw_square({x, kGameHeight-1});
  }
  
  for(char y = 0; y < kGameHeight; ++y) {
    draw_square({0, y});
    draw_square({kGameWidth-1, y});
  }
  
  player.reset();
  item.spawn();
}

void setup() {
  Serial.begin(115200);

  // Check display begin worked
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("Display init failed");
    for(;;);
  }

  display.setTextColor(WHITE);

  intro();

  while(!controller.isPressed(START))
    pressed = controller.poll();

  display.clearDisplay();
  display.display();

  flash_screen();

  resetGame();
}

void loop() {
  pressed = controller.poll(); // Poll controller for current presses
  input();
  updateGame();
  render();
}
