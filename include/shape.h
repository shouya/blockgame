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

#define NUM_SHAPES 7

#define SHAPE_O 0
#define _I 1
#define SHAPE_L 2
#define SHAPE_J 3
#define SHAPE_Z 4
#define SHAPE_S 5
#define SHAPE_T 6

/*                  shapeno,   y, x  */
extern char g_shapes[NUM_SHAPE][4][3]


#endif /* _blockstyle_h_ */
