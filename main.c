#include <stdio.h>

/* 
 * Build with:
 * gcc main.c -o a.out && ./a.out
 */

#define WIDTH 80
#define HEIGHT 10

#define CELL_TO_STR(X) X == 1 ? "X" : " "

typedef struct Board {
	int width;
	int height;
	int cells[HEIGHT][WIDTH];
} board;

void printHeader(board* b) {
	printf("+");
	for (int i = 0; i < b->width; i++)
		printf("-");
	printf("+\n");
}

void show(board* b) {
	printHeader(b);
	for (int y = 0; y < b->height; y++) {
		// print a line:
		printf("|");
		for (int x = 0; x < b->width; x++)
			printf("%s", CELL_TO_STR(b->cells[y][x]));
		printf("|\n");
	}
	printHeader(b);
}

int get(int x, int y, board* b) {
	// wrap board like a torus
	if (y < 0) {
		y = b->height + y;
	}
	if (x < 0) {
		x = b->width + x;
	}
	if (y >= b->height) {
		y = b->height - y;
	}
	if (x >= b->width) {
		x = b->width - x;
	}
	return b->cells[y][x];
}

int countNeighbors(int x, int y, board* b) {
	int n = 0;
	// dx and dy are deltas from the given (x, y) point,
	// Here is a graph:
	/*
		(x-1, y-1) | (x, y-1) | (x+1, y-1)
		(x-1, y  ) | (x, y  ) | (x+1, y  )
		(x-1, y+1) | (x, y+1) | (x+1, y+1)
	*/
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			// make sure we don't count the square we're checking around
			if (x+dx != x || y+dy != y) {
				// count alive squares
				if (get(x+dx, y+dy, b) == 1) {
					n++;
				}
			}
		}
	}
	return n;
}

int main() {
	/* Initialize board */
	board b = {WIDTH, HEIGHT};
	for (int y = 0; y < b.height; y++)
		for (int x = 0; x < b.width; x++)
			b.cells[y][x] = 0;

	b.cells[5][4] = 1;
	b.cells[5][6] = 1;
	b.cells[4][4] = 1;
	b.cells[4][5] = 1;
	b.cells[4][6] = 1;
	b.cells[6][4] = 1;
	b.cells[6][5] = 1;
	b.cells[6][6] = 1;
	show(&b);
	printf("Neighbors: %d\n", countNeighbors(5, 5, &b));
}

