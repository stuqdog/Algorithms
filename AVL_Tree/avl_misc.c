#include "avl.h"
#include <stdio.h>

int number_of_nodes(struct Cell *cell) {
    if (!cell) {
        return 0;
    } else if (!cell->left && !cell->right) {
        return 1;
    } else {
        return number_of_nodes(cell->left) + number_of_nodes(cell->right) + 1;
    }
}

int find_largest(struct Cell *cell) {
    while (cell->right) {
        cell = cell->right;
    }
    return cell->val;
}

int find_smallest(struct Cell *cell) {
    while (cell->left) {
        cell = cell->left;
    }
    return cell->val;
}


int gamma(struct Cell *cell) {
    if (!cell) { return 0; }
    return cell->gamma;
}

struct Cell *next_smaller(struct Cell *cell) {
        cell = cell->left;
        while (cell->right) {
            cell = cell->right;
        }
    return cell;
}

void search(int num, struct Cell *node) {
    while (node && node->val != num) {
        node = (node->val > num) ? node->left : node->right;
    }
    if (!node) {
        printf("%d is not in the tree.\n", num);
    } else {
        printf("%d occurs in the tree %d times.\n", num, node->occurrences);
    }
    return;
}
