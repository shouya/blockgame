#include <SDL/SDL.h>

#include <graphics.h>

#include <font.h>


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
    Uint32 o = ((Uint32*)sfc->pixels)[y*sfc->clip_rect.w+x];
    r = (r*a + PIXR(o)*(0xff-a))>>8;
    g = (g*a + PIXG(o)*(0xff-a))>>8;
    b = (b*a + PIXB(o)*(0xff-a))>>8;
  }
  ((Uint32*)sfc->pixels)[y*sfc->clip_rect.w+x] =
    PIXRGB(r,g,b)/*mapRGB(sfc, r, g, b);*/;
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

inl int drawchar(SDL_Surface* sfc, int x, int y, int c,
                  int r, int g, int b, int a) {
  int i, j, w, bn = 0, ba = 0;
  char *rp = font_data + font_ptrs[c];
  w = *(rp++);
  for (j = 0; j != FONT_H; ++j) {
    for (i = 0; i != w; ++i) {
      if (!bn) {
        ba = *(rp++);
        bn = 8;
      }
      drawpixel(sfc, x+i, y+j, r, g, b, ((ba&3)*a)/3);
      ba >>= 2;
      bn -= 2;
    }
  }
  return x + w;
}


inl void drawtext(SDL_Surface* sfc, int x, int y, const char* s,
                  int r, int g, int b, int a) {
  int sx = x;
  for (; *s; ++s) {
    if (*s == '\n') {
      x = sx;
      y += FONT_H+2;
    } else if (*s == '\b') {
      switch (s[1]) {
      case 'w': r = g = b = 255; break;
      case 'g': r = b = 0; g = 255 ; break;
      case 'o': r = 255; g = 216; b = 32; break;
      case 'r': r = 255; g = b = 0; break;
      case 'b': r = g = 0; b = 255; break;
      case 't': b = 255; g = 170; r = 32; break;
      }
      ++s;
    } else {
      x = drawchar(sfc, x, y, *(unsigned char *)s, r, g, b, a);
    }
  }
}


