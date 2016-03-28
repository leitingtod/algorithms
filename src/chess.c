/*
 * chess.c
 *
 *  Created on: 2016年3月24日
 *      Author: liu
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "chess.h"
#include "linux-list.h"
/*
 * 马踏棋盘（国际象棋）——骑士环游问题，与八皇后问题类似。
 * 环游问题的解决，也就解决的了任意两点之间路径解决。
 */
struct coordinate {
	unsigned int x;
	unsigned int y;
};

struct chess_history {
	struct list_head list;
	struct coordinate coor;
};

#define CHESS_SIZE 8
#define TRUE 1
#define FALSE 0

static unsigned int chess[CHESS_SIZE][CHESS_SIZE] = { 0 };

void chess_show() {
	int i, j;
	for (i = CHESS_SIZE - 1; i >= 0; i--) {
		printf("%2u |", i);
		for (j = 0; j < CHESS_SIZE; j++) {
			//printf("%u, %u] %u\t", i, j, chess[i][j]);
			printf("%4u ", chess[i][j]);
//			if(j == CHESS_SIZE-1)
//				printf("| %2u\n", i);
		}
		puts("");
		printf("   |\n");
	}

	for (i = 0; i < CHESS_SIZE; i++) {
		printf("-----");
	}
	printf("\n x |");
	for (i = 0; i < CHESS_SIZE; i++) {
		printf("%4u ", i);
	}
	puts("");
}

void debug_show(const char *label, struct coordinate *p, int dir) {
	printf("%s: %u %u, dir: %u\n", label, p->x, p->y, dir);
}

int is_valid(struct coordinate *a) {
	if (a->x > CHESS_SIZE - 1 || a->x < 0 || a->y > CHESS_SIZE - 1 || a->y < 0)
		return FALSE;
	else {
		if (chess[a->x][a->y] != 0)
			return FALSE;
		else
			return TRUE;
	}
}

int get_direction(struct coordinate *start, struct coordinate *end) {
	int dx = end->x - start->x;
	int dy = end->y - start->y;
	if (dx > 0 && dy > 0) {
		if (dx < dy)
			return 0;
		else
			return 1;
	} else if (dx > 0 && dy < 0) {
		if (dx < abs(dy))
			return 3;
		else
			return 2;
	} else if (dx < 0 && dy < 0) {
		if (abs(dx) < abs(dy))
			return 4;
		else
			return 5;
	} else {
		if (abs(dx) < abs(dy))
			return 7;
		else
			return 6;
	}
}

static int step = 1;
static int check_flag = FALSE;
static clock_t s, e;

int get_next(struct coordinate *now, struct coordinate *next, int dir) {
	switch (dir) {
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

	if (TRUE == is_valid(next)) {
		if (chess[next->x][next->y] != 0)
			return FALSE;
		else {
			if (FALSE == check_flag) {
				chess[next->x][next->y] = step;
				step++;
			}
			return TRUE;
		}
	} else
		return FALSE;
}

int check_next(struct coordinate *now, struct coordinate *next) {
	int i;
	check_flag = TRUE;
	for (i = 0; i < 8; i++) {
		if (TRUE == get_next(now, next, i)) {
			break;
		}
	}
	check_flag = FALSE;
	if (i >= 8)
		return FALSE;
	return TRUE;
}

int try_direction(unsigned int dir) {
	int tmp = dir + 1;
	if (tmp > 7)
		return 0;
	else
		return tmp;
}

void INThandler(int sig) {
	char c;

	signal(sig, SIG_IGN);
//	printf("OUCH, did you hit Ctrl-C?\n"
//			"Do you really want to quit? [y/n]\n");
	printf("\n");
	chess_show();
	e = clock();
	printf("步数:%d, 共耗时:%f\n", step, (double) (e - s) / CLOCKS_PER_SEC);
	exit(0);
//     c = getchar();
//     if (c == 'y' || c == 'Y')
//          exit(0);
//     else
//          signal(SIGINT, INThandler);
}

static int tmp_step = 0;
void test_chess() {
	struct coordinate start = { 0, 0 };
	//struct coordinate end= {6,6};
	struct coordinate end = { 7, 7 };
	struct coordinate next = { 0, 0 };
	struct coordinate tmp_next = { 0, 0 }, tmp_start = { 0, 0 };
	int dir, i;

	signal(SIGINT, INThandler);

	if (FALSE == is_valid(&end) || FALSE == is_valid(&start)) {
		printf("\n无效的坐标\n\n");
		return;
	}

	s = clock();

	chess_show();
	dir = 0;
//	debug_show("next", &next, dir);

	for (i = 0;; i++) {
		if (TRUE == get_next(&start, &next, dir)) {
			tmp_start.x = next.x;
			tmp_start.y = next.y;
			if (TRUE == check_next(&tmp_start, &tmp_next)) {
				start.x = next.x;
				start.y = next.y;
//				debug_show("next", &next, dir);
				continue;
			} else {
				//回溯，选择下一个有效的点
				dir = try_direction(dir);
			}
		} else {
			//选择下一个有效的点
			dir = try_direction(dir);
		}
		printf(".");
//		if(next.x == end.x && next.y == end.y)
//			break;
	}
	printf("\n");
	chess_show();
	e = clock();
	printf("步数:%d, 共耗时:%f\n", step, (double) (e - s) / CLOCKS_PER_SEC);
}
