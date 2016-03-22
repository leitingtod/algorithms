/*
 * list.c
 *
 *  Created on: 2016年3月21日
 *      Author: liu
 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

LinkList * linklist_init(){
	LinkList *head = (LinkList *)malloc(sizeof(LinkList));
	head->next = NULL;
	return head;
}

void linklist_iter(LinkList *head){
	LinkList *p;
	int pos = 1;

	if(head == NULL) return;

	p = head->next;

	while(p != NULL) {
		printf("[%2d] %p: %d\n", pos, p, p->data);
		p = p->next;
		pos++;
	}
}

/*
 * 倒序打印列表元素，但不能更改列表
 * 除了递归，还有其他好办法吗？
 */
void linklist_iter_reverse(LinkList *head){
	LinkList *p;
	int pos = 1;

	if(head == NULL) return;

	p = head;

	if(p->next == NULL)
	{
		printf("[%2d] %p: %d\n", pos, p, p->data);
		return;
	} else {
		linklist_iter_reverse(p->next);
		printf("[%2d] %p: %d\n", pos, p, p->data);
	}
}

void linklist_check_loop(LinkList *head) {

}

LinkListElem *linklist_find(LinkList *head, int val){
	LinkList *p = head;

	while(p->next != NULL) {
		if(p->data == val)
			break;
		p = p->next;
	}
	printf("[find] %p: %d\n", p, p->data);
	return p;
}

LinkListElem *linklist_get(LinkList *head, int position) {
	LinkList *p = head, *get;
	int pos = 0;

	if(head == NULL || position < 1) return NULL;

	while(p->next != NULL) {
		if(pos == position-1)
			break;
		p = p->next;
		pos++;
	}
	get = p->next;
	printf("[get] %p: %d\n", get, get->data);
	return get;
}

void linklist_append(LinkList *head, int val){
	LinkList *p = head, *e;

	if(head == NULL) return;

	e = (LinkList *)malloc(sizeof(LinkList));
	e->data = val;

	while(p->next != NULL) {
		p = p->next;
	}

	p->next = e;
	e->next = NULL;
}

void linklist_remove(LinkList *head, int val){
	LinkList *p = head, *del;

	while(p->next != NULL) {
		if(p->next->data == val)
			break;
		p = p->next;
	}
	del = p->next;
	p->next = del->next;
	free(del);
}

void linklist_insert(LinkList *head, int val, int position){
	LinkList *p = head, *e;
	int pos = 0;

	if(head == NULL || position < 1) return;

	e = (LinkList *)malloc(sizeof(LinkList));
	e->data = val;

	while(p != NULL) {
		if(pos == position-1)
			break;
		p = p->next;
		pos++;
	}
	e->next = p->next;
	p->next = e;
}

void linklist_delete(LinkList *head, int position){
	LinkList *p = head, *del;
	int pos = 0;

	if(head == NULL || position < 1) return;

	// 注意与linklist_insert的不同
	while(p->next != NULL) {
		if(pos == position-1)
			break;
		p = p->next;
		pos++;
	}
	del = p->next;
	p->next = del->next;
	free(del);
}

/*
 * example: LinkList a = 1 2 3 4 5
 * excute: linklist_swap_2by2(a)
 * output: 2 1 4 3 5
 */
void linklist_swap_2by2(LinkList *head) {
	LinkList *a, *b, *p;

	if(head == NULL) return;

	p = head;
	a = head->next;

	while(a != NULL) {
		b = a->next;
		if(b != NULL) {
			// swap
			a->next = b->next;
			b->next = a;
			p->next = b;
			p = a;
			if(a->next != NULL) {
				a = a->next;
				continue;
			} else {
				break;
			}
		} else {
			break;
		}
	}
}


