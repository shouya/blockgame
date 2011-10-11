#include <stdio.h>
#include <stdlib.h>

#include <game.h>

#include <blockmap.h>
#include <shape.h>
#include <config.h>

int g_state = GAME_WAITING;
int g_score = 0;
int g_level = 0;
int g_lnkilled;


void newgame(void) {
  resetbmap();
  g_state = GAME_STARTED;
  g_score = 0;
  g_level = 0;
  g_lnkilled = 0;
  puts("game started!");
}


void gameover(void) {
  g_state = GAME_WAITING;
  printf("game over! your score is %d, level is %d!\n", g_score, g_level+1);
}

void pausegmae(void) {
  if (g_state == GAME_STARTED) {
    g_state = GAME_PAUSED;
    puts("paused.");
  } else if (g_state == GAME_PAUSED) {
    g_state = GAME_STARTED; 
    puts("unpaused.");
  }
}

void goal(int score) {
  g_score += score;
  if (g_score >= g_scorelst[g_level]) {
    ++g_level;
    if (g_level >= MAX_LEVEL) {
      gameover();
    }
  }
}
