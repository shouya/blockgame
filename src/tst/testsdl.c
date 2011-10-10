#include <SDL/SDL.h>
#include <stdlib.h>


#define W 800
#define H 600

#define PIXRGB(r,g,b) ((((r)<<16)&0xFF0000)|(((g)<<8)&0xFF00)|((b)&0xFF))

typedef unsigned long pixel;
void drawpixel(pixel* pix, int x, int y, int r, int g, int b);
void drawrect(pixel* pix, int x, int y, int w, int h, int r, int g, int b);

int main() {
  SDL_Surface* sfc;
  SDL_Event event;
  Uint32 tick = SDL_GetTicks();
  int x = W/2 - 50, y = H/2 - 100;
  
  SDL_Init(SDL_INIT_EVERYTHING);

  sfc = SDL_SetVideoMode(W, H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

  srand((rand()%rand()%rand())*rand());

  for (;;) {
    SDL_PollEvent(&event);
    if (SDL_GetTicks() - tick > 50) {
      x += rand()%3-1;
      y += rand()%3-1;
      tick = SDL_GetTicks();
    }
/*    SDL_FillRect(sfc, &sfc->clip_rect, mapRGB(sfc, 0,0,0));*/
    SDL_FillRect(sfc, &sfc->clip_rect, PIXRGB(0,0,0));
    drawrect(sfc->pixels, x+10, y, 100, 200, 127, 255, 255);
    drawrect(sfc->pixels, x, y+10, 100, 200, 127, 255, 255);
    drawrect(sfc->pixels, x, y, 100, 200, 127, 255, 255);
    drawrect(sfc->pixels, x+10, y+10, 100, 200, 127, 255, 255);

    if (event.type == SDL_QUIT) {
      break;
    }
    SDL_Flip(sfc);
  }
  return 0;
}


void drawpixel(pixel* pix, int x, int y, int r, int g, int b) {
  if (x < 0 || x >= W || y < 0 || y >= H) {
    return;
  }
  pix[y*W+x] = PIXRGB(r,g,b);
}

void drawrect(pixel* pix, int x, int y, int w, int h, int r, int g, int b) {
  int i;
  for (i = x; i != x+w; ++i) {
    drawpixel(pix, i, y, r, g, b);
    drawpixel(pix, i, y+h-1, r, g, b);
  }
  for (i = y+1; i != y+h-1; ++i) {
    drawpixel(pix, x, i, r, g, b);
    drawpixel(pix, x+w-1, i, r, g, b);
  }
}

