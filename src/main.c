#include <stdio.h>
#include <stdlib.h>
#include <list.h>

int main(int argc, char **argv) {
	LinkList *head;
	linklist_init(head);
	int i;
	for(i=0; i<4; i++) {
		linklist_append(head, i);
	}

	linklist_iter(head);
	return 0;
}
