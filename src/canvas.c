#include <SDL/SDL.h>

#include <canvas.h>

#include <config.h>
#include <blockmap.h>
#include <graphics.h>
#include <shape.h>

static SDL_Surface* canvas;



static void rendermap(void);
static void renderblocks(void);
static void rendershape(void);
static void renderghost(void);




void initcanvas(void) {
  canvas = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                g_cols * g_boxsize,
                                g_lines * g_boxsize,
                                32,
                                0xff<<16, 0xff<<8, 0xff, 0);

  if (!canvas) {
    perror(SDL_GetError());
  }
}

void destroycanvas(void) {
  SDL_FreeSurface(canvas);
}

void rendercanvas(void) {
  SDL_FillRect(canvas, NULL, g_canvas_bg);
  drawrect(canvas, 0, 0, canvas->clip_rect.w, canvas->clip_rect.h,
           0xff, 0xff, 0xff, 0xff);
  rendermap();
  renderghost();
  rendershape();
  renderblocks();
}

void blitcanvas(SDL_Surface* dst) {
  static SDL_Rect dst_rct = {CANVAS_X, CANVAS_Y};
  SDL_BlitSurface(canvas, NULL, dst, &dst_rct);
}


void rendermap(void) {
  int i, j, x, y;
  for (i = 0; i != g_cols; ++i) {
    for (j = 0; j != g_lines; ++j) {
      x = i * g_boxsize;
      y = j * g_boxsize;
      drawrect(canvas, x, y, g_boxsize, g_boxsize,
               0xff, 0xff, 0xff, 0x8);
    }
  }

  
}

void renderblocks(void) {
  int i, j, x, y;
  for (i = 0; i != g_cols; ++i) {
    for (j = 0; j != g_lines; ++j) {
      if (bmap[j*g_cols+i].is_occupied) {
        x = i * g_boxsize;
        y = j * g_boxsize;
        fillrect(canvas, x, y, g_boxsize, g_boxsize,
                 UNPIXRGB(g_shape[bmap[j*g_cols+i].shape].color), 0xf0);
        drawrect(canvas, x, y, g_boxsize, g_boxsize,
                 0xff, 0xff, 0xff, 0x30);
      }
    }
  }
}

void renderghost(void) {
  int i, j, x, y;
  if (g_ghost.shape < 0) { return; }
  for (i = 0; i != MOV_BUFSIZE; ++i) {
    for (j = 0; j != MOV_BUFSIZE; ++j) {
      if (i<0 || j<0 || i>=g_cols || j>=g_lines) return;
      if (g_ghost.pixbuf[j][i]) {
        x = i + g_ghost.x; x *= g_boxsize;
        y = j + g_ghost.y; y *= g_boxsize;
        fillrect(canvas, x, y, g_boxsize, g_boxsize,
                 UNPIXRGB(g_shape[g_ghost.shape].color), 0x30);
      }
    }
  }
}

void rendershape(void) {
  int i, j, x, y;
  if (g_movbuf.shape < 0) { return; }
  for (i = 0; i != MOV_BUFSIZE; ++i) {
    for (j = 0; j != MOV_BUFSIZE; ++j) {
      if (g_movbuf.pixbuf[j][i]) {
        x = i + g_movbuf.x; x *= g_boxsize;
        y = j + g_movbuf.y; y *= g_boxsize;
        fillrect(canvas, x, y, g_boxsize, g_boxsize,
                 UNPIXRGB(g_shape[g_movbuf.shape].color), 0xff);
        drawrect(canvas, x, y, g_boxsize, g_boxsize,
                 0xff, 0xff, 0xff, 0x7f);
      }
    }
  }
}

