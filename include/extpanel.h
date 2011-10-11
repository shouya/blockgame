#ifndef _extpanel_h_
#define _extpanel_h_


struct SDL_Surface;

void initpanel(void);
void destroypanel(void);
void renderpanel(void);
void blitpanel(SDL_Surface* dst);


#endif /* _extpanel_h_ */
