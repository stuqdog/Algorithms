#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
extern struct Cell* root;

void add_cell(struct Cell *parent, struct Cell *new) {
    /* Given a new cell (new), we go down the tree from the root until we find
    a place to put it, and then we insert it. */
    while (!new->parent) {
        if (new->val == parent->val) {
            ++parent->occurrences;
            return;
        }
        else if (new->val < parent->val) {
            if (parent->left) {
                parent = parent->left;
            } else {
                parent->left = new;
                new->parent = parent;
            }
        }
        else {
            if (parent->right) {
                parent = parent->right;
            } else {
                parent->right = new;
                new->parent = parent;
            }
        }
    }
    rebalance(new);
    return;
}

void rebalance(struct Cell *cell) {
    while (cell) {
        update_height(cell);
        update_gamma(cell);
        if (height(cell->left) - height(cell->right) >= 2) {
            if (height(cell->left->right) > height(cell->left->left)) {
                rotate_left(cell->left);
            }
            rotate_right(cell);
        } else if (height(cell->right) - height(cell->left) >= 2) {
            if (height(cell->right->left) > height(cell->right->right)) {
                rotate_right(cell->right);
            }
            rotate_left(cell);
        }
        if (cell->parent == NULL) {
            root = cell;
        }
        cell = cell->parent;
    }
    return;
}

void update_height(struct Cell *cell) {
    if (!cell) { return; }
    int l = height(cell->left) + 1;
    int r = height(cell->right) + 1;
    cell->height = (l > r) ? l : r;
    return;
}

void update_gamma(struct Cell *cell) {
    if (!cell) { return; }
    cell->gamma = gamma(cell->left) + gamma(cell->right) + 1;
    return;
}

int height(struct Cell *cell) {
    if (!cell) { return -1; }
    return cell->height;
}

void delete(int key, struct Cell *node) {
    while (node && node->val != key) {
        node = (node->val > key) ? node->left : node->right;
    }
    if (!node) {
        printf("Value was not in tree.\n");
        return;
    }

    if (node->occurrences > 1) {
        --node->occurrences;
        printf("Single value deleted. Remaining occurences: %d\n", node->occurrences);
        return;
    }
    printf("Node deleted.\n");
    if (!node->left && !node->right) { //We're a leaf, so we're done!
        if (node->val > node->parent->val) {
            node->parent->right = NULL;
        } else {
            node->parent->left = NULL;
        }
        rebalance(node->parent);
    } else if (node->right && !node->left) {
        // node->right must be a leaf, so it just replaces node.
        node->right->parent = node->parent;
        if (node->val > node->parent->val) {
            node->parent->right = node->right;
        } else {
            node->parent->left = node->right;
        }
        rebalance(node->parent);
    } else if (node->left && !node->right) {
        node->left->parent = node->parent;
        if (node->val > node->parent->val) {
            node->parent->right = node->left;
        } else {
            node->parent->left = node->right;
        }
        rebalance(node->parent);
    } else {
        struct Cell *new_node = next_smaller(node);
        if (new_node->parent != node) {
            if (new_node->left) {
                new_node->left->parent = new_node->parent;
            }
            new_node->parent->right = new_node->left;
            node->left->parent = new_node;
            node->right->parent = new_node;
            new_node->left = node->left;
            new_node->right = node->right;
            new_node->parent = node->parent;
            if (node->parent) {
                if (node->val > node->parent->val) {
                    node->parent->right = new_node;
                } else {
                    node->parent->left = new_node;
                }
            }
        } else {
            new_node->parent = node->parent;
            new_node->right = node->right;
            if (node->right) {
                node->right->parent = new_node;
            }
            if ((node->parent) && node->val > node->parent->val) {
                node->parent->right = new_node;
            } else if ((node->parent) && node->val < node->parent->val) {
                node->parent->left = new_node;
            }
        }
        rebalance(new_node);
    }
    free(node);
}

void rotate_left(struct Cell *cell) {
    cell->right->parent = cell->parent;
    if (cell->parent) {
        if (cell->val < cell->parent->val) {
            cell->parent->left = cell->right;
        } else {
            cell->parent->right = cell->right;
        }
    }
    cell->parent = cell->right;
    cell->right = cell->right->left;
    if (cell->right) {
        cell->right->parent = cell;
    }
    cell->parent->left = cell;
    update_gamma(cell);
    update_height(cell);
    return;
}

void rotate_right(struct Cell *cell) {
    cell->left->parent = cell->parent;
    if (cell->parent) {
        if (cell->val < cell->parent->val) {
            cell->parent->left = cell->left;
        } else {
            cell->parent->right = cell->left;
        }
    }
    cell->parent = cell->left;
    cell->left = cell->left->right;
    if (cell->left) {
        cell->left->parent = cell;
    }
    cell->parent->right = cell;
    update_gamma(cell);
    update_height(cell);
    return;
}
