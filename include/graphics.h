#ifndef _graphics_h_
#define _graphics_h_

#include <defines.h>

typedef struct SDL_Surface SDL_Surface;

inl void drawpixel(SDL_Surface* sfc, int x, int y,
               int r, int g, int b, int a);
inl void drawline(SDL_Surface* sfc, int x1, int y1, int x2, int y2,
              int r, int g, int b, int a);
inl void drawrect(SDL_Surface* sfc, int x, int y, int w, int h,
              int r, int g, int b, int a);
inl void fillrect(SDL_Surface* sfc, int x, int y, int w, int h,
              int r, int g, int b, int a);

/*#define PIXRGB(r,g,b) ((r&0xff)<<16|(g&0xff)<<8|(b&0xff))*/
#define PIXRGBA(r,g,b,a) (((r)<<16)|((g)<<8)|(b)|(a)<<24)
#define PIXRGB(r,g,b) PIXRGBA(r,g,b,0xff)
#define UNPIXRGB(rgb) ((rgb>>16)&0xff), ((rgb>>8)&0xff), (rgb&0xff)


#endif /* _graphics_h_ */
