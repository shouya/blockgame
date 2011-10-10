#include <shape.h>

#define _ {
#define O 1,
#define X 0,
#define __ },
/*            styleno,   y, x  */
char g_shapes [NUM_SHAPES][4][3] = {
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

