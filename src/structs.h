#ifndef STRUCTS
#define STRUCTS

#define MAX_SIZE 50

typedef struct {
	int base;
	int size;
	int free;
	float score;
	int type;
	int tiles[MAX_SIZE][MAX_SIZE];
} Board;

#endif
