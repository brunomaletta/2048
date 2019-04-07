#include <stdlib.h> // rand
#include <math.h>
#include <stdio_ext.h> // __fpurge

#include "display.h"
#include "board.h"
#include "curses.h"
#include "scoreboard.h"

int prob(int one_in);

void generate_number(Board* board);

int slide(Board* board, int dir);

int move();

void run(int base, int size, int type, int c);
