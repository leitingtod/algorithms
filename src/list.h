/*
 * list.h
 *
 *  Created on: 2016年3月21日
 *      Author: liu
 */

#ifndef DATA_STRUCTURE_SRC_LIST_H_
#define DATA_STRUCTURE_SRC_LIST_H_

struct node {
	int data;
	struct node *next;
};

typedef struct node LinkList;
typedef struct node LinkListElem;

LinkList * linklist_init();
void linklist_iter(LinkList *head);
void linklist_iter_reverse(LinkList *head);
void linklist_check_loop(LinkList *head);
LinkListElem * linklist_find(LinkList *head, int val);
LinkListElem * linklist_get(LinkList *head, int position);

void linklist_append(LinkList *head, int val);
void linklist_remove(LinkList *head, int val);
void linklist_insert(LinkList *head, int val, int position);
void linklist_delete(LinkList *head, int position);

#define SEPERATOR "--------------------------"
void test_linklist(int len);

#endif /* DATA_STRUCTURE_SRC_LIST_H_ */
