/*
 * chess.c
 *
 *  Created on: 2016年3月24日
 *      Author: liu
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chess.h"

struct coordinate {
	unsigned int x;
	unsigned int y;
};

#define CHESS_SIZE 7
#define TRUE 1
#define FALSE 0

static unsigned int chess[CHESS_SIZE][CHESS_SIZE] = {0};

void chess_show() {
	int i, j;
	for(i=CHESS_SIZE-1; i>=0; i--) {
		printf("%2u |", i);
		for(j=0; j<CHESS_SIZE; j++) {
			//printf("%u, %u] %u\t", i, j, chess[i][j]);
			printf("%2u ", chess[i][j]);
//			if(j == CHESS_SIZE-1)
//				printf("| %2u\n", i);
		}
		puts("");
	}
	printf("---|");
	for(i=0; i< CHESS_SIZE; i++) {
		printf("---");
	}
	printf("\n x |");
	for(i=0; i< CHESS_SIZE; i++) {
		printf("%2u ", i);
	}
	puts("");
}

void debug_show(const char *label, struct coordinate *p, int dir) {
	printf("%s: %u %u, dir: %u\n", label, p->x, p->y, dir);
}

static int check_coordinate(struct coordinate *a) {
	if(a->x > CHESS_SIZE-1 || a->x < 0 || a->y > CHESS_SIZE-1 || a->y <0)
		return FALSE;
	else {
		if(chess[a->x][a->y] == 1)
			return FALSE;
		else
		return TRUE;
	}
}

static unsigned int step = 1;

static int guess_direction(struct coordinate *a, struct coordinate *b) {
	int dx = b->x - a->x;
	int dy = b->y - a->y;
	if(dx > 0 && dy > 0) {
		if (dx < dy)
			return 0;
		else
			return 1;
	} else if(dx > 0 && dy < 0) {
		if (dx < abs(dy))
			return 3;
		else
			return 2;
	} else if(dx <0 && dy <0) {
		if (abs(dx) < abs(dy)) return 4;
		else return 5;
	} else {
		if (abs(dx) < abs(dy)) return 7;
		else return 6;
	}
}

static int try_direction(unsigned int dir) {
	switch(dir) {
	case 0:
		return 1;
	case 1:
		return 2;
	case 2:
		return 3;
	case 3:
		return 4;
	case 4:
		return 5;
	case 5:
		return 6;
	case 6:
		return 7;
	case 7:
		return 0;
	default:
		return 0;
	}
}

int guess_next(struct coordinate *now, struct coordinate *next, int dir) {
	switch(dir) {
	case 0:
		next->x = now->x + 1;
		next->y = now->y + 2;
		break;
	case 1:
		next->x = now->x + 2;
		next->y = now->y + 1;
		break;
	case 3:
		next->x = now->x + 2;
		next->y = now->y - 1;
		break;
	case 4:
		next->x = now->x + 1;
		next->y = now->y - 2;
		break;
	case 5:
		next->x = now->x - 1;
		next->y = now->y - 2;
		break;
	case 6:
		next->x = now->x - 2;
		next->y = now->y - 1;
		break;
	case 7:
		next->x = now->x - 2;
		next->y = now->y + 1;
		break;
	case 8:
		next->x = now->x - 1;
		next->y = now->y + 2;
		break;
	default:
		return FALSE;
	}

	if(TRUE == check_coordinate(next)) {
		chess[next->x][next->y] = step;
		step++;
		return TRUE;
	} else
		return FALSE;
}

void test_chess() {

	struct coordinate start = {0, 0};
	struct coordinate end= {6,6};
	struct coordinate next = {0, 0};
	int dir, i;
	clock_t s, e;

	if(FALSE == check_coordinate(&end) || FALSE == check_coordinate(&start)) {
		printf("\n无效的坐标\n\n");
		return;
	}

	s = clock();

	chess_show();
	debug_show("next", &next, dir);
	dir = guess_direction(&start, &end);

	for(i=0; i<105; i++) {
		if(TRUE == guess_next(&start, &next, dir)) {
			start.x = next.x;
			start.y = next.y;
			dir = guess_direction(&start, &end);
			debug_show("next", &next, dir);
		} else {
			dir = try_direction(dir);
		}


		if(next.x == end.x && next.y == end.y)
			break;
	}
	chess_show();
	e = clock();
	printf("共耗时:%f\n",(double)(e-s)/CLOCKS_PER_SEC);
}
