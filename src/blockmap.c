#include <stdlib.h>

#include <strings.h>

#include <unistd.h>

#include <blockmap.h>
#include <config.h>
#include <shape.h>
#include <game.h>

struct move_buf {
  int shape;
  int w, h;
  
  int pixbuf[4][4];
};

struct block_t* bmap;

#define SHPBUF_EMPTY (-1)

static int shape_buf;
static struct move_buf mov_buf;

static void blockrmflag(int x, int y, int flags);
static void blockaddflag(int x, int y, int flags);
static int createblock(int shape, int x, int y, int flags);
static void destoryblock(int x, int y);
/*static int moveblock(int x, int y, int off_x, int off_y);*/
static void killline(int ln);


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
      if (g_shape[shape_buf].pixels[j][i]) {
        x = (g_cols-SHAPE_MAX_W)/2+g_shape[shape_buf].off_x+i;
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
      if (g_shape[shape_buf].pixels[j][i]) {
        x = (g_cols-SHAPE_MAX_W)/2+g_shape[shape_buf].off_x+i;
        y = j;
        createblock(shape_buf, x, y, FLAG_MOVABLE);
      }
  shape_buf = SHPBUF_EMPTY;
  return;
}

int trymove(int direction) {
  int i, j, x, y;
  static int xno[80], yno[80];
  int nop = 0;
  if (direction == MOVE_LEFT) {
    for (j = 0; j != g_lines; ++j) {
      for (i = 0; i != g_cols; ++i) {
        if (bmap[j*g_cols+i].is_occupied && (bmap[j*g_cols+i].flags & FLAG_MOVABLE)) {
          x = i-1;
          y = j;
          if (x<0 || x>=g_cols || y<0 || y>=g_lines) {
            return -1;
          } else if (bmap[y*g_cols+x].is_occupied) {
            int p, nothing = 0;
            for (p = 0; p != nop; ++p) {
              if (xno[p] == x && yno[p] == y) {
                nothing = 1;
                break;
              }
            }
            if (!nothing) {
              return -1;
            }
          } /* if failed */
          xno[nop] = i;
          yno[nop++] = j;
        } /* if movable */
      } /* for i++ */
    } /* for j++ */
  } else if (direction == MOVE_RIGHT) { /* move right */
    for (j = 0; j != g_lines; ++j) {
      for (i = g_cols-1; i >= 0; --i) {
        if (bmap[j*g_cols+i].is_occupied &&
            (bmap[j*g_cols+i].flags & FLAG_MOVABLE)) {
          x = i+1;
          y = j;
          if (x<0 || x>=g_cols || y<0 || y>=g_lines) {
            return -1;
          } else if (bmap[y*g_cols+x].is_occupied) {
            int p, nothing = 0;
            for (p = 0; p != nop; ++p) {
              if (xno[p] == x && yno[p] == y) {
                nothing = 1;
                break;
              }
            }
            if (!nothing) {
              return -1;
            }
          } /* if failed */
          xno[nop] = i;
          yno[nop++] = j;
        } /* if movable */
      } /* for i-- */
    } /* for j++ */
  } else if (direction == MOVE_DOWN) {
    for (i = 0; i != g_cols; ++i) {
      for (j = g_lines-1; j >= 0; --j) {
        if (bmap[j*g_cols+i].is_occupied &&
            (bmap[j*g_cols+i].flags & FLAG_MOVABLE)) {
          x = i;
          y = j+1;
          if (x<0 || x>=g_cols || y<0 || y>=g_lines) {
            return -1;
          } else if (bmap[y*g_cols+x].is_occupied) {
            int p, nothing = 0;
            for (p = 0; p != nop; ++p) {
              if (xno[p] == x && yno[p] == y) {
                nothing = 1;
                break;
              }
            }
            if (!nothing) {
              return -1;
            }
          } /* if failed */
          xno[nop] = i;
          yno[nop++] = j;
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
    } /* for i++ */
  } /* direction selector */
  createghost();
}


void steadyall(void) {
  int i, j;
  for (i = 0; i != g_cols; ++i)
    for (j = 0; j != g_lines; ++j)
      if (bmap[j*g_cols+i].is_occupied && (bmap[j*g_cols+i].flags & FLAG_MOVABLE)) {
        blockrmflag(i, j, FLAG_MOVABLE);
        blockaddflag(i, j, FLAG_STEADY);
      }

  /* after steady, create a new shape */
  newshape(rand()%NUM_SHAPES);
  checklines();

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
      ++num_killed;
    }
  }
  g_score += num_killed * num_killed * SCORE_PER_LINE;
  if (num_killed)
    printf("gotcha! now score: %d\n", g_score);
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

/* BUG !!!! */
void createghost(void) {
  int i,j, h=99, ij, nop = 0, x, y;
  static int xno[80], yno[80];
  for (i = 0; i != g_cols; ++i) {
    for (j = g_lines-1; j >= 0; --j) {
      blockrmflag(i, j, FLAG_GHOST);
      if (bmap[j*g_cols+i].is_occupied &&
          (bmap[j*g_cols+i].flags & FLAG_MOVABLE)) {
        x = i;
        ij = 1;
        for (;;) {
          y = j+ij;
          if (x<0 || x>=g_cols || y<0 || y>=g_lines) {
            break;
          } else if (bmap[y*g_cols+x].is_occupied) {
            int p, nothing = 0;
            for (p = 0; p != nop; ++p) {
              if (xno[p] == x && yno[p] == y) {
                nothing = 1;
                break;
              }
            }
            if (!nothing) {
              break;
            } else {
              xno[nop] = x;
              yno[nop++] = y;
            }
          } else {
            xno[nop] = x;
            yno[nop++] = y;
          }
          ++ij;
        }
        if (ij < h) {
          h = ij;
          printf("x %d, y %d , ij %d, h %d\n", x, y, ij, h);
        }
      }
    }
  }
  for (i = 0; i != g_cols; ++i) {
    for (j = g_lines-1; j >= 0; --j) { 
      if (bmap[j*g_cols+i].is_occupied &&
          (bmap[j*g_cols+i].flags & FLAG_MOVABLE)) {
        x = i;
        y = j+h;
        blockaddflag(x, y, FLAG_GHOST);
      }
    }
  }
}
