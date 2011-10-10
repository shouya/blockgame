#include <shape.h>

#include <graphics.h>

#define _ {
#define O 1,
#define X 0,
#define __ },
/*           styleno,    y,           x  */
char g_shape[NUM_SHAPES][SHAPE_MAX_H][SHAPE_MAX_W] = {
  { /* O */
    _ O O X __
    _ O O X __
    _ X X X __
    _ X X X __
  },
  { /* I */
    _ O X X __
    _ O X X __
    _ O X X __
    _ O X X __
  },
  { /* L */
    _ O X X __
    _ O X X __
    _ O O X __
    _ X X X __
  },
  { /* J */
    _ X O X __
    _ X O X __
    _ O O X __
    _ X X X __
  },
  { /* Z */
    _ O O X __
    _ X O O __
    _ X X X __
    _ X X X __
  },
  { /* S */
    _ X O O __
    _ O O X __
    _ X X X __
    _ X X X __
  },
  { /* T */
    _ O O O __
    _ X O X __
    _ X X X __
    _ X X X __
  },
};

#undef _
#undef O
#undef X
#undef __

unsigned long g_shape_color[NUM_SHAPES] = {
  PIXRGB(0xff,0xff,0x0), /* O: Yello */
  PIXRGB(0x0,0xff,0xff), /* I: Cyan */
  PIXRGB(0xff,0x7f,0x0), /* L: Orange*/
  PIXRGB(0x0,0x0, 0xff), /* J: Blue */
  PIXRGB(0xff, 0x0,0x0), /* Z: Red */
  PIXRGB(0x0, 0xff,0x0), /* S: Lime */
  PIXRGB(0x7f,0x0,0x7f), /* T: Purple */
};

int g_shape_offset[NUM_SHAPES] = {
  0, 1, 1, 0, 0, 0, 0
};


