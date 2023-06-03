#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdlib.h> 

#ifndef FIELD
#define FIELD

struct Field
{
  int32_t up;
  int32_t down;
  int32_t left;
  int32_t right;
};

struct SDL_Rect get_field(void);

#endif