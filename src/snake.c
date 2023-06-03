#include "snake.h"
#include "defs.h"

struct SDL_Rect get_snake_head(void)
{
  SDL_Rect rect = {GAP, GAP, SNAKE_SIZE, SNAKE_SIZE};

  return rect;
}

struct SDL_Rect get_snake_tail(uint32_t x, uint32_t y)
{
  SDL_Rect rect = {x, y, SNAKE_SIZE, SNAKE_SIZE};

  return rect;
}

uint32_t get_snake_length(SDL_Rect *snake)
{
  uint32_t length = sizeof(&snake) / sizeof(snake[0]);
  return length;
}