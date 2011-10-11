#include <stdio.h>

#include <SDL/SDL.h>

#include <extpanel.h>

#include <config.h>
#include <graphics.h>
#include <game.h>
#include <font.h>
#include <shape.h>
#include <blockmap.h>

#define X_MARGIN 5
#define Y_MARGIN 5
#define TEXT_COLOR PIXRGB(0,0x7f,0)
#define TEXT_BUFSIZE 512

static SDL_Surface* panel;



static int renderinfo(int h);
static int renderqueue(int h);
static int renderhold(int h);


void initpanel(void) {
  panel = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                XRES - g_cols * g_boxsize,
                                YRES, 32,
                                0xff<<16, 0xff<<8, 0xff, 0);


  if (!panel) {
    perror(SDL_GetError());
  }
}

void destroypanel(void) {
  SDL_FreeSurface(panel);
}
void renderpanel(void) {
  int h = Y_MARGIN;
  SDL_FillRect(panel, NULL, g_panel_bg);
  h = renderinfo(h);
  h = renderhold(h);
  h = renderqueue(h);
}



void blitpanel(SDL_Surface* dst) {
  static SDL_Rect dst_rct = {PANEL_X, PANEL_Y};
  SDL_BlitSurface(panel, NULL, dst, &dst_rct);
}

int renderinfo(int h) {
  static char s[TEXT_BUFSIZE];
  snprintf(s, TEXT_BUFSIZE, "Game %s",
           g_state == GAME_STARTED? "\bgstarted":
           g_state == GAME_PAUSED?  "\bbpaused" :
           g_state == GAME_WAITING? "\brstopped": "unknown");
  drawtext(panel, X_MARGIN, h, s, 0xff, 0xff, 0xff, 0xff);
  h += FONT_H + 2;

  snprintf(s, TEXT_BUFSIZE, "Score \bg%d", g_score);
  drawtext(panel, X_MARGIN, h, s, 0xff, 0xff, 0xff, 0xff);
  h += FONT_H + 2;

  snprintf(s, TEXT_BUFSIZE, "Level \bg%d", g_level+1);
  drawtext(panel, X_MARGIN, h, s, 0xff, 0xff, 0xff, 0xff);
  h += FONT_H + 2;

  snprintf(s, TEXT_BUFSIZE, "Lines \bg%d", g_lnkilled);
  drawtext(panel, X_MARGIN, h, s, 0xff, 0xff, 0xff, 0xff);
  h += FONT_H + 2;

  return h;
}
int renderqueue(int h) {
  int i, j, x, y, q = 0;
  const int nxt_sz = 15;
  const int oth_sz = 4;
  if (g_state != GAME_STARTED) return h;

  drawtext(panel, X_MARGIN, h, "\nNext:", 0xff, 0xff, 0xff, 0xff);
  h += FONT_H*2 + 3;

  for (i = 0; i != g_shape[g_queue[q]].w; ++i) {
    for (j = 0; j != g_shape[g_queue[q]].h; ++j) {
      if (g_shape[g_queue[q]].pixels[j][i]) {
        x = (i /*+ g_shape[g_queue[q]].off_x*/) * nxt_sz; y = j * nxt_sz;
        x += X_MARGIN; y += h;
        fillrect(panel, x, y, nxt_sz, nxt_sz,
                 UNPIXRGB(g_shape[g_queue[q]].color), 0xff);
      }
    }
  }

  for (q = 1; q != QUEUE_SIZE; ++q) {
    for (i = 0; i != g_shape[g_queue[q]].w; ++i) {
      for (j = 0; j != g_shape[g_queue[q]].h; ++j) {
        if (g_shape[g_queue[q]].pixels[j][i]) {
          x = (i /*+ g_shape[g_queue[q]].off_x*/) * oth_sz; y = j * oth_sz;
          x += X_MARGIN+nxt_sz*SHAPE_MAX_W+10; y += h;
          fillrect(panel, x, y, oth_sz, oth_sz,
                   UNPIXRGB(g_shape[g_queue[q]].color),
                   0xff-0xf0*q/QUEUE_SIZE);
        }
      }
    }
    h += SHAPE_MAX_H * oth_sz + 3;
  }

  return h; /* 6*4 + 6 */
}

int renderhold(int h) {
  int i, j, x, y;
  const int shape_sz = 18;
  const int const_h = shape_sz * SHAPE_MAX_H + 6;
  if (g_state != GAME_STARTED) return h;
  drawtext(panel, X_MARGIN, h, "\nHolding:", 0xff, 0xff, 0xff, 0xff);
  h += FONT_H*2 + 3;
  drawrect(panel, X_MARGIN, h, shape_sz * SHAPE_MAX_W + 6,
           shape_sz * SHAPE_MAX_H + 6, 0xff, 0xff, 0xff, 0x7f);
  h += 3;
  if (g_hold == -1) return h+const_h;
  for (i = 0; i != g_shape[g_hold].w; ++i) {
    for (j = 0; j != g_shape[g_hold].h; ++j) {
      if (g_shape[g_hold].pixels[j][i]) {
        x = (i + g_shape[g_hold].off_x) * 18; y = j * 18;
        x += X_MARGIN + 3; y += h;
        fillrect(panel, x, y, 18, 18,
                 UNPIXRGB(g_shape[g_hold].color), 0xff);
      }
    }
  }
  return h+const_h;
}


