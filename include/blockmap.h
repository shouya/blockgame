#ifndef _blockmap_h_
#define _blockmap_h_


#define FLAG_TRY       0x1 /* no use */
#define FLAG_MOVABLE   0x2 /* no use */
#define FLAG_STEADY    0x4
#define FLAG_GHOST     0x8


struct block_t {
  unsigned char shape;
  unsigned char is_occupied;
  unsigned char flags;
};
/* block_t bmap[y*g_cols + x],
 * y = g_lines, x = g_cols */
extern struct block_t* bmap;

#define MOV_BUFSIZE 4 /*SHAPE_MAX_H*/

struct movebuf_t {
  int shape;
  int x, y, rotate, w, h;
  char pixbuf[MOV_BUFSIZE][MOV_BUFSIZE];
};

extern struct movebuf_t g_movbuf;
extern struct movebuf_t g_ghost;


void initbmap(void);
void resetbmap(void);

void destroybmap(void);

void automovedown(void);
void moveleft(void);
void moveright(void);
void dropdown(void);
void softdrop(void);
void rotateleft(void);
void rotateright(void);

void newshape(int shape);

int trycreateshape(void);
void createshape(void);

#define MOVE_LEFT 1
#define MOVE_RIGHT 2
#define MOVE_DOWN 3

int trymove(int direction);
void domove(int direction);
int tryrotatebuf(int direction);
void rotatebuf(int direction);

void steadyall(void);
void checklines(void);

void createghost(void);
void updateghost(void);


#endif /* _blockmap_h_ */
