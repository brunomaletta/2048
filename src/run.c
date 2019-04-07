#include <math.h>

#include "run.h"

int prob(int one_in) { 	return (rand() / (double) RAND_MAX) <= (1 / (double) one_in) ? 1 : 0; }

void generate_number(Board* board) {
	int free_bu = board->free;
	int i, j, stop = 0;
	for (i = 0; i < board->size && !stop; i++) for (j = 0; j < board->size && !stop; j++) if (board->tiles[i][j] == 0) {
		if (prob(free_bu) == 1) {
			if (prob(board->base + 1) == 0) { // put number
				board->tiles[i][j] = board->base;
				board->score += board->base / pow(board->size, 2);
			} else {
				board->tiles[i][j] = pow(board->base, 2);
				board->score += pow(board->base, 2) / pow(board->size, 2);
			}
			stop = 1;
		}
		free_bu--;
	}
	board->free -= 1; // ocupy
}

int slide(Board* board, int dir) { // return 1 if changed, 0 if not
	if (dir == 0 || dir == 1) { // up or down -> transpose and recall slide
		Board board_t = transp(*board);
		int ret = slide(&board_t, 3 - dir);
		Board board_t_t = transp(board_t);
		*board = board_t_t;
		return ret;
	} else if (dir == 2) { // right -> mirror and recall slide
		Board board_m = mirror(*board);
		int ret = slide(&board_m, dir + 1);
		Board board_m_m = mirror(board_m);
		*board = board_m_m;
		return ret;
	}
	int i, j, k, x, changed = 0;
	for (i = 0; i < board->size; i++) { // left
		for (x = 0; x < 2; x++) { //  pull - join - pull
		for (j = 0; j < board->size - 1; j++) if (board->tiles[i][j] == 0) { // pull
			for (k = j + 1; k < board->size; k++) if (board->tiles[i][k] != 0) {
				changed = 1;
				board->tiles[i][j] = board->tiles[i][k];
				board->tiles[i][k] = 0;
				break;
			}
		}
		if (x == 1) break; // don't join twice
		for (j = 0; j < board->size - board->base + 1; j++) { // join
			int first = board->tiles[i][j];
			int join = 1;
			if (first == 0) join = 0;
			for (k = j + 1; k < j + board->base && join; k++) { if (board->tiles[i][k] != first) join = 0; }
			if (join) {
				board->tiles[i][j] *= board->base;
				for (k = j + 1; k < j + board->base; k++) board->tiles[i][k] = 0;
				board->free += board->base - 1; // free tiles joined
				j++; // don't join formed
				changed = 1;
			}
		}}
	}
	return changed;
}

int move() {
	__fpurge(stdin);
	char c = getch();
	if (c == 'u' || c == 'U') return 4;
	else if (c == 'e' || c == 'E') return -1;
	else if ((int) c != 27) return 5;
	getch();
	switch (getch()) {
		case 'A': return 0; // up
		case 'B': return 1; // down
		case 'C': return 2; // right
		case 'D': return 3; // left
	}
	return -1;
}

void run(int base, int size, int type, int c) { // c -> 0 if new game, 1 if continue game
	Board board;
	if (c == 0) {
		FILE* cont = fopen("files/cont.txt", "r");
		int c_base; fscanf(cont, "%d", &c_base);
		if (c_base != 0) {
			printf("\nOverwrite ongoing game? (y/n) ");
			while (1) {
				char c = getch();
				if (c == 'n' || c == 'N') return;
				else if (c == 'y' || c == 'Y') break;
			}
		}
		board = new_board(size, base, type);
		generate_number(&board);
	} else {
		FILE* cont = fopen("files/cont.txt", "r");
		int c_base; fscanf(cont, "%d", &c_base);
		if (c_base == 0) {
			clear_screen();
			printf("No ongoing game\n");
			getch();
			return;
		}
		board.base = c_base;
		fscanf(cont, "%d", &board.size);
		fscanf(cont, "%d", &board.free);
		fscanf(cont, "%f", &board.score);
		fscanf(cont, "%d", &board.type);
		int i, j;
		for (i = 0; i < board.size; i++) for (j = 0; j < board.size; j++) fscanf(cont, "%d", &board.tiles[i][j]);
		fclose(cont);
	}
	Board last = board;
	while(1) {
		if (board.free == 0) { // lose condition: no free tiles
			Board board2 = board, board3 = board;
			if (slide(&board2, 1) == 0 && slide(&board3, 2) == 0) { // and no moves
				update_scoreboard(board);
				FILE* cont = fopen("files/cont.txt", "w");
				fprintf(cont, "0\n");
				fclose(cont);
				clear_screen();
				printf("\n\nYou lose!\n\n[E] Exit\n\nScore: %.2f\n", board.score);
				draw_board(board);
				while (1) {
					char c = getch();
					if (c == 'e' || c == 'E') break;
				}
				return;
			}
		}
		clear_screen();
		draw_run_menu();
		printf("\nScore: %.2f\n", board.score);
		draw_board(board);
		int in = move();
		if (in == 4) board = last;
		else if (in == -1) break;
		else if (in != 5) {
			Board last_bu = last;
			last = board;
			if (slide(&board, in) == 1) generate_number(&board);
			else last = last_bu;
		}
	}
	update_scoreboard(board);
	FILE* cont = fopen("files/cont.txt", "w");
	fprintf(cont, "%d\n\n", board.base);
	fprintf(cont, "%d\n\n", board.size);
	fprintf(cont, "%d\n\n", board.free);
	fprintf(cont, "%f\n\n", board.score);
	fprintf(cont, "%d\n\n", board.type);
	int i, j;
	for (i = 0; i < board.size; i++) {
		for (j = 0; j < board.size; j++) fprintf(cont, j == 0 ? "%d" : " %d", board.tiles[i][j]);
		fprintf(cont, "\n");
	}
	fclose(cont);
}
