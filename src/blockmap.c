#include <stdlib.h>

#include <strings.h>

#include <unistd.h>

#include <blockmap.h>
#include <config.h>
#include <shape.h>
#include <game.h>

#include <util.h>

struct block_t* bmap;
struct movebuf_t g_movbuf;
struct movebuf_t g_ghost;

int g_queue[QUEUE_SIZE];
int g_hold, g_canswap;

#define SHPBUF_EMPTY (-1)

static int shape_buf;

static void killline(int ln);
static int checkmovbuf(void);
static void setmovbuf(int shape, int x, int y, int rotate);


void initbmap(void) {
  bmap = calloc(g_cols * g_lines, sizeof(struct block_t));
  if (!bmap) {
    perror("init bmap alloc memory failed");
  }
}

void resetbmap(void) {
  int i;
  bzero(bmap, g_cols * g_lines * sizeof(struct block_t));
  for (i = 0; i != QUEUE_SIZE; ++i) {
    g_queue[i] = myrand() % NUM_SHAPES ;
  }
  g_canswap = 1;
  g_hold = -1;
  newshape(shiftqueue());
  automovedown();
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
      g_movbuf.shape = -1;
      g_ghost.shape = -1;
    }
    return;
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
  updateghost();
}

void moveright(void) {
  if (trymove(MOVE_RIGHT) == 0) {
    domove(MOVE_RIGHT);
  }
  updateghost();
}

void dropdown(void) {
  do {
    ++g_movbuf.y;
  } while (checkmovbuf() == 0);
  --g_movbuf.y;
}

void softdrop(void) {
  ++g_movbuf.y;
  if (checkmovbuf() != 0) {
    --g_movbuf.y;
  }
}

void rotateleft(void) {
  if (tryrotatebuf(-1) == 0) {
    rotatebuf(-1);
  }
  updateghost();
}
void rotateright(void) {
  if (tryrotatebuf(1) == 0) {
    rotatebuf(1);
  }
  updateghost();
}

void newshape(int shape) {
  shape_buf = shape;
}


int trycreateshape(void) {
  if (shape_buf == SHPBUF_EMPTY) {
    return 0;
  }

  setmovbuf(shape_buf, (g_cols-g_shape[shape_buf].w)/2, 0, 0);
  return checkmovbuf();
}

void createshape(void) {
  setmovbuf(shape_buf, (g_cols-g_shape[shape_buf].w)/2, 0, 0);
  shape_buf = SHPBUF_EMPTY;
  createghost();
  return;
}

int trymove(int direction) {
  if (direction == MOVE_LEFT) {
    --g_movbuf.x;
    if (checkmovbuf() == 0) {
      ++g_movbuf.x;
      return 0;
    } else {
      ++g_movbuf.x;
      return -1;
    }
  } else if (direction == MOVE_RIGHT) {
    ++g_movbuf.x;
    if (checkmovbuf() == 0) {
      --g_movbuf.x;
      return 0;
    } else {
      --g_movbuf.x;
      return -1;
    }
  } else if (direction == MOVE_DOWN) {
    ++g_movbuf.y;
    if (checkmovbuf() == 0) {
      --g_movbuf.y;
      return 0;
    } else {
      --g_movbuf.y;
      return -1;
    }
  } else { /* unkown direction */
    return -1;
  }
}

void domove(int direction) {
  if (direction == MOVE_LEFT) {
    --g_movbuf.x;
  } else if (direction == MOVE_RIGHT) { /* move right */
    ++g_movbuf.x;
  } else if (direction == MOVE_DOWN) {
    ++g_movbuf.y;
  } /* direction selector */
}


void steadyall(void) {
  int i, j, x, y;
  if (checkmovbuf() != 0) {
    return;
  }

  for (i = 0; i != MOV_BUFSIZE; ++i) {
    for (j = 0; j != MOV_BUFSIZE; ++j) {
      if (g_movbuf.pixbuf[j][i]) {
        x = i + g_movbuf.x;
        y = j + g_movbuf.y;
        bmap[y*g_cols+x].is_occupied = 1;
        bmap[y*g_cols+x].shape = g_movbuf.shape;
        bmap[y*g_cols+x].flags = FLAG_STEADY;
      }
    }
  }

  /* after steady, create a new shape */
  checklines();
  newshape(shiftqueue());

  g_movbuf.shape = -1;

  updateghost();

  g_canswap = 1;

  return;
}


void checklines(void) {
  int i, j;
  int lncheck;
  int num_killed = 0;
  for (j = g_lines-1; j >= 0; --j) {
    lncheck = 1;
    for (i = 0; i != g_cols; ++i) {
      if (!bmap[j*g_cols+i].is_occupied) {
        lncheck = 0;
        break;
      }
    }
    if (lncheck) {
      killline(j);
      ++j; /* recheck the line */
      ++num_killed;
    }
  }

  g_lnkilled += num_killed;
  goal(num_killed * num_killed * SCORE_PER_LINE);
}


void killline(int ln) {
  int i, j, y, x;
  for (j = ln-1; j >= 0; --j) {
    for (i = 0; i != g_cols; ++i) {
      y = j+1; x=i;
      bmap[y*g_cols+x].is_occupied = bmap[j*g_cols+i].is_occupied;
      bmap[y*g_cols+x].shape = bmap[j*g_cols+i].shape;
      bmap[y*g_cols+x].flags = bmap[j*g_cols+i].flags;
    }
  }
}

void createghost(void) {
  memcpy(&g_ghost, &g_movbuf, sizeof(struct movebuf_t));
  updateghost();
}

void updateghost(void) {
  int h;
  if (g_movbuf.shape == -1) {
    g_ghost.shape = -1;
  }
  if (g_ghost.rotate != g_movbuf.rotate) {
    memcpy(&g_ghost.pixbuf, &g_movbuf.pixbuf, MOV_BUFSIZE*MOV_BUFSIZE);
    g_ghost.rotate = g_movbuf.rotate;
  }
  g_ghost.x = g_movbuf.x;
  h = g_movbuf.y;
  dropdown();
  g_ghost.y = g_movbuf.y;
  g_movbuf.y = h;
}

/** static functions  **/
int checkmovbuf(void) {
  int i, j, x, y, nopix = 1;
  for (i = 0; i != MOV_BUFSIZE; ++i) {
    for (j = 0; j != MOV_BUFSIZE; ++j) {
      if (g_movbuf.pixbuf[j][i]) {
        nopix = 0;
        x = i + g_movbuf.x;
        y = j + g_movbuf.y;
        if (x<0 || y<0 || x>=g_cols || y>=g_lines) {
          return -1;
        }
        if (bmap[y*g_cols+x].is_occupied) {
          return -1;
        }
      }
    }
  }
  if (nopix) return -1;
  return 0;
}

void setmovbuf(int shape, int x, int y, int rotate) {
  int i, j;
  /* DBG printf("shape is %d\n", shape); */
  for (j = 0; j != MOV_BUFSIZE; ++j) {
    for (i = 0; i != MOV_BUFSIZE; ++i) {
      if (i >= g_shape[shape].w || j >= g_shape[shape].h) {
        g_movbuf.pixbuf[j][i] = 0;
      } else {
#ifdef __GNUC__
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Warray-bounds"
#endif /* __GNUC__ */
        /* how to ignore -Warray-bounds here */
        g_movbuf.pixbuf[j][i] = g_shape[shape].pixels[j][i];
#ifdef __GNUC__
# pragma GCC diagnostic pop
#endif /* __GNUC__ */
      }
      /* DBG printf("%c ", g_movbuf.pixbuf[j][i]?'o':' '); */
    }
    /* DBG printf("\n"); */
  }
  g_movbuf.shape = shape;
  g_movbuf.x = x; g_movbuf.y = y;
  g_movbuf.rotate = rotate;
  g_movbuf.w = g_shape[shape].w; g_movbuf.h = g_shape[shape].h;
}

int tryrotatebuf(int dir) {
  int success;
  rotatebuf(dir);
  success = checkmovbuf();
  rotatebuf(-dir);
  return success;
}

void rotatebuf(int dir) {
  static int xb[MOV_BUFSIZE*MOV_BUFSIZE];
  static int yb[MOV_BUFSIZE*MOV_BUFSIZE];
  int p = 0, i, j;
  for (i = 0; i != MOV_BUFSIZE; ++i) {
    for (j = 0; j != MOV_BUFSIZE; ++j) {
      if (g_movbuf.pixbuf[j][i]) {
        if (dir == 1) { /* clock wise 90' */
          xb[p] = g_movbuf.h - (j+1);
          yb[p] = i;
        } else if (dir == -1) { /* counter clockwise 90' */
          xb[p] = j;
          yb[p] = g_movbuf.w - (i+1);
        } else { /* just do nothing */
          xb[p] = i;
          yb[p] = j;
        }
        ++p;
      } /* if pixel */
    } /* for j */
  } /* for i */

  /* set the new position of pixels */
  bzero(g_movbuf.pixbuf, MOV_BUFSIZE*MOV_BUFSIZE*sizeof(char));
  for (i = 0; i != p; ++i) {
    g_movbuf.pixbuf[yb[i]][xb[i]] = 1;
  }
  if (dir == 1 || dir == -1) { /* swap the width with height */
    int swp = g_movbuf.w;
    g_movbuf.w = g_movbuf.h;
    g_movbuf.h = swp;
  }
  /* modify the rotate flag */
  g_movbuf.rotate += dir;
  if (g_movbuf.rotate == -1) g_movbuf.rotate = 3;
  if (g_movbuf.rotate == 4) g_movbuf.rotate = 0;

} /* end function rotatebuf */


void hold(void) {
  if (g_canswap && g_movbuf.shape != -1) {
    if (g_hold != -1) {
      int shp = g_movbuf.shape;
      g_movbuf.shape = -1;
      newshape(g_hold);
      g_hold = shp;
    } else {
      g_hold = g_movbuf.shape;
      g_movbuf.shape = -1;
      newshape(shiftqueue());
    }
    automovedown();
    g_canswap = 0;
  }
}

int shiftqueue(void) {
  int s = g_queue[0], i;
  for (i = 1; i != QUEUE_SIZE; ++i) {
    g_queue[i-1] = g_queue[i];
  }
  g_queue[QUEUE_SIZE-1] = myrand() % NUM_SHAPES;
  return s;
}
