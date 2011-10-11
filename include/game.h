#ifndef _game_h_
#define _game_h_

#define GAME_STARTED 1
#define GAME_PAUSED 2
#define GAME_WAITING 3

extern int g_state;
extern int g_score;
extern int g_level;
extern int g_lnkilled;

void newgame(void);
void gameover(void);
void pausegmae(void);
void goal(int score);



#endif /* _game_h_ */
