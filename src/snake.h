#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdlib.h>


struct SDL_Rect get_snake_head(void);
struct SDL_Rect get_snake_tail(uint32_t x, uint32_t y);
uint32_t get_snake_length(SDL_Rect *snake);
