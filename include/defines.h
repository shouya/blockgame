#ifndef _defines_h_
#define _defines_h_

#ifdef __GNUC__
# define inl __inline
#else
# define inl _inline
#endif /*__GNUC__ * inline */

#define MAX_LEVEL 15

#define XRES 200
#define YRES 400
#define CANVAS_X 0
#define CANVAS_Y 0

#define SCORE_PER_LINE 10


#endif /* _defines_h_ */
