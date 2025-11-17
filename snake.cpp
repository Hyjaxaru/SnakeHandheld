//
// Shake.cpp
//
// A really bad implementation of snake!
// Do not ever use this as an example of best practice <3
//
// Inspired by the work of Luke Garrigan
// https://dev.to/lukegarrigan/how-to-code-snake-1jeb
//

#include "snake.h"

// --- Food --- //

void Food::Spawn()
{
  int randomX = std::rand() % SCREEN_WIDTH;
  int randomY = std::rand() % SCREEN_HEIGHT;
  pos.x = randomX - randomX % (SCREEN_WIDTH / GRID_WIDTH);
  pos.y = randomY - randomY % (SCREEN_HEIGHT / GRID_HEIGHT);
}

void Food::Draw(Adafruit_SSD1306& display)
{
  display.fillRect(pos.x, pos.y, SCREEN_WIDTH / GRID_WIDTH, SCREEN_HEIGHT / GRID_HEIGHT, WHITE);
}


// --- Snake --- //

void Snake::Spawn()
{
  body.push_back({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
}

void Snake::DetectFood(Food &food)
{
  // decide if the snake has touched a food
  if (body[0] == food.pos)
  {
    // make snake bigger
    body.push_back(body.back());
    food.Spawn();
  }
}

void Snake::Move()
{
  // move the body of the snake
  int size = body.size();
  for (int i = 1; i < size; i++)
  {
    int part = size - i;
    body[part] = body[part - 1];
  }

  // move the head of the snake
  if (dir == INPUT_LEFT)
    body[0].x -= CELL_XSIZE;
  else if (dir == INPUT_DOWN)
    body[0].y += CELL_YSIZE;
  else if (dir == INPUT_UP)
    body[0].y -= CELL_YSIZE;
  else if (dir == INPUT_RIGHT)
    body[0].x += CELL_XSIZE;

  // wrap movement around the screen
  if (body[0].x < 0)
    body[0].x = SCREEN_WIDTH;

}

void Snake::Draw(Adafruit_SSD1306& display)
{
  for (int i = 0; i < body.size(); i++)
  {
    display.drawRect(body[i].x, body[i].y, SCREEN_WIDTH / GRID_WIDTH, SCREEN_HEIGHT / GRID_HEIGHT, WHITE);
  }
}
