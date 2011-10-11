#include <shape.h>

#include <graphics.h>

#define _ {
#define O 1,
#define X 0,
#define __ },

const struct shape_t g_shape[NUM_SHAPES] = {
  { 0, /* O */
    {
      _ O O X __
      _ O O X __
      _ X X X __
      _ X X X __
    }, PIXRGB(0xff,0xff,0x0), /* O: Yellow */
    0, 2, 2,
  },
  { 1, /* I */
    {
      _ O X X __
      _ O X X __
      _ O X X __
      _ O X X __
    }, PIXRGB(0x0,0xff,0xff), /* I: Cyan */
    1, 1, 4,
  },
  { 2, /* L */
    {
      _ O X X __
      _ O X X __
      _ O O X __
      _ X X X __
    }, PIXRGB(0xff,0x7f,0x0), /* L: Orange*/
    1, 2, 3,
  },
  { 3, /* J */
    {
      _ X O X __
      _ X O X __
      _ O O X __
      _ X X X __
    }, PIXRGB(0x0,0x0, 0xff), /* J: Blue */
    0, 2, 3,
  },
  { 4, /* Z */
    {
      _ O O X __
      _ X O O __
      _ X X X __
      _ X X X __
    }, PIXRGB(0xff, 0x0,0x0), /* Z: Red */
    0, 3, 2,
  },
  { 5, /* S */
    {
      _ X O O __
      _ O O X __
      _ X X X __
      _ X X X __
    }, PIXRGB(0x0, 0xff,0x0), /* S: Lime */
    0, 3, 2,
  },
  { 6, /* T */
    {
      _ O O O __
      _ X O X __
      _ X X X __
      _ X X X __
    }, PIXRGB(0x7f,0x0,0x7f), /* T: Purple */
    0, 3, 2,
  },
};

#undef _
#undef O
#undef X
#undef __

