#include "display.h"

void clear_screen() { printf("\e[1;1H\e[2J"); }

void draw_file(char file[]) {
	FILE* f = fopen(file, "r");
	char l[200];
	while (fgets(l, 200, f) != NULL) printf("%s", l);
	fclose(f);
}

void draw_how_to_play() { draw_file("files/how_to_play.txt"); }

void draw_run_menu() { draw_file("files/run_menu.txt"); }

void draw_menu() { draw_file("files/menu.txt"); }

void draw_diff() { draw_file("files/diff.txt"); }

void draw_number(int n, int base) {
	int p = round(log(n) / log(base));
	switch (p % 7) {
		case 0: printf(WHT "%d" RESET, n); break;
		case 1: printf(RED "%d" RESET, n); break;
		case 2: printf(GRN "%d" RESET, n); break;
		case 3: printf(YEL "%d" RESET, n); break;
		case 4: printf(BLU "%d" RESET, n); break;
		case 5: printf(MAG "%d" RESET, n); break;
		case 6: printf(CYN "%d" RESET, n); break;
	}
}

void draw_line(int length) { int i; for (i = 0; i < length; i++) printf("–"); printf("\n"); }

void draw_tiles(int* line, int size, int base) {
	printf("|");
	int i, j;
	for (i = 0; i < size; i++) {
		int x = line[i];
		if (x == 0) for (j = 0; j < NUMBER_SPACE; j++) printf(" "); // blank tile
		else {
			int n_size = floor(log10(x)) + 1;
			for (j = 0; j < ceil((NUMBER_SPACE - n_size) / (float) 2); j++) printf(" "); // space before number
			draw_number(x, base); // number
			for (j = 0; j < (NUMBER_SPACE - n_size) / 2; j++) printf(" "); // space after number
		} printf("|");
	} printf("\n");
}

void draw_board(Board board) {
	int i, j, k;
	int line_size = board.size * NUMBER_SPACE + board.size + 1;
	draw_line(line_size);
	for (i = 0; i < board.size; i++) {
		draw_tiles(board.tiles[i], board.size, board.base);
		draw_line(line_size);
	}
}

void how_to_play() {
	Board board1 = new_board(4, 2, 0), board2 = new_board(4, 2, 0),
	      		board3 = new_board(4, 2, 0), board4 = new_board(4, 2, 0);
	board1.tiles[2][2] = 2;
	board2.tiles[2][0] = 2; board2.tiles[0][2] = 4;
	board3.tiles[0][3] = 2; board3.tiles[1][1] = 2; board3.tiles[2][0] = 16;
	board3.tiles[2][1] = 16; board3.tiles[3][0] = 2; board3.tiles[3][1] = 4;
	board3.tiles[3][2] = 4; board3.tiles[3][3] = 4;
	board4.tiles[0][0] = 2; board4.tiles[1][0] = 2; board4.tiles[2][0] = 32;
	board4.tiles[2][3] = 2; board4.tiles[3][0] = 2; board4.tiles[3][1] = 8;
	board4.tiles[3][2] = 4;

	FILE* h = fopen("files/how_to_play.txt", "r");
	char l[200];
	int i, j;
	clear_screen();
	printf("Press enter to keep reading\n\n[E] Exit\n\n");
	char c = getch();
	for (i = 0; c != 'e' && c != 'E'; i++) {
		if (i == 0) {
			for (j = 0; j < 3; j++) {
				fgets(l, 200, h);
				printf("\n%s", l);
				c = getch();
				if (c == 'e' || c == 'E') break;
			}
		} else if (i == 1) {
			printf("\n");
			draw_board(board1);
			c = getch();
		} else if (i == 2) {
			for (j = 0; j < 2; j++) {
				fgets(l, 200, h);
				printf("\n%s", l);
				c = getch();
				if (c == 'e' || c == 'E') break;
			}
		} else if (i == 3) {
			printf("\n");
			draw_board(board2);
			c = getch();
		} else if (i == 4) {
			for (j = 0; j < 2; j++) {
				fgets(l, 200, h);
				printf("\n%s", l);
				c = getch();
				if (c == 'e' || c == 'E') break;
			}
		} else if (i == 5) {
			printf("\n");
			draw_board(board3);
			c = getch();
		} else if (i == 6) {
			fgets(l, 200, h);
			printf("\n%s", l);
			c = getch();
		} else if (i == 7) {
			printf("\n");
			draw_board(board4);
			c = getch();
		} else if (i == 8) {
			for (j = 0; j < 4; j++) {
				fgets(l, 200, h);
				printf("\n%s", l);
				c = getch();
				if (c == 'e' || c == 'E') break;
			}
		} else if (i == 9) {
			printf("\n\n[E] Exit\n");
		} else {
			c = getch();
		}
	}
	fclose(h);
}
