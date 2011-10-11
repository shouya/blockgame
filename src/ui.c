#include <time.h>
#include <stdlib.h>

#include <sched.h>

#include <SDL/SDL.h>

#include <ui.h>
#include <canvas.h>
#include <graphics.h>
#include <control.h>
#include <game.h>
#include <config.h>
#include <blockmap.h>

SDL_Surface* g_ui;

static int is_quit;

static void eventdeal(void);
static void kbdeventdeal(SDL_KeyboardEvent* e);

void initui(void) {
  g_ui = SDL_SetVideoMode(XRES, YRES, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
  if (!g_ui) {
    perror(SDL_GetError());
    return;
  }
  SDL_WM_SetCaption("The Block Game", 0);
  
  initcanvas();
}

void renderframe(void) {
  SDL_FillRect(g_ui, NULL, PIXRGB(0xff,0xff,0xff));
  rendercanvas();
  blitcanvas(g_ui);
  SDL_Flip(g_ui);
}

void destroyui(void) {
  destroycanvas();
  SDL_FreeSurface(g_ui);
}

void mainloop(void) {
  is_quit = 0;
  int tick = SDL_GetTicks();

  SDL_EnableKeyRepeat(100, 70);

  srand(time(NULL));
  for (; !is_quit;) {
    eventdeal();
    renderframe();

    if (g_state == GAME_STARTED) {
      if (SDL_GetTicks() - tick >= g_speed[g_level]) {
        tick = SDL_GetTicks();
        automovedown();
      }
    }

    sched_yield();
  }

}

void eventdeal(void) {
  static SDL_Event event;
  if (SDL_PollEvent(&event)) {
    /* deal events */
    switch (event.type) {
    case SDL_QUIT:
      is_quit = 1;
      break;
    case SDL_KEYDOWN:
      kbdeventdeal(&event.key);
      break;
    default:;
    }
  }
}

void kbdeventdeal(SDL_KeyboardEvent* e) {
  switch (e->keysym.sym) {
  case SDLK_q:
    is_quit = 1;
    return;
  case SDLK_n:
    if (e->keysym.mod & KMOD_CTRL) {
      newgame();
    }
    break;
  case SDLK_LEFT:
    ctrlleft();
    break;
  case SDLK_RIGHT:
    ctrlright();
    break;
  case SDLK_DOWN:
    ctrlsoftdrop();
    break;
  case 'x':
  case SDLK_UP:
    ctrlrotateright();
    break;
  case 'z':
    ctrlrotateleft();
    break;
  case SDLK_SPACE:
    ctrldrop();
    break;
  default:;
  }
}
