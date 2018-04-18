#include <stdio.h>

#define MAX_N 100
#define MAX_K 100
#define MAX_L 100

enum Direction {left, up, right, down};
enum State {blank, snake, apple};

typedef struct {
	enum State state;
	enum Direction direction;
} Cell;

typedef struct {
	int row;
	int col;
} Point;

typedef struct {
	int sec;
	char turn;
} TimeTable;

enum Direction turnDirection(enum Direction cur_d, char turn)
{
	if (turn == 'L') 
		--cur_d;
	if (turn == 'D') 
		++cur_d;
	return cur_d % 4;
}

Point move(Point p, enum Direction d)
{
	switch (d) {
	case left:
		--p.col;
		break;
	case right:
		++p.col;
		break;
	case up:
		--p.row;
		break;
	case down:
		++p.row;
		break;
	}
	return p;
}

void print_map(Cell map[MAX_N][MAX_N], int N)
{ 
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (map[i][j].state == blank) 
				printf("O ");
			else if (map[i][j].state == apple) 
				printf("X ");
			else if (map[i][j].direction == left) 
				printf("< ");
			else if (map[i][j].direction == right) 
				printf("> ");
			else if (map[i][j].direction == up) 
				printf("^ ");
			else if (map[i][j].direction == down) 
				printf("v ");
		}
		printf("\n");
	}
	printf("--------------------------------------------\n");
}

int runGame_rec(Cell map[MAX_N][MAX_N], TimeTable* tt, int N, int L, Point head, Point tail, int time)
{
    //printf("%d\n", time);
	//print_map(map, N);
	time++;
	enum Direction head_direction = map[head.row][head.col].direction;
	head = move(head, head_direction);

	if (head.row < 0 || N <= head.row || head.col < 0 || N <= head.col)
		return time;
	if (map[head.row][head.col].state == snake) 
		return time;

	if (L != 0 && tt[0].sec == time) {
		head_direction = turnDirection(head_direction, tt[0].turn);
		//printf("%c\n", tt[0].turn);
		L -= 1;
		tt++;
	}
	if (map[head.row][head.col].state != apple) {
		enum Direction tail_direction = map[tail.row][tail.col].direction;
		map[tail.row][tail.col].state = blank;
		tail = move(tail, tail_direction);
	}
	map[head.row][head.col].state = snake;
	map[head.row][head.col].direction = head_direction;

	return runGame_rec(map, tt, N, L, head, tail, time);
}

int runGame(Cell map[MAX_N][MAX_N], TimeTable tt[MAX_L], int N, int L)
{
	map[0][0].state = snake;
	map[0][0].direction = right;
	Point head = { .row = 0, .col = 0 };
	Point tail = { .row = 0, .col = 0 };
	return runGame_rec(map, tt, N, L, head, tail, 0);
}

int main()
{
	int N, K, L;

	Cell map[MAX_N][MAX_N];
	TimeTable tt[MAX_L];

	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			map[i][j].state = blank;
		}
	}
	int row, col;
	for (int i = 0; i < K; ++i) {
		scanf("%d%d", &row, &col);
		map[row - 1][col - 1].state = apple;
	}
	scanf("%d", &L);
	for (int i = 0; i < L; ++i) {
		scanf("%d %c", &tt[i].sec, &tt[i].turn);
	}

	printf("%d\n", runGame(map, tt, N, L));
}

