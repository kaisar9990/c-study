#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct avl_tree_node
{
    int data;
    struct avl_tree_node *left;
    struct avl_tree_node *right;
} avl_tree_node;

typedef struct avl_tree
{
    avl_tree_node *root;
} avl_tree;

typedef struct avl_node_list
{
    avl_tree_node *node;
    struct avl_node_list *nxt_node;
} avl_node_list;

avl_tree_node *avl_new_node(int data);
void avl_insert(avl_tree *avl, int data);
void avl_insert_node(avl_tree *avl, avl_tree_node *src, avl_tree_node *node);
void avl_visit_node(avl_tree_node *node);
void avl_in_order(avl_tree_node *node);
void avl_pre_order(avl_tree_node *node);
int avl_node_height(avl_tree_node *node);
avl_tree_node *avl_pre_node(avl_tree_node *src, avl_tree_node *node);
void avl_rotate_right(avl_tree *avl, avl_tree_node *pre, avl_tree_node *node);
void avl_rotate_left(avl_tree *avl, avl_tree_node *pre, avl_tree_node *node);
#endif