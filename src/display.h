#include <stdio.h>
#include <math.h>

#include "board.h"
#include "curses.h"

#define NUMBER_SPACE 5

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m" // colors
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

void clear_screen();

void daw_file(char file[]);

void draw_how_to_play();

void draw_run_menu();

void draw_menu();

void draw_diff();

void draw_number(int n, int base);

void draw_line(int length);

void draw_tiles(int line[], int size, int base);

void draw_board(Board board);

void how_to_play();
