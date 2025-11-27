//
// SnakeTest.ino
//
// It's the main file, we all know this
//

#include <Streaming.h>

// --- Import & Define --- //

// expansion board (tm1638)
#include "tm1638.h"
TM1638plus tm = TM1638Utility::Init();

// OLED display (ssd1306)
#include "ssd1306.h"
Adafruit_SSD1306 display = SSD1306Utility::Init();

// Buzzer
#define BUZZER_PIN D6

// snake	
#include "snake.h"
Snake snake = Snake();
Food food = Food();

// --- Globals --- //

// frame rate :)
#define FRAME_DELAY 500

// SFX length and freq
#define SFX_STEP_FREQ 1000
#define SFX_STEP_DUR 5
#define SFX_FOOD_FREQ 2000
#define SFX_FOOD_DUR 5

// the game score
int score;
int scoreLastFrame;

// --- Functions --- //

bool isButtonPressed(int buttonIndex) { return TM1638Utility::IsButtonPressed(tm, buttonIndex); }

int snakeMovementInput()
{
	if (isButtonPressed(INPUT_LEFT))
		return INPUT_LEFT;
	else if (isButtonPressed(INPUT_DOWN))
		return INPUT_DOWN;
	else if (isButtonPressed(INPUT_UP))
		return INPUT_UP;
	else if (isButtonPressed(INPUT_RIGHT))
		return INPUT_RIGHT;
	else
		return -1;
}

// --- MAIN --- //

void setup()
{
  // set up components
  TM1638Utility::Setup(tm);
  SSD1306Utility::Setup(display);

	food.Spawn();
}

void loop()
{
  // input
  int snakeInput = snakeMovementInput();
	if (snakeInput != -1)
			snake.dir = snakeInput;

	// move the snake
  snake.Move();
  snake.DetectFood(food, score);

	// show the score on the 7seg
	tm.displayIntNum(score, false, TMAlignTextRight);
	tm.setLEDs(score);

	// draw the game on the OLED
	display.clearDisplay();
  snake.Draw(display);
	food.Draw(display);
	display.display();

	// play a tone to show movement
	tone(BUZZER_PIN, SFX_STEP_FREQ, SFX_STEP_DUR);

	// if the score has increased, play a tone
	if (scoreLastFrame != score)
	{
		tone(BUZZER_PIN, SFX_FOOD_FREQ, SFX_FOOD_DUR);
	}
	scoreLastFrame = score;

	// delay
	delay(FRAME_DELAY);
}