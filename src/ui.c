#include <sched.h>

#include <SDL/SDL.h>

#include <ui.h>
#include <canvas.h>
#include <graphics.h>
#include <control.h>

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

  SDL_EnableKeyRepeat(200, 100);


  for (; !is_quit;) {
    eventdeal();
    renderframe();
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
  default:;
  }
}
