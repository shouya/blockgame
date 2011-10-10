#include <stdlib.h>

#include <stdio.h>
#include <errno.h>

int main() {
  puts("fuck you at beginning");
  errno = EACCES;
  perror("fuck error, EACCES");
  puts("fuck you twice");
  errno = EADDRINUSE;
  perror("fuck error, EADDRINUSE");
  puts("fuck you at end");
  exit(0);
}
