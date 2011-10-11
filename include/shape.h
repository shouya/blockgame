#ifndef _shape_h_
#define _shape_h_

/*
shapeno 0    1    2      3      4       5        6
shape   O    I    L      J      Z       S        T

form   o o   o    o       o    o o       o o     o
       o o   o    o       o      o o   o o     o o o
             o    o o   o o
             o
*/

#define SHAPE_MAX_W 3
#define SHAPE_MAX_H 4

#define NUM_SHAPES 7

#define SHAPE_O 0
#define SHAPE_I 1
#define SHAPE_L 2
#define SHAPE_J 3
#define SHAPE_Z 4
#define SHAPE_S 5
#define SHAPE_T 6


struct shape_t {
  int no;
  char pixels[SHAPE_MAX_H][SHAPE_MAX_W];
  unsigned long color;
  int off_x;
  int w, h;
};

extern const struct shape_t g_shape[NUM_SHAPES];


/*                  shapeno,    y,           x  */

#endif /* _blockstyle_h_ */
