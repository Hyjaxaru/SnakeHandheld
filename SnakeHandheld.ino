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

// Input
#define INPUT_SHOW_CONTROLLS 5
#define INPUT_RESET_GAME 4


// the game score
int score;
int scoreLastFrame;

// --- Functions --- //

// the following line is taken from this website:
// https://www.instructables.com/two-ways-to-reset-arduino-in-software/
void(* resetFunc) (void) = 0;

bool isButtonPressed(int buttonIndex)
{
	return TM1638Utility::IsButtonPressed(tm, buttonIndex);
}

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

void drawControls()
{
	// left
	Vec2 head = snake.Head();
	display.setCursor(head.x - 6, head.y - 2);
	display << INPUT_LEFT+1 << endl; // +1 because we start at 0 internally, but the markings on the board start at 1

	// right
	display.setCursor(head.x + 6, head.y - 2);
	display << INPUT_RIGHT+1 << endl;

	// up
	display.setCursor(head.x, head.y - 8);
	display << INPUT_UP+1 << endl;

	// down
	display.setCursor(head.x, head.y + 6);
	display << INPUT_DOWN+1 << endl;
}

void resetWithMessage(char* message)
{
	tm.displayText(message);
	resetFunc();
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

	// show the score on the 7seg anBuzz
	tm.displayIntNum(score, false, TMAlignTextRight);
	tm.setLEDs(score);

	display.clearDisplay();

	// draw the game on the OLED
  snake.Draw(display);
	food.Draw(display);
	
	// show controlls if button is pressed
	if (isButtonPressed(INPUT_SHOW_CONTROLLS))
		drawControls();

	display.display();

	// reset the game if the player presses restart
	if (isButtonPressed(INPUT_RESET_GAME))
		resetWithMessage("RESET");

	// play a tone to show movement
	tone(BUZZER_PIN, SFX_STEP_FREQ, SFX_STEP_DUR);

	// if the score has increased, play a tone
	if (scoreLastFrame != score)
	{
		tone(BUZZER_PIN, SFX_FOOD_FREQ, SFX_FOOD_DUR);
	}
	else
	{
		// only preform the death check if we havent just picked up food...
		if (snake.DetectSelf())
			resetWithMessage("YOU DIED");
	}
	scoreLastFrame = score;

	// delay
	delay(FRAME_DELAY);
}