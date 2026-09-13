
typedef struct _b_tree_node
{
    int data;
    struct _b_tree_node *l_child;
    struct _b_tree_node *r_child;
} b_tree_node;

b_tree_node *create_node(int data);

void set_l_child(b_tree_node *p, b_tree_node *c);

void set_r_child(b_tree_node *p, b_tree_node *c);

void visit(b_tree_node *node);

void in_order(b_tree_node *node);

void pre_order(b_tree_node *node);

void post_order(b_tree_node *node);