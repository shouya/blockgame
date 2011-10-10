#include <string.h>

#include <stdio.h>

#include <config.h>

int g_lines;
int g_rows;
int g_speed[MAX_LEVEL];
int g_boxsize;

static void makedefault(void);

void loadconfig(const char* filename) {
  int fd;

  makedefault();
  if ((fd = open(filename, O_RDONLY)) == -1) {
    perror("open config file error");
    return;
  }
  /* todo: config loading */
}

void makedefault(void) {
  int i = 0;

  g_lines = 10;
  g_rows = 20;
  g_boxsize = 20;

  for (; i != MAX_LEVEL; ++i) {
    /* avg spd btw 100-500 */
    g_speed[i] = 100 + (500-100)/MAX_LEVEL*i;
  }
}
