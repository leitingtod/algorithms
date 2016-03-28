/*
 * linux-list.h
 *
 *  Created on: 2016年3月25日
 *      Author: liu
 */

#ifndef DATA_STRUCTURE_SRC_LINUX_LIST_H_
#define DATA_STRUCTURE_SRC_LINUX_LIST_H_

struct list_head {
	struct list_head *prev, *next;
};

#define LIST_HEAD_INIT(name) { &(name), &(name)}
#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do {\
	(ptr)->next = (ptr);\
	(ptr)->prev = (ptr);\
} while(0)

static inline void __list_add(struct list_head *new,
                              struct list_head *prev,
                              struct list_head *next)
{
        next->prev = new;
        new->next = next;
        new->prev = prev;
        prev->next = new;
}

//加入一个新节点
static inline void list_add(struct list_head *new, struct list_head *head)
{
        __list_add(new, head, head->next);
}

//返回类型type的数据结构地址
#define list_entry(ptr, type, member) \
        ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

void test_linux_list();

#endif /* DATA_STRUCTURE_SRC_LINUX_LIST_H_ */
