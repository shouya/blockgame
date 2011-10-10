#include <SDL/SDL.h>

#include <graphics.h>

inl static Uint32 mapRGBA(SDL_Surface* sfc, int r, int g, int b, int a) {
  return SDL_MapRGBA(sfc->format, r, g, b, a);
}

inl static Uint32 mapRGB(SDL_Surface* sfc, int r, int g, int b) {
  return SDL_MapRGB(sfc->format, r, g, b);
}

inl void drawpixel(SDL_Surface* sfc, int x, int y,
                        int r, int g, int b, int a) {
  if (x<0 || y<0 || x>=sfc->clip_rect.w || y>=sfc->clip_rect.h) {
    return;
  }
  if (a != 0xff) {
    static Uint8 o_r, o_g, o_b;
    SDL_GetRGB(((Uint32*)sfc->pixels)[y*sfc->clip_rect.w+x],
                sfc->format, &o_r, &o_g, &o_b);
    r = r*a + o_r*(0xff-a);
    g = g*a + o_g*(0xff-a);
    b = b*a + o_b*(0xff-a);
  }
  ((Uint32*)sfc->pixels)[y*sfc->clip_rect.w+x] = mapRGB(sfc, r, g, b);
}

inl void drawrect(SDL_Surface* sfc, int x, int y, int w, int h,
                       int r, int g, int b, int a) {
  int i;
  for (i = x; i != x+w; ++i) {
    drawpixel(sfc, i, y, r, g, b, a);
    drawpixel(sfc, i, y+h-1, r, g, b, a);
  }
  for (i = y+1; i != y+h-1; ++i) {
    drawpixel(sfc, x, i, r, g, b, a);
    drawpixel(sfc, x+w-1, i, r, g, b, a);
  }

}

inl void fillrect(SDL_Surface* sfc, int x, int y, int w, int h,
                       int r, int g, int b, int a) {
  int i, j;
  for (i = x; i != x+w; ++i) {
    for (j = y; j != y+h; ++j) {
      drawpixel(sfc, i, j, r, g, b, a);
    }
  }
  
}


