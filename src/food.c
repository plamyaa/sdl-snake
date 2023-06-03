#include "food.h"


SDL_Rect get_food(void)
{
  int num1, num2;
   
  srand(time(NULL));
   
  num1 = rand() % WINDOW_WIDTH;
  num2 = rand() % WINDOW_WIDTH;
  int rest1 = num1 % BLOCK;
  int rest2 = num2 % BLOCK;

  SDL_Rect rect = {num1 - rest1 + GAP, num2 - rest2 + GAP, SNAKE_SIZE, SNAKE_SIZE};

  return rect;
}