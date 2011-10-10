#include <stdlib.h>

#include <strings.h>

#include <unistd.h>

#include <blockmap.h>
#include <config.h>
#include <shape.h>
#include <control.h>


struct block_t* bmap;

#define SHPBUF_EMPTY (-1)
static int shape_buf;

#define FLAG_TRY       0x1
#define FLAG_MOVABLE   0x2
#define FLAG_STEADY    0x4

static void blockrmflag(int x, int y, int flags);
static void blockaddflag(int x, int y, int flags);
static int createblock(int shape, int x, int y, int flags);
static void destoryblock(int x, int y);
/*static int moveblock(int x, int y, int off_x, int off_y);*/


void initbmap(void) {
  bmap = calloc(g_cols * g_lines, sizeof(struct block_t));
  if (!bmap) {
    perror("init bmap alloc memory failed");
  }
}

void resetbmap(void) {
  bzero(bmap, g_cols * g_lines * sizeof(struct block_t));
}


void destroybmap(void) {
  if (bmap) {
    free(bmap);
    bmap = NULL;
  }
}

void automovedown(void) {
  if (shape_buf != SHPBUF_EMPTY) {
    if (trycreateshape() == 0) {
      createshape();
    } else {
      gameover();
    }
  }

  if (trymove(MOVE_DOWN) == 0) {
    domove(MOVE_DOWN);
  } else {
    steadyall();
  }
}

void moveleft(void) {
  if (trymove(MOVE_LEFT) == 0) {
    domove(MOVE_LEFT);
  }
}

void moveright(void) {
  if (trymove(MOVE_RIGHT) == 0) {
    domove(MOVE_RIGHT);
  }
}


void newshape(int shape) {
  shape_buf = shape;
}

int createblock(int shape, int x, int y, int flags) {
  if (bmap[y*g_cols+x].is_occupied) {
    return -1;
  }
  bmap[y*g_cols+x].is_occupied = 1;
  bmap[y*g_cols+x].shape = shape;
  bmap[y*g_cols+x].flags = flags | FLAG_STEADY;
  return 0;
}


void destoryblock(int x, int y) {
  bmap[y*g_cols+x].is_occupied =
    bmap[y*g_cols+x].flags =
    bmap[y*g_cols+x].shape = 0;
}

void blockrmflag(int x, int y, int flags) {
  bmap[y*g_cols+x].flags &= ~flags;
}
void blockaddflag(int x, int y, int flags) {
  bmap[y*g_cols+x].flags |= flags;
}

/*
int moveblock(int x, int y, int off_x, int off_y) {
  int step = 0;
  if (x<0 || x>=g_cols || y<0 || y>=g_lines) {
    return -1;
  }
  if (bmap[y+off_y][x+off_x].is_occupied) {
    step = moveblock(x+off_x, y+off_y, off_x, off_y);
    if (step < 0) {
      return -1;
    }
  }
  
  bmap[y+off_y][x+off_x].is_occupied = 1;
  bmap[y+off_y][x+off_x].flags = bmap[y*g_cols+x].flags;
  bmap[y+off_y][x+off_x].shape = bmap[y*g_cols+x].shape;
  bmap[y*g_cols+x].flag = 0;
  bmap[y*g_cols+x].is_occupied = 0;
  bmap[y*g_cols+x].shape = 0;
  return step + 1;
}
*/

int trycreateshape(void) {
  int x, y, i, j;

  if (shape_buf == SHPBUF_EMPTY) {
    return 0;
  }
  for (j = SHAPE_MAX_H-1; j >= 0; --j) {
    for (i = 0; i != SHAPE_MAX_W; ++i) {
      if (g_shape[shape_buf][j][i]) {
        x = (g_cols-SHAPE_MAX_W)/2+g_shape_offset[shape_buf];
        y = j;
        if (x<0 || x>=g_cols || y<0 || y>=g_lines) {
          return -1;
        } else if (bmap[y*g_cols+x].is_occupied) {
          return -1;
        } else {
          continue;
        } /* if creatable */
      } /* */
    } /* for i */
  } /* for j */
  return 0;
}

void createshape(void) {
  int x, y, i, j;
  for (j = SHAPE_MAX_H-1; j >= 0; --j)
    for (i = 0; i != SHAPE_MAX_W; ++i)
      if (g_shape[shape_buf][j][i]) {
        x = (g_cols-SHAPE_MAX_W)/2+g_shape_offset[shape_buf];
        y = j;
        createblock(shape_buf, x, y, FLAG_MOVABLE);
      }
  shape_buf = SHPBUF_EMPTY;
  return;
}

int trymove(int direction) {
  int i, j, x, y;
  if (direction == MOVE_LEFT) {
    for (j = 0; j != g_lines; ++j) {
      for (i = 0; i != g_cols; ++i) {
        if (bmap[j*g_cols+i].is_occupied && (bmap[j*g_cols+i].flags & FLAG_MOVABLE)) {
          x = i-1;
          y = j;
          if (x<0 || x>=g_cols || y<0 || y>=g_lines) {
            return -1;
          } else if (bmap[y*g_cols+x].is_occupied) {
            return -1;
          } /* if failed */
        } /* if movable */
      } /* for i++ */
    } /* for j++ */
  } else if (direction == MOVE_RIGHT) { /* move right */
    for (j = 0; j != g_lines; ++j) {
      for (i = g_cols-1; i >= 0; --i) {
        if (bmap[j*g_cols+i].is_occupied && (bmap[j*g_cols+i].flags & FLAG_MOVABLE)) {
          x = i+1;
          y = j;
          if (x<0 || x>=g_cols || y<0 || y>=g_lines) {
            return -1;
          } else if (bmap[y*g_cols+x].is_occupied) {
            return -1;
          } /* if failed */
        } /* if movable */
      } /* for i-- */
    } /* for j++ */
  } else if (direction == MOVE_DOWN) {
    for (i = 0; i != g_cols; ++i) {
      for (j = g_lines-1; j >= 0; --j) {
        if (bmap[j*g_cols+i].is_occupied && (bmap[j*g_cols+i].flags & FLAG_MOVABLE)) {
          x = i;
          y = j+1;
          if (x<0 || x>=g_cols || y<0 || y>=g_lines) {
            return -1;
          } else if (bmap[y*g_cols+x].is_occupied) {
            return -1;
          } /* if failed */
        } /* if movable */
      } /* for j-- */
    } /* for i++ */
  } /* direction selector */
  return 0;
}

void domove(int direction) {
  int x, y, i, j;
  if (direction == MOVE_LEFT) {
    for (j = 0; j != g_lines; ++j) {
      for (i = 0; i != g_cols; ++i) {
        if (bmap[j*g_cols+i].is_occupied && (bmap[j*g_cols+i].flags & FLAG_MOVABLE)) {
          x = i-1;
          y = j;
          bmap[y*g_cols+x].flags = bmap[j*g_cols+i].flags;
          bmap[y*g_cols+x].is_occupied = 1;
          bmap[y*g_cols+x].shape = bmap[j*g_cols+i].shape;
          destoryblock(i, j);
        }
      } /* for i++ */
    } /* for j++ */
  } else if (direction == MOVE_RIGHT) { /* move right */
    for (j = 0; j != g_lines; ++j) {
      for (i = g_cols-1; i >= 0; --i) {
        if (bmap[j*g_cols+i].is_occupied && (bmap[j*g_cols+i].flags & FLAG_MOVABLE)) {
          x = i+1;
          y = j;
          bmap[y*g_cols+x].flags = bmap[j*g_cols+i].flags;
          bmap[y*g_cols+x].is_occupied = 1;
          bmap[y*g_cols+x].shape = bmap[j*g_cols+i].shape;
          destoryblock(i, j);
        }
      } /* for i-- */
    } /* for j++ */
  } else if (direction == MOVE_DOWN) {
    for (i = 0; i != g_cols; ++i) {
      for (j = g_lines-1; j >= 0; --j) {
        if (bmap[j*g_cols+i].is_occupied && (bmap[j*g_cols+i].flags & FLAG_MOVABLE)) {
          x = i;
          y = j+1;
          bmap[y*g_cols+x].flags = bmap[j*g_cols+i].flags;
          bmap[y*g_cols+x].is_occupied = 1;
          bmap[y*g_cols+x].shape = bmap[j*g_cols+i].shape;
          destoryblock(i, j);
        }
      } /* for j-- */
    } /* for           bmap[j*g_cols+i].flags = 0;
          bmap[j*g_cols+i].is_occupied = 0;
          bmap[j*g_cols+i].shape = 0;
i++ */
  } /* direction selector */
}


void steadyall(void) {
  int i, j;
  for (i = 0; i != g_cols; ++i)
    for (j = 0; j != g_lines; ++j)
      if (bmap[j*g_cols+i].is_occupied && (bmap[j*g_cols+i].flags & FLAG_MOVABLE)) {
        blockrmflag(i, j, FLAG_MOVABLE);
        blockaddflag(i, j, FLAG_STEADY);
      }
  return;
}

