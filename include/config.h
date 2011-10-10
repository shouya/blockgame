#ifndef _config_h_
#define _config_h_

#include <defines.h>

void loadconfig(const char* filename);

extern int g_lines;
extern int g_rows;
/* square box size, for pixel */
extern int g_boxsize;
/* how many ms per line falling */
extern int g_speed[MAX_LEVEL];


#endif /* _config_h_*/
