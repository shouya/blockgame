#ifndef _blockstyle_h_
#define _blockstyle_h_

/*
styleno 0    1    2      3      4       5        6
style   O    I    L      J      Z       S        T

form   o o   o    o       o    o o       o o     o
       o o   o    o       o      o o   o o     o o o
             o    o o   o o
             o
*/

#define NUM_STYLES 7

#define STYLE_O 0
#define STYLE_I 1
#define STYLE_L 2
#define STYLE_J 3
#define STYLE_Z 4
#define STYLE_S 5
#define STYLE_T 6

/*                 styleno,   y, x  */
extern char styles [NUM_STYLE][4][3]


#endif /* _blockstyle_h_ */
