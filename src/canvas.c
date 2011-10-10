#include <SDL/SDL.h>

#include <canvas.h>

#include <config.h>
#include <blockmap.h>
#include <graphics.h>
#include <shape.h>

static SDL_Surface* canvas;

void initcanvas(void) {
  canvas = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                g_cols * g_boxsize,
                                g_lines * g_boxsize,
                                32,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
                                0xff, 0xff<<8, 0xff<<16, 0
#else
                                0xff<<16, 0xff<<8, 0xff, 0
#endif
    );

  if (!canvas) {
    perror(SDL_GetError());
  }
}

void destroycanvas(void) {
  SDL_FreeSurface(canvas);
}

void rendercanvas(void) {
  int i, j, x, y;
  SDL_FillRect(canvas, NULL, g_canvas_bg);
  for (i = 0; i != g_cols; ++i) {
    for (j = 0; j != g_lines; ++j) {
      if (bmap[j*g_cols+i].is_occupied) {
        x = i * g_boxsize;
        y = j * g_boxsize;
        fillrect(canvas, x, y, g_boxsize, g_boxsize,
                 UNPIXRGB(g_shape_color[bmap[j*g_cols+i].shape]), 0xff);
        drawrect(canvas, x, y, g_boxsize, g_boxsize,
                 0xff, 0xff, 0xff, 0x7f);

      } else if (bmap[j*g_cols+i].flags & FLAG_GHOST) {
        x = i * g_boxsize;
        y = j * g_boxsize;
        drawrect(canvas, x, y, g_boxsize, g_boxsize,
                 0xff, 0xff, 0xff, 0xff);
      }
    }
  }
}

void blitcanvas(SDL_Surface* dst) {
  static SDL_Rect dst_rct = {CANVAS_X, CANVAS_Y};
  SDL_BlitSurface(canvas, NULL, dst, &dst_rct);
}



