#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include <stdbool.h>

#include "defs.h"
#include "field.h"
#include "snake.h"
#include "food.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_TimerID *timerID = NULL;
SDL_Rect *snake = NULL;
SDL_Rect food;

uint8_t direction = NULL;
uint16_t score = NULL;
bool quit = false;

bool is_bound(void);
bool is_food_eaten();
Uint32 move_snake_callback(Uint32 interval, void *param);
void move_snake();

void init(void)
{
  score = 1;
  direction = 2;

  window = SDL_CreateWindow("Snake", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  timerID = SDL_AddTimer(TIMER_INTERVAL, move_snake_callback, NULL);

  snake = (SDL_Rect*)malloc(score * sizeof(SDL_Rect));

  snake[0] = get_snake_head();
  food = get_food();
}

int main(int argc, char *argv[])
{
  init();
  SDL_Event event;
  
  SDL_Rect field = get_field();
  SDL_Color color = {0, 0, 0, 255};

  while (!quit)
  {
    SDL_RenderClear(renderer);
    while( SDL_PollEvent(&event) != 0 )
    {
      if (event.type == SDL_KEYDOWN) 
      {
        switch (event.key.keysym.sym)
        {
          case SDLK_UP:
            direction = 1;
            break;
          case SDLK_RIGHT:
            direction = 2;
            break;
          case SDLK_DOWN:
            direction = 3;
            break;
          case SDLK_LEFT:
            direction = 4;
            break;
          case SDLK_q:
            quit = true;
            break;
        }
      }

      if (event.type == SDL_QUIT ) // unless player manually quits
        quit = true;
    }
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
    //  Field 
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &field);
    // Food 
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &food);    
    // Snake
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // uint32_t snake_length = get_snake_length(snake) + 1;
    for (uint8_t i = 0; i < score; i++)
    {
      SDL_RenderFillRect(renderer, &snake[i]);    
    }

    SDL_RenderPresent(renderer);
  }
  printf("\n Score: %d", score);
  free(snake);
  SDL_RemoveTimer(timerID);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

Uint32 move_snake_callback(Uint32 interval, void* param) {
  bool is_eaten = is_food_eaten();
  move_snake();
  if (is_eaten)
  {
    snake[score - 1] = get_snake_tail(food.x, food.y);
    food = get_food();
  }

  for (uint8_t i = score - 1; i > 0; i--)
  {
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
      quit = true;
  }

  for (uint8_t i = score - 1; i > 0; i--)
  {
    snake[i] = (struct SDL_Rect){snake[i - 1].x, snake[i - 1].y, SNAKE_SIZE, SNAKE_SIZE};
  }
  return interval;
}

void move_snake()
{
  switch (direction)
  {
    case 1:
      snake[0].y -= BLOCK;
      if (is_bound()) 
        snake[0].y = SQUARE_EDGE - BLOCK + GAP;
      break;
    case 2:
      snake[0].x += BLOCK;
      if (is_bound()) 
        snake[0].x = GAP;
      break;
    case 3:
      snake[0].y += BLOCK;
      if (is_bound()) 
        snake[0].y = GAP;
      break;
    case 4:
      snake[0].x -= BLOCK;
      if (is_bound()) 
        snake[0].x = SQUARE_EDGE - BLOCK + GAP;
      break;
    default:
      break;
  }
}

bool is_food_eaten(void)
{
  if (food.x == snake[0].x && food.y == snake[0].y) 
  {
    score += 1;
    printf("new score: %d", score);
    snake = (SDL_Rect *)realloc(snake, score * sizeof(SDL_Rect));
    return true;
  }
  return false;
}

bool is_bound(void)
{
  int32_t left = 0;
  int32_t right = SQUARE_EDGE - GAP;
  int32_t up = 0;
  int32_t down = SQUARE_EDGE - GAP;

  if (snake[0].x < left)
    return true;
  if (snake[0].x > right)
    return true;
  if (snake[0].y < up)
    return true;
  if (snake[0].y > down)
    return true;
  return false;
}