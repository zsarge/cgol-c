#include <stdio.h>

/* 
 * Build with:
 * gcc main.c -o a.out && ./a.out
 */

#define WIDTH 80
#define HEIGHT 10

typedef struct Board {
	int width;
	int height;
	int cells[HEIGHT][WIDTH];
} board;

void printHeader(board* b) {
	for (int i = 0; i < b->width + 2; i++)
		printf("-");
	printf("\n");
}

void show(board* b) {
	printHeader(b);
	for (int y = 0; y < b->height; y++) {
		// print a line:
		printf("|");
		for (int x = 0; x < b->width; x++)
			printf("%s", b->cells[y][x] == 1 ? "X" : " ");
		printf("|\n");
	}
	printHeader(b);
}

int main() {
	/* Initialize board */
	board b = {WIDTH, HEIGHT};
	for (int y = 0; y < b.height; y++)
		for (int x = 0; x < b.width; x++)
			b.cells[y][x] = 0;

	b.cells[5][5] = 1;

	show(&b);
}

