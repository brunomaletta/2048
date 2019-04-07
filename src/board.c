#include "board.h"

int size(int base) { return 2 * base; } // default

Board new_board(int size, int base, int type) {
	Board ret;
	ret.base = base;
	ret.size = size;
	ret.free = size * size;
	ret.score = 0;
	ret.type = type; // 0 -> medium ; 1 -> hard ; 2 -> pro ; 3 -> custom
	int i, j;
	for (i = 0; i < ret.size; i++) for (j = 0; j < ret.size; j++) ret.tiles[i][j] = 0;
	return ret;
}

Board mirror(Board board) {
	Board ret;
	ret.base = board.base;
	ret.size = board.size;
	ret.free = board.free;
	ret.score = board.score;
	ret.type = board.type;
	int i, j;
	for (i = 0; i < board.size; i++) for (j = 0; j < board.size; j++) ret.tiles[i][j] = board.tiles[i][board.size - 1 - j];
	return ret;
}

Board transp(Board board) {
	Board ret;
	ret.base = board.base;
	ret.size = board.size;
	ret.free = board.free;
	ret.score = board.score;
	ret.type = board.type;
	int i, j;
	for (i = 0; i < board.size; i++) for (j = 0; j < board.size; j++) ret.tiles[i][j] = board.tiles[j][i];
	return ret;
}
