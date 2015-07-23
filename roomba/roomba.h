#ifndef ROOMBA_H
#define	ROOMBA_H

#include "eagle_soc.h"

#define ROOMBA_WAKEUP_PIN	BIT2

void roomba_startup(void);
void roomba_wakeup(void);
void roomba_dock(void);
void roomba_clean(void);
void roomba_sleep(void);
void roomba_motors(char *);
void roomba_play_song(char *);
void roomba_program_songs(void);

#endif
