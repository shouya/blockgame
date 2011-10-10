#ifndef _config_h_
#define _config_h_

#include <SDL/SDL.h>

#include <defines.h>

void loadconfig(const char* filename);

extern int g_lines;
extern int g_cols;
/* square box size, for pixel */
extern int g_boxsize;
/* how many ms per line falling */
extern int g_speed[MAX_LEVEL];
/* the canvas's background color */
extern Uint32 g_canvas_bg;


#endif /* _config_h_*/
