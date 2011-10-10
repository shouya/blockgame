#include <stdlib.h>

#include <config.h>
#include <ui.h>
#include <blockmap.h>

int main(int argc, char** argv) {
  loadconfig("blockgame.conf");
  initbmap();
  initui();

  mainloop();

  exit(0);
}
