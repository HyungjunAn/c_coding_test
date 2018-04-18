#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_K 100
#define MAX_L 100

typedef enum {left, up, right, down} Direction;
typedef enum {blank, snake, apple} State;

typedef struct {
	int row;
	int col;
} Point;

typedef struct Snake_cell {
    struct Snake_cell* next;
    Point point;
} Snake_cell;

typedef struct {
	int sec;
	char turn;
} TimeTable;

typedef struct {
    Snake_cell* head;
    Snake_cell* tail;
} Snake_queue;

void head_insert(Snake_queue* sq, Point point)
{
    Snake_cell* new_head = (Snake_cell*)malloc(sizeof(Snake_cell));
    new_head->next = NULL;
    new_head->point = point;
    sq->head->next = new_head;
    sq->head = new_head;
}
void tail_pop(Snake_queue* sq)
{
    Snake_cell* tmp = sq->tail;
    sq->tail = sq->tail->next;
    free(tmp);
}
Direction turnDirection(Direction cur_d, char turn)
{
	if (turn == 'L') 
		--cur_d;
	if (turn == 'D') 
		++cur_d;
	return cur_d % 4;
}

Point move(Point p, Direction d)
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

void print_map(State map[MAX_N][MAX_N], int N)
{ 
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (map[i][j] == blank) 
				printf("O ");
			else if (map[i][j] == apple) 
				printf("X ");
			else 
				printf("* ");
		}
		printf("\n");
	}
	printf("--------------------------------------------\n");
}

int runGame_rec(State map[MAX_N][MAX_N], TimeTable* tt, int N, int L, Snake_queue* sq, Direction head_d, int time)
{
    //printf("%d\n", time);
	//print_map(map, N);
	time++;
    Point head = move(sq->head->point, head_d);
    head_insert(sq, head);

	if (head.row < 0 || N <= head.row || head.col < 0 || N <= head.col)
		return time;
	if (map[head.row][head.col] == snake)
		return time;

	if (L != 0 && tt[0].sec == time) {
		head_d = turnDirection(head_d, tt[0].turn);
		//printf("%c\n", tt[0].turn);
		L -= 1;
		tt++;
	}
    if (map[head.row][head.col] != apple) {
        Point tail = sq->tail->point;
		map[tail.row][tail.col] = blank;
        tail_pop(sq);
	}
	map[head.row][head.col] = snake;

	return runGame_rec(map, tt, N, L, sq, head_d, time);
}

int runGame(State map[MAX_N][MAX_N], TimeTable tt[MAX_L], int N, int L)
{
	map[0][0] = snake;
    Snake_queue sq;
    sq.head = (Snake_cell*)malloc(sizeof(Snake_cell));
    sq.head->point.row = 0;
    sq.head->point.col = 0;
    sq.head->next = NULL;
    sq.tail = sq.head;
	return runGame_rec(map, tt, N, L, &sq, right, 0);
}

int main()
{
	int N, K, L;

	State map[MAX_N][MAX_N];
	TimeTable tt[MAX_L];

	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			map[i][j] = blank;
		}
	}
	int row, col;
	for (int i = 0; i < K; ++i) {
		scanf("%d%d", &row, &col);
		map[row - 1][col - 1] = apple;
	}
	scanf("%d", &L);
	for (int i = 0; i < L; ++i) {
		scanf("%d %c", &tt[i].sec, &tt[i].turn);
	}

	printf("%d\n", runGame(map, tt, N, L));
}

