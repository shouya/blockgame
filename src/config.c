#include <string.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <config.h>

#include <graphics.h>

int g_lines;
int g_cols;
int g_speed[MAX_LEVEL];
int g_boxsize;
Uint32 g_canvas_bg;

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

  g_cols = 10;
  g_lines = 20;
  g_boxsize = 20;
  g_canvas_bg = PIXRGB(0,0,0);

  for (; i != MAX_LEVEL; ++i) {
    /* avg spd btw 100-500 */
    g_speed[i] = 100 + (500-100)/MAX_LEVEL*i;
  }
}
