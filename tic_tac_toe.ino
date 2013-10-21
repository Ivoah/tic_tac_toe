#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"

// Pins for the TFT
#define _sclk 13
#define _miso 12
#define _mosi 11
#define _cs 10
#define _rst 9
#define _dc 8

// TFT object
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);

int board[3][3] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

int WIDTH;
int HEIGHT;

int posX;
int oposX;

int posO;
int oposO;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A3, INPUT);
  pinMode(A5, INPUT);
  tft.begin();
  tft.setRotation(map(analogRead(A3), 0, 1023, 0, 3)); // Rotate the screen depending on the value of A3
  
  WIDTH = tft.width();
  HEIGHT = tft.height();
  
  posX = analogRead(A0);
  oposX = !posX;
  
  posO = analogRead(A5);
  oposO = !posO;
  
  tft.fillScreen(ILI9340_BLACK);
}

void loop() {
  
  posX = map(analogRead(A0), 0, 1023, 0, 9);
  if (posX != oposX) { board[oposX / 3][oposX % 3] = 0; oposX = posX; }
  board[posX / 3][posX % 3] = 1;
  
  posO = map(analogRead(A5), 0, 1023, 0, 9);
  if (posO != oposO) { board[oposO / 3][oposO % 3] = 0; oposO = posO; }
  board[posO / 3][posO % 3] = 2;
  
  drawBoard();
  
}

void drawBoard() {
  
  tft.drawFastVLine(WIDTH/2 - 25, HEIGHT/2 - 75, 150, ILI9340_GREEN);
  tft.drawFastVLine(WIDTH/2 + 25, HEIGHT/2 - 75, 150, ILI9340_GREEN);
  
  tft.drawFastHLine(WIDTH/2 - 75, HEIGHT/2 - 25, 150, ILI9340_GREEN);
  tft.drawFastHLine(WIDTH/2 - 75, HEIGHT/2 + 25, 150, ILI9340_GREEN);
  
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      if (board[y][x] == 1) {
        drawX(WIDTH/2 - 50 + x*50, HEIGHT/2 - 50 + y*50, 25, 25, ILI9340_GREEN);
      } else if (board[y][x] == 2) {
        tft.drawCircle(WIDTH/2 - 50 + x*50, HEIGHT/2 - 50 + y*50, 25/2, ILI9340_GREEN);
      } else {
        tft.fillRect(WIDTH/2 - 50 - 25/2 + x*50, HEIGHT/2 - 50 - 25/2 + y*50, 25, 25, ILI9340_BLACK);
      }
    }
  }
  
}

void drawX(int x, int y, int w, int h, int color) {
  tft.drawLine(x - w/2, y - h/2, x + w/2, y + h/2, color);
  tft.drawLine(x + w/2, y - h/2, x - w/2, y + h/2, color);
}
