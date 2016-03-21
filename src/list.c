/*
 * list.c
 *
 *  Created on: 2016年3月21日
 *      Author: liu
 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

LinkList * linklist_init(LinkList *head){
	head = (LinkList *)malloc(sizeof(LinkList));
	head->next = NULL;
	return head;
}

void linklist_iter(LinkList *head){
	LinkList *p = head;
	if(head == NULL) return;

	while(p->next != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
}

LinkListElem *linklist_search(LinkList *head, int val){
	LinkList *p = head;

	while(p->next != NULL) {
		if(p->data == val)
			break;
		p = p->next;
	}
	return p;
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

	if(head == NULL) return;

	e = (LinkList *)malloc(sizeof(LinkList));
	e->data = val;

	while(p->next != NULL) {
		if(pos == position)
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

