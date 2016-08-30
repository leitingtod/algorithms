/*
 * linux-list.c
 *
 *  Created on: 2016年3月25日
 *      Author: liu
 */
#include <stdio.h>
#include <stdlib.h>
#include "linux-list.h"

struct path {
	struct list_head list;
	int x;
	int y;
};

void list_print(struct list_head *pos, struct path *path_head) {
	struct path *p;
	// 下面把这个链表中各个节点的值打印出来
	printf("\n");
	printf("=========== print the list ===============\n");
	list_for_each(pos, &(path_head->list))
	{
		// 这里我们用list_entry来取得pos所在的结构的指针
		p = list_entry(pos, struct path, list);
		printf("axis: %d, %d \n", p->x, p->y);
	}
	printf("\n");

}

void test_linux_list() {
	struct path *p;
	struct list_head *pos, *n;
	int x, y, i;

	struct path path_head;
	INIT_LIST_HEAD(&path_head.list);

	for (i = 0; i < 10; i++) {
		p = (struct path *) malloc(sizeof(struct path));
		p->x = i;
		p->y = i + 1;
//		list_add(&(p->list), &(path_head.list));
		list_add_tail(&(p->list), &(path_head.list));
	}

	list_print(pos, &path_head);

	printf("========== print list after delete a node which age is 20 "
			"==========\n");
	list_for_each_safe(pos, n, &path_head.list)
	{

		p = list_entry(pos, struct path, list);
		if (p->x == 4) {
			list_del_init(pos);
			free(p);
		}
	}
	list_print(pos, &path_head);

    // 释放资源
    list_for_each_safe(pos, n, &path_head.list)
    {
           p = list_entry(pos, struct path, list);
           list_del_init(pos);
           free(p);
    }
    list_print(pos, &path_head);
}

