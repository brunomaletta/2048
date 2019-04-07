#include "scoreboard.h"

void update_scoreboard(Board board) {
	FILE* scoreboard;
	switch (board.type) {
		case 0: scoreboard = fopen(".score_m.txt", "r"); break;
		case 1: scoreboard = fopen(".score_h.txt", "r"); break;
		case 2: scoreboard = fopen(".score_p.txt", "r"); break;
		case 3: scoreboard = fopen(".score_c.txt", "r"); break;
	}
	float score;
	fscanf(scoreboard, "%f", &score);
	fclose(scoreboard);
	if (score >= board.score) return;
	switch (board.type) {
		case 0: scoreboard = fopen(".score_m.txt", "w"); break;
		case 1: scoreboard = fopen(".score_h.txt", "w"); break;
		case 2: scoreboard = fopen(".score_p.txt", "w"); break;
		case 3: scoreboard = fopen(".score_c.txt", "w"); break;
	}
	fprintf(scoreboard, "%f\n\n", board.score);
	fprintf(scoreboard, "%d\n\n", board.base);
	fprintf(scoreboard, "%d\n\n", board.size);
	int i, j;
	for (i = 0; i < board.size; i++) {
		for (j = 0; j < board.size; j++) fprintf(scoreboard, j == 0 ? "%d" : " %d", board.tiles[i][j]);
		fprintf(scoreboard, "\n");
	}
	fclose(scoreboard);
}

void scoreboard() {
	while (1) {
		clear_screen();
		printf("SCOREBOARD\n\n");
		draw_diff();
		FILE* scoreboard;
		char c = getch();
		if (c == 'm' || c == 'M') scoreboard = fopen(".score_m.txt", "r");
		else if (c == 'h' || c == 'H') scoreboard = fopen(".score_h.txt", "r");
		else if (c == 'p' || c == 'P') scoreboard = fopen(".score_p.txt", "r");
		else if (c == 'c' || c == 'C') scoreboard = fopen(".score_c.txt", "r");
		else if (c == 'b' || c == 'B') break;
		else c = '\0';
		if (c != '\0') {
			float score;
			fscanf(scoreboard, "%f", &score);
			if (score == 0) {
				clear_screen();
				printf("No best score on this category\n");
				getch();
			} else {
				Board board;
				fscanf(scoreboard, "%d", &board.base);
				fscanf(scoreboard, "%d", &board.size);
				int i, j;
				for (i = 0; i < board.size; i++) for (j = 0; j < board.size; j++) fscanf(scoreboard, "%d", &board.tiles[i][j]);
				clear_screen();
				printf("Score: %.2f\n", score);
				draw_board(board);
				getch();
			}
			fclose(scoreboard);
		}
	}
}
