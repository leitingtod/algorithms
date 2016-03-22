#include <stdio.h>
#include <stdlib.h>
#include "list.h"

static char *seperator ="--------------------------";

void test_linklist(int len) {
	LinkList *head;
	int i;

	printf("%s init\n", seperator);
	head = linklist_init();

	for(i=0; i<len; i++) {
		linklist_append(head, i);
	}

	linklist_iter(head);

	printf("%s find elem's val == 2\n", seperator);
	linklist_find(head, 2);

	printf("%s get elem's pos == 2\n", seperator);
	linklist_get(head, 2);

	printf("%s remove elem's val == 1\n", seperator);
	linklist_remove(head, 1);
	linklist_iter(head);

	printf("%s insert elem's val=8 in pos 2\n", seperator);
	linklist_insert(head, 8, 2);
	linklist_iter(head);

	printf("%s insert elem's val=98 in pos 1\n", seperator);
	linklist_insert(head, 98, 1);
	linklist_iter(head);


	printf("%s delete elem in pos 2\n", seperator);
	linklist_delete(head, 2);
	linklist_iter(head);

	printf("%s insert elem's val=99 in pos 1\n", seperator);
	linklist_insert(head, 99, 1);
	linklist_iter(head);

	printf("%s swap elem 2 by 2\n", seperator);
	linklist_swap_2by2(head);
	linklist_iter(head);

	printf("%s reverse iter link list\n", seperator);
	linklist_iter_reverse(head);
}

int main(int argc, char **argv) {
	test_linklist(8);
	return 0;
}
