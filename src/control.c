#include <stdio.h>

#include <control.h>
#include <blockmap.h>

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
