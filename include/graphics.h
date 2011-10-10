#ifndef _graphics_h_
#define _graphics_h_

typedef Uint32 pixel;

inl void drawpixel(SDL_Surface* sfc, int x, int y,
               int r, int g, int b, int a);
inl void drawline(SDL_Surface* sfc, int x1, int y1, int x2, int y2,
              int r, int g, int b, int a);
inl void drawrect(SDL_Surface* sfc, int x, int y, int w, int h,
              int r, int g, int b, int a);
inl void fillrect(SDL_Surface* sfc, int x, int y, int w, int h,
              int r, int g, int b, int a);

#endif /* _graphics_h_ */
