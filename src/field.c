#include "field.h"
#include "defs.h"

struct SDL_Rect get_field(void)
{
  struct Field field;
  
  field.up = (WINDOW_HEIGHT - SQUARE_EDGE) / 2;
  field.left = (WINDOW_WIDTH - SQUARE_EDGE) / 2;
  field.right = SQUARE_EDGE;
  field.down = SQUARE_EDGE;

  SDL_Rect rect = {field.left, field.up, field.right, field.down};

  return rect;
}