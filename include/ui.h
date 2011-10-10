#ifndef _ui_h_
#define _ui_h_

struct SDL_Surface* g_ui;

void initui(void);
void destroyui(void);
void renderframe(void);
void mainloop(void);

#endif /* _ui_h_ */
