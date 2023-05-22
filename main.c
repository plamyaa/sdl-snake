#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "defs.h"
// #include "init.h"

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Renderer *renderer;

// struct Field field;
// field = {
//   (WIDTH - SQUARE_EDGE) / 2 + 2,
//   (HEIGHT - SQUARE_EDGE) / 2 + 2,
//   SQUARE_EDGE + SNAKE - 7,
//   SQUARE_EDGE - 7};
// printf("%d", field.first_x);

bool is_bound(int32_t x, int32_t y);
// void move_snake(SDL_rect *snake, char[] direction);

int main(int argc, char *argv[])
{
  SDL_Window *window = SDL_CreateWindow("Snake", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
  SDL_Event event;
  bool quit = false;

  SDL_Rect rect = {(WIDTH - SQUARE_EDGE) / 2, (HEIGHT - SQUARE_EDGE) / 2, SQUARE_EDGE, SQUARE_EDGE};
  SDL_Color color = {0, 0, 0, 255};

  int32_t snake_x = (WIDTH - SQUARE_EDGE) / 2 + 2;
  int32_t snake_y = (HEIGHT - SQUARE_EDGE) / 2 + 2;
  SDL_Rect snake = {snake_x, snake_y, SNAKE, SNAKE};

  while (!quit)
  {
    SDL_RenderClear(renderer);
    while( SDL_PollEvent(&event) != 0 )
    {
      if (event.type == SDL_KEYDOWN) 
      {
        switch (event.key.keysym.sym)
        {
          case SDLK_RIGHT:
            snake_x += SNAKE;
            if (is_bound(snake_x, snake_y)) {
              snake_x = (WIDTH - SQUARE_EDGE) / 2 + 2;
              snake = (struct SDL_Rect){snake_x, snake_y, SNAKE, SNAKE};
              break;
            }
            is_bound(snake_x, snake_y);
            snake = (struct SDL_Rect){snake_x, snake_y, SNAKE, SNAKE};
            break;
          case SDLK_LEFT:
            snake_x -= SNAKE;
            if (is_bound(snake_x, snake_y)) {
              snake_x = SQUARE_EDGE + SNAKE - 7;
              snake = (struct SDL_Rect){snake_x, snake_y, SNAKE, SNAKE};
              break;
            }
            snake = (struct SDL_Rect){snake_x, snake_y, SNAKE, SNAKE};
            break;
          case SDLK_UP:
            snake_y -= SNAKE;
            if (is_bound(snake_x, snake_y)) {
              snake_y = SQUARE_EDGE - SNAKE + 9;
              snake = (struct SDL_Rect){snake_x, snake_y, SNAKE, SNAKE};
              break;
            }
            snake = (struct SDL_Rect){snake_x, snake_y, SNAKE, SNAKE};
            break;
          case SDLK_DOWN:
            snake_y += SNAKE;
            if (is_bound(snake_x, snake_y)) {
              snake_y = (HEIGHT - SQUARE_EDGE) / 2 + 2;
              snake = (struct SDL_Rect){snake_x, snake_y, SNAKE, SNAKE};
              break;
            }
            snake = (struct SDL_Rect){snake_x, snake_y, SNAKE, SNAKE};
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
    SDL_RenderDrawRect(renderer, &rect);
    // Snake
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &snake);    

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool is_bound(int32_t x, int32_t y)
{
  int32_t left_x = (WIDTH - SQUARE_EDGE) / 2 + 2;
  int32_t right_x = SQUARE_EDGE + SNAKE - 7;
  int32_t up_y = (HEIGHT - SQUARE_EDGE) / 2 + 2;
  int32_t down_y = SQUARE_EDGE - 7;

  if (x < left_x)
    return true;
  if (x > right_x)
    return true;
  if (y < up_y)
    return true;
  if (y > down_y)
    return true;
  return false;
}

// void move_snake(SDL_Rect *snake, char[] direction)
// {
//   switch (direction)
//   {
//     case "right":
//       &snake_x += SNAKE;
//       if (is_bound(snake_x, snake_y)) {
//         snake_x = (WIDTH - SQUARE_EDGE) / 2 + 2;
//         snake = (struct SDL_Rect){snake_x, snake_y, SNAKE, SNAKE};
//         break;
//       }
//       is_bound(snake_x, snake_y);
//       snake = (struct SDL_Rect){snake_x, snake_y, SNAKE, SNAKE};
//       break;
//   }
// }