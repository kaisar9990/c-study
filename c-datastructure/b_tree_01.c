#ifndef B_TREE_01_H
#define B_TREE_01_H

#include <stdlib.h>
#include <stdio.h>
#include "b_tree_01.h"

b_tree_node *create_node(int data)
{
    b_tree_node *node = malloc(sizeof(b_tree_node));
    node->data = data;
    node->l_child = NULL;
    node->r_child = NULL;
    return node;
}

void set_l_child(b_tree_node *p, b_tree_node *c)
{
    p->l_child = c;
}

void set_r_child(b_tree_node *p, b_tree_node *c)
{
    p->r_child = c;
}

void visit(b_tree_node *node)
{
    printf("data:%d\n", node->data);
}

void in_order(b_tree_node *node)
{
    if (node == NULL)
    {
        return;
    }
    in_order(node->l_child);
    visit(node);
    in_order(node->r_child);
}

void pre_order(b_tree_node *node)
{
    if (node == NULL)
    {
        return;
    }
    visit(node);
    pre_order(node->l_child);
    pre_order(node->r_child);
}

void post_order(b_tree_node *node)
{
    if (node == NULL)
    {
        return;
    }
    post_order(node->l_child);
    post_order(node->r_child);
    visit(node);
}

#endif