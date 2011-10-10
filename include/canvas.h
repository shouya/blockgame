#ifndef _canvas_h_
#define _canvas_h_

struct SDL_Surface;

void initcanvas(void);
void destroycanvas(void);
void rendercanvas(void);
void blitcanvas(SDL_Surface* dst);

#endif /* _canvas_h_ */
