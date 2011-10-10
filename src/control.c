#include <stdio.h>

#include <control.h>
#include <blockmap.h>

int g_state = GAME_WAITING;
int g_score = 0;
int g_level = 0;

void newgame(void) {
  if (g_state == GAME_STARTED || g_state == GAME_PAUSED) {
    resetbmap();
  }
  g_state = GAME_STARTED;
  g_score = 0;
  g_level = 0;
  puts("game started!");
}


void gameover(void) {
  g_state = GAME_WAITING;
  puts("game over!");
}



void ctrlleft(void) {
  if (trymove(MOVE_LEFT) == 0) {
    domove(MOVE_LEFT);
  }
}

void ctrlright(void) {
  if (trymove(MOVE_RIGHT) == 0) {
    domove(MOVE_RIGHT);
  }

}
