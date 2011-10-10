#include <SDL/SDL.h>

#include <ui.h>
#include <canvas.h>

SDL_Surface* g_ui;

void initui(void) {
  g_ui = SDL_SetVideoMode(XRES, YRES, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
  if (!g_ui) {
    perror(SDL_GetError());
  }
}

void initui(void) {
  
}
