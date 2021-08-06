#include <stdio.h>
#include <sys/time.h>
#include "sleep.h"

/* 
 * Build with:
 * gcc main.c -o a.out && ./a.out
 *
 * This has been tested on Ubuntu 20.04
 */

#define WIDTH 80
#define HEIGHT 10

#define CELL_TO_STR(X) X == 1 ? "X" : " "

typedef struct Board {
	int width;
	int height;
	int cells[HEIGHT][WIDTH];
	int nextCells[HEIGHT][WIDTH];
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

void setNext(int x, int y, int state, board* b) {
	b->nextCells[y][x] = state;
}

void applyRules(int x, int y, board* b) {
	int n = countNeighbors(x, y, b);

	// Any live cell
	if (get(x, y, b) == 1) {
		if (n < 2) { // with fewer than two live neighbours
			// dies, as if by underpopulation.
			setNext(x, y, 0, b);
		} else if (n > 3) { // with more than three live neighbours
			// dies, as if by overpopulation.
			setNext(x, y, 0, b);
		} else { // with two or three live neighbours
			// lives on to the next generation.
			setNext(x, y, 1, b);
		}
	} else {
		// Any dead cell with exactly three live neighbours
		// becomes a live cell, as if by reproduction.
		if (n == 3) {
			setNext(x, y, 1, b);
		} else {
			setNext(x, y, 0, b);
		}
	}
}

void tick(board* b) {
	// generate next frame
	for (int y = 0; y < b->height; y++)
		for (int x = 0; x < b->width; x++)
			applyRules(x, y, b);

	// copy next frame to current frame
	for (int y = 0; y < b->height; y++)
		for (int x = 0; x < b->width; x++)
			b->cells[y][x] = b->nextCells[y][x];
}

int main() {
	/* Initialize board */
	board b = {WIDTH, HEIGHT};
	for (int y = 0; y < b.height; y++)
		for (int x = 0; x < b.width; x++)
			b.cells[y][x] = 0;
	for (int y = 0; y < b.height; y++)
		for (int x = 0; x < b.width; x++)
			b.nextCells[y][x] = 0;

	// a glider:
	b.cells[5][5] = 1;
	b.cells[6][6] = 1;
	b.cells[6][7] = 1;
	b.cells[5][7] = 1;
	b.cells[4][7] = 1;

	struct timeval stop, start;
	for (;;) {
		gettimeofday(&start, NULL);
		tick(&b);
		gettimeofday(&stop, NULL);
		show(&b);
		printf("frame generated in %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 
		sleep_ms(100);
	}
}

