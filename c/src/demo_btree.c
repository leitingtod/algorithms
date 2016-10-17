//
// Created by lWX351071 on 2016/10/13.
//
#include <stdlib.h>
#include <stdio.h>
#include "btree.h"

extern void demo_btree_main();
static void demo_btree_walk();

void demo_btree_main() {
//    demo_btree_walk();
//    return;
    struct btree_node root;
    struct btree_node *p;
    int i;
    int node[] = {1, 7, 2, 4, 12, 8, 20, 9};
    init_btree_node(&root, 5);

    for (i=0; i<sizeof(node)/ sizeof(int); i++) {
        p = (struct btree_node *)malloc(sizeof(struct btree_node));
        init_btree_node(p, node[i]);
        btree_cmp_insert(p, &root);
    }

    btree_for_each(&root);
    printf("\n");
    btree_for_each_mid(&root);
    printf("\n");
    btree_for_each_post(&root);
    printf("\n");

    int sk = 6;
    p = btree_search(&root, sk);
    if (p != NULL)
        printf("%d\n", p->key);
    else
        printf("%d: Not Found\n", sk);

    p = btree_minimum(&root);
    printf("%d\n", p->key);

    p = btree_maximum(&root);
    printf("%d\n", p->key);

}

static void demo_btree_walk() {
    struct btree_node root;
    struct btree_node *q[20];
    int i;
    int node[] = {'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    init_btree_node(&root, 'A');

    for (i=0; i<sizeof(node)/ sizeof(int); i++) {
        q[i] = (struct btree_node *)malloc(sizeof(struct btree_node));
        init_btree_node(q[i], node[i]);
    }

    btree_insert(q[0], &root, LEFT);
    btree_insert(q[1], &root, RIGHT);
    btree_insert(q[2], q[0], LEFT);
    btree_insert(q[3], q[1], LEFT);
    btree_insert(q[4], q[1], RIGHT);
    btree_insert(q[5], q[2], LEFT);
    btree_insert(q[6], q[2], RIGHT);
    btree_insert(q[7], q[3], RIGHT);

    btree_for_each(&root);
    printf("\n");
    btree_for_each_mid(&root);
    printf("\n");
    btree_for_each_post(&root);
    printf("\n");
}
