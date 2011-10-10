#include <stdio.h>
#include <stdlib.h>

#include <game.h>

#include <blockmap.h>
#include <shape.h>

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
  newshape(rand()%NUM_SHAPES);
  puts("game started!");
}


void gameover(void) {
  g_state = GAME_WAITING;
  puts("game over!");
}




