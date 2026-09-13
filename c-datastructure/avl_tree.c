#include <stdlib.h>
#include <stdio.h>
#include "avl_tree.h"

avl_tree_node *avl_new_node(int data)
{
    avl_tree_node *node = malloc(sizeof(avl_tree_node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void avl_insert(avl_tree *avl, int data)
{
    printf("avl_insert:%d\n", data);
    avl_tree_node *node = avl_new_node(data);
    if (avl->root == NULL)
    {
        avl->root = node;
        return;
    }
    avl_tree_node *tmp_node = avl->root;
    avl_node_list *pre_nodes = malloc(sizeof(avl_node_list));
    pre_nodes->node = NULL;
    pre_nodes->nxt_node = NULL;
    while (tmp_node != NULL)
    {
        avl_node_list *pre_node = malloc(sizeof(avl_node_list));
        pre_node->node = tmp_node;
        pre_node->nxt_node = pre_nodes;
        pre_nodes = pre_node;
        // printf("avl add pre:%d\n", tmp_node->data);

        if (tmp_node->data < data)
        {
            if (tmp_node->right == NULL)
            {
                tmp_node->right = node;
                printf("tmp_node:%d>r=%d\n", tmp_node->data, node->data);
                break;
            }
            tmp_node = tmp_node->right;
        }
        else if (tmp_node->data > data)
        {
            if (tmp_node->left == NULL)
            {
                tmp_node->left = node;
                printf("tmp_node:%d>l=%d\n", tmp_node->data, node->data);
                break;
            }
            tmp_node = tmp_node->left;
        }
        else
        {
            printf("avl_insert fail, duplicate value\n");
            return;
        }
    }
    if (tmp_node == NULL)
    {
        printf("avl_insert fail,not find right place\n");
        return;
    }
    avl_tree_node *cur = NULL;
    avl_node_list *tmp_pre = pre_nodes;

    while (tmp_pre != NULL)
    {
        cur = tmp_pre->node;
        if (cur == NULL)
        {
            break;
        }

        tmp_pre = tmp_pre->nxt_node;
        avl_tree_node *pre = tmp_pre->node;

        int l_height = avl_node_height(cur->left);
        int r_height = avl_node_height(cur->right);
        printf("node:%d l_h:%d r_h:%d\n", cur->data, l_height, r_height);
        if (l_height - r_height > 1)
        {
            avl_tree_node *cur_left = cur->left;
            if (node->data < cur_left->data)
            {
                avl_rotate_right(avl, pre, cur);
            }
            else
            {
                avl_rotate_left(avl, cur, cur_left);
                avl_rotate_right(avl, pre, cur);
            }
        }
        else if (l_height - r_height < -1)
        {
            avl_tree_node *cur_right = cur->right;
            if (cur_right->data < node->data)
            {
                avl_rotate_left(avl, pre, cur);
            }
            else
            {
                avl_rotate_right(avl, cur, cur_right);
                avl_rotate_left(avl, pre, cur);
            }
        }
    }
}

void avl_visit_node(avl_tree_node *node)
{
    printf("data:%d\n", node->data);
}

void avl_in_order(avl_tree_node *node)
{
    if (node == NULL)
    {
        return;
    }
    avl_in_order(node->left);
    avl_visit_node(node);
    avl_in_order(node->right);
}

void avl_pre_order(avl_tree_node *node)
{
    if (node == NULL)
    {
        return;
    }
    avl_visit_node(node);
    avl_pre_order(node->left);
    avl_pre_order(node->right);
}

int avl_node_height(avl_tree_node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    int l_height = avl_node_height(node->left) + 1;
    int r_height = avl_node_height(node->right) + 1;
    return __max(l_height, r_height);
}

avl_tree_node *avl_pre_node(avl_tree_node *src, avl_tree_node *node)
{
    if (src == NULL || node == NULL)
    {
        return NULL;
    }
    if (src->left == node)
    {
        return src;
    }
    if (src->right == node)
    {
        return src;
    }
    if (node->data < src->data)
    {
        return avl_pre_node(src->left, node);
    }
    return avl_pre_node(src->right, node);
}

/**
       10
      /
     9
    /
   8
       9
      /  \
     8   10
    /
   7
  /
 5
       9
      /  \
     7   10
    / \
   5   8
   \
    6

       7
     /   \
    5     9
    \    /  \
     6  8   10
*/

void avl_rotate_right(avl_tree *avl, avl_tree_node *pre, avl_tree_node *node)
{
    printf("rr...\n");
    if (pre != NULL)
    {
        printf("pre:%d ", pre->data);
    }
    if (node != NULL)
    {
        printf("node:%d", node->data);
    }
    printf("\n");
    // pre 10 node 20
    avl_tree_node *left = node->left;     // 14
    avl_tree_node *l_right = left->right; // NULL
    left->right = node;                   // 14->r=20
    node->left = l_right;                 // 20->l=NULL
    if (pre == NULL)                      // 9
    {
        avl->root = left;
    }
    else if (pre->data > left->data)
    {
        pre->left = left; // 9->r=10
    }
    else if (pre->data < left->data)
    {
        pre->right = left;
    }
}

/*
      1
       \
        2
         \
          3
      2
     / \
    1   3
         \
          4
           \
            5
      2
     / \
    1   4
       / \
      3   5
         /
        6

       4
     /   \
    2      5
   / \    /
  1   3  6


*/
void avl_rotate_left(avl_tree *avl, avl_tree_node *pre, avl_tree_node *node)
{
    printf("rl...\n");
    if (pre != NULL)
    {
        printf("pre:%d ", pre->data);
    }
    if (node != NULL)
    {
        printf("node:%d", node->data);
    }
    printf("\n");
    // pre NULL node 9
    avl_tree_node *right = node->right;  // 10
    avl_tree_node *r_left = right->left; // NULL
    right->left = node;                  // 10->l=9
    node->right = r_left;                // 9->r=NULL
    if (pre == NULL)
    {
        avl->root = right; // 10
    }
    else if (pre->data > right->data)
    {
        pre->left = right;
    }
    else if (pre->data < right->data)
    {
        pre->right = right;
    }
}
/*
    10
    /
   8
    \
     9

     10
     /
    9
   /
  8

      9
     / \
    8  10
*/

/*
     2
      \
       3
      /
     1

    2
     \
      1
       \
        3

     1
    / \
   2   3
*/

/*

                         7
                    /       \
                  5          9
                /  \        /   \
               3   6       8      14
                                 /   \
                                10    20
                                 \
                                  13

*/