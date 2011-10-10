#include <stdlib.h>

#include <config.h>



int main(int argc, int argv) {
  loadconfig();

  initenv();

  initui();

  mainloop();

  exit(0);
}
