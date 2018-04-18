#include <stdio.h>
#include <stdlib.h>

#define SEARCH_NUM 5

typedef struct {
	int size;
	int **table;
} Puzzle;

enum Direction {left, right, up, down};

void shift_array(int **array, int size)
{
	int index = 0;
	int old_n = *array[0];
	
	for (int i = 1; i < size; ++i) {
		if (*array[i] == 0) {
			continue;
		} else if (*array[i] == old_n) {
			*array[index] = old_n * 2;
			old_n = 0;
			index++;
		} else {
			if (old_n != 0) {
				*array[index] = old_n;
				index++;
			}
			old_n = *array[i];
		}
	}
	if (old_n != 0) {
		*array[index] = old_n;
		index++;
	}
	for (; index < size; index++) {
		*array[index] = 0;
	}
}

void shift_puzzle(Puzzle *load_puzzle, Puzzle *save_puzzle,  enum Direction d)
{
	int size = load_puzzle->size;
	int **array = (int**)malloc(size * sizeof(int*));
	int row, col;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			switch (d) {
			case left:
				row = i;
				col = j;
				break;
			case right:
				row = i;
				col = size - j - 1;
				break;
			case up:
				row = j;
				col = i;
				break;
			case down:
				row = size - j - 1;
				col = i;
				break;
			}
			save_puzzle->table[row][col] = load_puzzle->table[row][col];
			array[j] = &(save_puzzle->table[row][col]);
		}
		shift_array(array, size);
	}
	free(array);
}

int back_tracking(Puzzle* puzzles, int step, int max_num)
{
	static enum Direction directions[] = {left, right, up, down};
	static int num_of_directions = sizeof(directions) / sizeof(directions[0]);

	if (step == SEARCH_NUM) {
		for (int i = 0; i < puzzles[step].size; ++i) {
			for (int j = 0; j < puzzles[step].size; ++j) {
				if (max_num < puzzles[step].table[i][j]) {
					max_num = puzzles[step].table[i][j];
				}
			}
		}
		return max_num;
	} else {
		for (int i = 0; i < num_of_directions; ++i) {
			shift_puzzle(&puzzles[step], &puzzles[step + 1], directions[i]);
			max_num = back_tracking(puzzles, step + 1, max_num);
		}
		return max_num;
	}
}

int main()
{
	int N;
	scanf("%d", &N);

	Puzzle puzzle[SEARCH_NUM + 1];
	for (int i = 0; i < SEARCH_NUM + 1; ++i) {
		puzzle[i].size = N;
		puzzle[i].table = (int**)malloc(puzzle[i].size * sizeof(int*));
		for (int j = 0; j < puzzle[i].size; ++j) {
			puzzle[i].table[j] = (int*)malloc(puzzle[i].size * sizeof(int));
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &puzzle[0].table[i][j]);
		}
	}
	printf("%d", back_tracking(puzzle, 0, 0));
}
