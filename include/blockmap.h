#ifndef _blockmap_h_
#define _blockmap_h_


struct block_t {
  unsigned char shape;
  unsigned char is_occupied;
  unsigned char flags;
};

#define FLAG_TRY       0x1
#define FLAG_MOVABLE   0x2
#define FLAG_STEADY    0x4
#define FLAG_GHOST     0x8



/* typedef block_t block_t; */

/* block_t bmap[y*g_cols + x],
 * y = g_lines, x = g_cols */
extern struct block_t* bmap;


void initbmap(void);
void resetbmap(void);

void destroybmap(void);

void automovedown(void);
void moveleft(void);
void moveright(void);

void newshape(int shape);

int trycreateshape(void);
void createshape(void);

#define MOVE_LEFT 1
#define MOVE_RIGHT 2
#define MOVE_DOWN 3

int trymove(int direction);
void domove(int direction);

void steadyall(void);

void checklines(void);

void createghost(void);


#endif /* _blockmap_h_ */
