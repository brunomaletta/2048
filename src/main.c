#include <stdlib.h>
#include <time.h>

#include "run.h"
#include "display.h"
#include "scoreboard.h"

int main() {
	srand((unsigned) time(NULL)); // rand seed
	while (1) {
		clear_screen();
		draw_menu();
		char c = getch();
		if (c == 'n' || c == 'N') { // new game
			while (1) {
				clear_screen();
				printf("NEW GAME\n\n");
				draw_diff();
				char d = getch();
				int stop = 1;
				if (d == 'm' || d == 'M') run(2, size(2), 0, 0);
				else if (d == 'h' || d == 'H') run(3, size(3), 1, 0);
				else if (d == 'p' || d == 'P') run(5, size(5), 2, 0);
				else if (d == 'c' || d == 'C') {
					clear_screen();
					int base;
					printf("Enter the base number [2, 20]: ");
					scanf("%d", &base);
					if (base < 2 || base > 20) {
						clear_screen();
						printf("Invalid base number\n");
						__fpurge(stdin);
						getch();
					} else {
						int size;
						printf("Enter the board size [1, 40] (default = 2 * base number): ");
						scanf("%d", &size);
						if (size < 1 || size > 40) {
							clear_screen();
							printf("Invalid size number\n");
							__fpurge(stdin);
							getch();
						} else run(base, size, 3, 0);
					}
				} else if (d == 'b' || d == 'B') break;
				else stop = 0;
				if (stop) break;
			}
		} else if (c == 'c' || c == 'C') run(0, 0, 0, 1); // continue game
		else if (c == 's' || c == 'S') scoreboard(); // scoreboard
		else if (c == 'h' || c == 'H') how_to_play(); // how to play 
		else if (c == 'e' || c == 'E') break; // exit
	}
	clear_screen();
	return 0;
}
