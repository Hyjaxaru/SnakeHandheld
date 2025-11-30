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

Food::Food()
{
  Spawn();
}

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

Snake::Snake()
{
  Spawn();
}

Vec2& Snake::Head()
{
  return body[0];
}

void Snake::Spawn()
{
  body.push_back({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
}

void Snake::DetectFood(Food &food, int& score)
{
  // decide if the snake has touched a food
  if (Head() == food.pos)
  {
    // make snake bigger
    body.push_back(body.back());
    food.Spawn();

    score++;
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
  Vec2& head = Head();
  if (dir == INPUT_LEFT)
    head.x -= CELL_XSIZE;
  else if (dir == INPUT_DOWN)
    head.y += CELL_YSIZE;
  else if (dir == INPUT_UP)
    head.y -= CELL_YSIZE;
  else if (dir == INPUT_RIGHT)
    head.x += CELL_XSIZE;

  // wrap movement around the screen
  if (head.x < 0)
    head.x = SCREEN_WIDTH;
  else if (head.x > SCREEN_WIDTH)
    head.x = 0;
  else if (head.y < 0)
    head.y = SCREEN_HEIGHT;
  else if (head.y > SCREEN_HEIGHT)
    head.y = 0;

}

bool Snake::DetectSelf()
{
  Vec2 head = Head();

  // loop for every body part
  int size = body.size();
  for (int i = 1; i < size; i++)
  {
    // if the head is inside the body, then we die!
    if (body[i] == head)
      return true;
  }

  // the snake is not inside itself
  return false;
}

void Snake::Draw(Adafruit_SSD1306& display)
{
  for (int i = 0; i < body.size(); i++)
  {
    display.drawRect(body[i].x, body[i].y, SCREEN_WIDTH / GRID_WIDTH, SCREEN_HEIGHT / GRID_HEIGHT, WHITE);
  }
}
