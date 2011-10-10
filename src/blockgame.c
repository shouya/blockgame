#include <stdlib.h>

#include <config.h>



int main(int argc, int argv) {
  loadconfig();

  mainloop();

  exit(0);
}
