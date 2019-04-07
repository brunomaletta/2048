#include <termios.h>
#include <stdio.h>

static struct termios old, new;

void initTermios(int echo);

void resetTermios(void);

char getch_(int echo);

char getch(void);

char getche(void);
