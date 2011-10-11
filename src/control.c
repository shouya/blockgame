#include <stdio.h>

#include <control.h>
#include <blockmap.h>
#include <game.h>

void ctrlleft(void) {
  if (g_state == GAME_STARTED) {
    moveleft();
  }
}

void ctrlright(void) {
  if (g_state == GAME_STARTED) {
    moveright();
  }
}

void ctrldrop(void) {
  if (g_state == GAME_STARTED) {
    dropdown();
  }
}


void ctrlsoftdrop(void) {
  if (g_state == GAME_STARTED) {
    softdrop();
  }
}

void ctrlrotateright(void) {
  if (g_state == GAME_STARTED) {
    rotateright();
  }
}

void ctrlrotateleft(void) {
  if (g_state == GAME_STARTED) {
    rotateleft();
  }
}
