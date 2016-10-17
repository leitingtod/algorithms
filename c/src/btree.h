//
// Created by lWX351071 on 2016/10/13.
//

#ifndef DATA_STRUCTURE_TREE_H
#define DATA_STRUCTURE_TREE_H
enum {
    LEFT,
    RIGHT
};

struct btree_node {
    int key;
    struct btree_node *parent;
    struct btree_node *left;
    struct btree_node *right;
};

static inline void init_btree_node(struct btree_node *root, int key) {
    root->parent = NULL;
    root->left = NULL;
    root->right = NULL;
    root->key = key;
}

static inline void btree_insert(struct btree_node *new, struct btree_node *node, int type) {
    if (new != NULL && node != NULL) {
        new->parent = node;
        if (type == LEFT)
            node->left = new;
        else {
            node->right = new;
        }
    }
}

static inline void btree_cmp_insert(struct btree_node *new, struct btree_node *node) {
    while (node != NULL && node->key != new->key) {
        if (new->key < node->key) {
            if (node->left != NULL)
                node = node->left;
            else
                break;
        } else {
            if (node->right != NULL)
                node = node->right;
            else
                break;
        }
    }

    if (new->key < node->key) {
        node->left = new;
        new->parent = node;
    } else if (new->key > node->key) {
        node->right = new;
        new->parent = node;
    }
}
//#define PRINT_CHAR
static inline void btree_print_node(int key) {
#ifndef PRINT_CHAR
    printf("%d ", key);
#else
    printf("%c ", key);
#endif
}


static inline void btree_for_each(struct btree_node *node) {
    if (node != NULL) {
        btree_print_node(node->key);
        btree_for_each(node->left);
        btree_for_each(node->right);
    }
}

static inline void btree_for_each_mid(struct btree_node *node) {
    if (node != NULL) {
        btree_for_each_mid(node->left);
        btree_print_node(node->key);
        btree_for_each_mid(node->right);
    }
}

static inline void btree_for_each_post(struct btree_node *node) {
    if (node != NULL) {
        btree_for_each_post(node->left);
        btree_for_each_post(node->right);
        btree_print_node(node->key);
    }
}

//static inline void btree_delete(struct btree_node *node, int key) {
//    struct btree_node *del;
//
//    del = btree_search(node, key);
//
//    if (del != NULL) {
//        if (del->key < del->parent->key) {
//            if (del->left == NULL && del->right == NULL) {
//                del->parent->left = NULL;
//            } else if (del->left != NULL && del->right != NULL) {
//
//            } else {
//                if (del->left != NULL)
//                    del->parent->left = del->left;
//                else
//                    del->parent->left = del->right;
//            }
//        } else {
//            if (del->left == NULL && del->right == NULL) {
//                del->parent->right = NULL;
//            } else if (del->left != NULL && del->right != NULL) {
//
//            } else {
//                if (del->left != NULL)
//                    del->parent->right = del->left;
//                else
//                    del->parent->right = del->right;
//            }
//        }
//    }
//}

static inline struct btree_node *btree_search(struct btree_node *node, int key) {
    while (node != NULL && node->key != key) {
        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}

static inline struct btree_node *btree_minimum(struct btree_node *node) {
    while (node != NULL && node->left != NULL) {
        node = node->left;
    }
    return node;
}

static inline struct btree_node *btree_maximum(struct btree_node *node) {
    while (node != NULL && node->right != NULL) {
        node = node->right;
    }
    return node;
}

//static inline struct btree_node * btree_successor(struct btree_node *node) {
//    struct btree_node *p;
//    if (node != NULL) {
//        if (node->right != NULL)
//            return btree_minimum(node->right);
//        else {
//            p = node->parent;
//            while (p != NULL && p->left != NULL) {
//
//            }
//        }
//    }
//    return node;
//}



#endif //DATA_STRUCTURE_TREE_H
