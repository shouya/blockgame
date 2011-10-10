#ifndef _blockmap_h_
#define _blockmap_h_

struct {
  unsigned char r, g, b;
  unsigned char is_steady;
} block_t;

/* typedef block_t block_t; */

/* block_t bmap[y][x],
 * y = g_rows, x = g_cols */
extern struct block_t** bmap;

void initbmap(void);

#define POS_CENTER 0
#define POS_LEFT (-1)
#define POS_RIGHT 1

void insertblock(int position, int shape);


#endif /* _blockmap_h_ */
