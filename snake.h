//
// Shake.h
// 
// A really bad implementation of snake!
// Do not ever use this as an example of best practice <3
//
// Initially inspired by the work of Luke Garrigan, but most of this is my own work
// https://dev.to/lukegarrigan/how-to-code-snake-1jeb
//

#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TM1638plus.h>

#include "vec2.h"

#define GRID_WIDTH 32
#define GRID_HEIGHT 16

// if we cant find the screen, define the screen size ourselfs
#ifndef SSD1306_H
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64
#endif

// pre-calculate the grid cell pixel width/height
#define CELL_XSIZE SCREEN_WIDTH / GRID_WIDTH
#define CELL_YSIZE SCREEN_HEIGHT / GRID_HEIGHT

// Input (like DDR!)
#define INPUT_LEFT 0
#define INPUT_DOWN 1
#define INPUT_UP 6
#define INPUT_RIGHT 7


// --- Food --- //

class Food
{
public:
  Food();
  ~Food() {}

  // the position of the food
  Vec2 pos;

  // spawn the food in a location
  void Spawn();

  // main draw call for the food
  void Draw(Adafruit_SSD1306& display);
};


// --- Snake --- //

class Snake
{
public:
  Snake();
  ~Snake() {}

  // the body of the snake
  std::vector<Vec2> body;

  // the direction the snake will go in
  int dir = INPUT_LEFT;

  // returns a pointer to the head of the snake
  Vec2& Head();

  // spawn the snake
  void Spawn();

  // detect if the snake has collided with food
  void DetectFood(Food& food, int& score);

  // detect if the snake collides with itself. If it does, end the game
  bool DetectSelf();

  // move the snake
  void Move();

  // draw the snake
  void Draw(Adafruit_SSD1306& display);
};

#endif // SNAKE_H