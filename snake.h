//
// Shake.h
// 
// A really bad implementation of snake!
// Do not ever use this as an example of best practice <3
//
// Inspired by the work of Luke Garrigan
// https://dev.to/lukegarrigan/how-to-code-snake-1jeb
//

#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "vec2.h"

#define GRID_WIDTH 32
#define GRID_HEIGHT 16

// if we cant find the screen, define the screen size ourselfs
#ifndef SSD1306_H
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64
#endif

// input
#define INPUT_LEFT 0
#define INPUT_DOWN 1
#define INPUT_UP 6
#define INPUT_RIGHT 7


// --- Food --- //

class Food
{
public:
  Food() {
    Spawn();
  }

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
  Snake() {
    Spawn();
  }

  // the body of the snake
  std::vector<Vec2> body;

  // the direction the snake will go in
  // 0 = left, 1 = down, 2 = up, 3 = right (like DDR!)
  int dir = 3;

  // spawn the snake
  void Spawn();

  // detect if the snake has collided with food
  void InteractWithFood(Food& food);

  // move the snake
  void Move();

  // draw the snake
  void Draw(Adafruit_SSD1306& display);
};

#endif // SNAKE_H