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

/*                  shapeno,    y,           x  */
extern char g_shape[NUM_SHAPES][SHAPE_MAX_H][SHAPE_MAX_W];
extern unsigned long g_shape_color[NUM_SHAPES];
extern int g_shape_offset[NUM_SHAPES];


#endif /* _blockstyle_h_ */
