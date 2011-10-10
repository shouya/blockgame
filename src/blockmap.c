#include <unistd.h>

#include <blockmap.h>
#include <config.h>

struct block_t** bmap;

void initbmap(void) {
  bmap = calloc(g_cols * g_rows, sizeof(struct block_t));
  if (!bmap) {
    perror("initbmap alloc memory failed");
  }
}

void insertblock(int position, int shape) {
  
}
