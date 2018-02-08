#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
extern struct Cell* root;

typedef struct pair {
    bool first;
    struct Cell *second;
} pair;

void print() {

    struct pair initial;
    initial.first = true;
    initial.second = root;
    struct pair *curr;
    curr = (struct pair[1]){initial};
    int row_length = 1;
    bool flag = true;
    bool should_print = false;

    while (flag) {
        flag = false;
        should_print = false;
        struct pair *new_array = malloc(row_length * 2 * sizeof(struct pair));

        for (int i = 0, j = 0; i < row_length; ++i) {
            if (curr[i].first == true) {
                new_array[j++] = (curr[i].second->left) ?
                    (should_print = true), (struct pair){true, curr[i].second->left} :
                    (struct pair){false, curr[i].second};
                new_array[j++] = (curr[i].second->right) ?
                    (should_print = true), (struct pair){true, curr[i].second->right} :
                    (struct pair){false, curr[i].second};
                flag = true;
            } else {
                new_array[j++] = (struct pair){false, NULL};
                new_array[j++] = (struct pair){false, NULL};
            }
        }
        if (flag == true) {
            for (int i = 0; i < row_length; ++i) {
                if (curr[i].first == true) {
                    printf(i < row_length - 1 ?
                           "%d, " : "%d", curr[i].second->val);
                } else {
                    printf((i < row_length - 1) ?
                           "NaN, " : "NAN");
                }
            }
        }
        printf("\n");
        if (should_print == false) {
            return;
        }
        curr = new_array;
        row_length *= 2;
    }
    return;
}
