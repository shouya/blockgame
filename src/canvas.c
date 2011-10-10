#include <SDL/SDL.h>

#include <config.h>

static SDL_Surface* canvas;

void initcanvas(void) {
  canvas = SDL_CreateRGBSurface(SDL_HWSURFACE,
                                g_cols * g_boxsize,
                                g_rows * g_boxsize,
                                32,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
                                0xff<<6, 0xff<<4, 0xff<<2, 0xff
#else
                                0xff, 0xff<<2, 0xff<<4, 0xff<<6
#endif
    );

  if (!canvas) {
    perror(SDL_GetError());
  }
}

void destroycanvas(void) {
  if (canvas) {
    SDL_FreeSurface(canvas);
  }
}

void rendercanvas(void) {
}


