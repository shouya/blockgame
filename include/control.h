#ifndef _control_h_
#define _control_h_

#define GAME_STARTED 1
#define GAME_PAUSED 2
#define GAME_WAITING 3

extern int g_gstate;
extern int g_score;
extern int g_level;

void newgame(void);
void gameover(void);

void ctrlleft(void);
void ctrlright(void);

#endif /* _control_h_ */
