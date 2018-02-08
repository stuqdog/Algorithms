#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXNUM 20

typedef struct Cell {
    struct Cell *left;
    struct Cell *right;
    struct Cell *parent;
    int val;
    int occurrences;
    int gamma;
    int height;
} Cell;

typedef struct pair {
    bool first;
    struct Cell *second;
} pair;

struct Cell *root;

void add_cell(struct Cell *parent, struct Cell *new); // Adds cells to tree.
void rebalance(struct Cell *cell); // Rebalances tree if it gets uneven.
void update_height(struct Cell *cell); //Updates cell's height after insertions/rotations.
void update_gamma(struct Cell *cell); //Updates cell's gamma after insertions/rotations.
void rotate_left(struct Cell *cell); //Rotates cells, part of rebalancing.
void rotate_right(struct Cell *cell); //Rotates cells, part of rebalancing.
int height(struct Cell *cell); //Returns a cell's height, or -1 if no cell.
int gamma(struct Cell *cell); //Returns a cell's gamma, or 0 if no cell.
void delete(int key, struct Cell *cell); //Searches tree for key, deletes it (1x) if found.
//void delete(int key); //Searches tree for key, deletes it (1x) if found.
struct Cell *next_smaller(struct Cell *cell); //returns next smaller cell from input.
void print(); //prints the tree. Needs refactoring.
int find_largest(struct Cell *cell); //Finds largest value in tree.
int find_smallest(struct Cell *cell); //Finds smallest value in tree.
char * get_instr(char *instr, int limit);
void search(int num, struct Cell *cell);
int number_of_nodes(struct Cell *cell);

int main(void) {

    root = (struct Cell*) malloc(sizeof(struct Cell));
    root->val = 10;
    root->occurrences = 1;
    root->gamma = 1;
    root->height = 0;
    root->parent = root->left = root->right = NULL;

    srand(time(NULL));
    for (int i = 0; i < 100000; ++i) {
        int r = rand() % 1000000;

        struct Cell *new;
        new = (struct Cell*) malloc(sizeof(struct Cell));
        new->val = r;
        new->occurrences = 1;
        new->gamma = 1;
        new->height = 0;
        new->parent = new->left = new->right = NULL;

        add_cell(root, new);
    }


    char instr[MAXNUM];
    char *num;
    printf("What would you like to do? (I)nsert number, (D)elete number, ");
    printf("(P)rint tree, Find (L)owest,\nFind (H)ighest, Show (R)oot, ");
    printf("Show (N)umber of unique nodes, (S)earch for a particular number,\n");
    printf("or (Q)uit?\n");
    while (*get_instr(instr, MAXNUM) != EOF) {

        switch ((int) instr[0]) {
            case 'n':
            case 'N':
                printf("Total nodes: %d\n---\n", number_of_nodes(root));
                break;
            case 'i':
            case 'I':
                num = get_instr(instr, MAXNUM);
                if(!isdigit(num[0])) {
                    printf("Inserted valued must be numbers.\n---\n");
                } else {
                    int i = atoi(num);
                    struct Cell *new;
                    new = (struct Cell*) malloc(sizeof(struct Cell));
                    add_cell(root, new);
                }
                break;
            case 'p':
            case 'P':
                print();
                break;
            case 'l':
            case 'L':
                printf("Smallest: %d\n", find_smallest(root));
                break;
            case 'h':
            case 'H':
                printf("Largest: %d\n", find_largest(root));
                break;
            case 'r':
            case 'R':
                printf("Root: %d\n", root->val);
                break;
            case 'd':
            case 'D':
                num = get_instr(instr, MAXNUM);
                if(!isdigit(num[0])) {
                    printf("Values must be numbers.\n---\n");
                } else {
                    int i = atoi(num);
                    delete(i, root);
                }
                break;
            case 's':
            case 'S':
                num = get_instr(instr, MAXNUM);
                if (isdigit(num[0])) {
                    int i = atoi(num);
                    search(i, root);
                } else {
                    printf("Search values must be numbers.\n---\n");
                }
                break;
            case 'q':
            case 'Q':
                return 0;
            default:
                printf("Please give a valid instruction.\n---\n");
                break;

        }
        printf("What would you like to do? (I)nsert number, (D)elete number, ");
        printf("(P)rint tree, Find (L)owest,\nFind (H)ighest, Show (R)oot, ");
        printf("Show (N)umber of unique nodes, (S)earch for a particular number,\n");
        printf("or (Q)uit?\n");
    }

    // }
//    print();
    return 0;
}

char * get_instr(char *instr, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *i = instr;

    while (isspace(c = getch())) { ; }
    if (c != EOF) {
        *i++ = c;
    }
    if (isalpha(c)) { // If first char is alpha, read that as instr; ignore the rest
        *i = '\0';
        return instr;
    }
    for (; --lim > 0; i++) {
        if (!isalnum(*i = getch())) {
            ungetch(*i);
            break;
        }
    }
    *i = '\0';
    return instr;
}

#define BUFSIZE 20
char buf[BUFSIZE];
int bufp = 0;

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("Ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

int number_of_nodes(struct Cell *cell) {
    if (!cell) {
        return 0;
    } else if (!cell->left && !cell->right) {
        return 1;
    } else {
        return number_of_nodes(cell->left) + number_of_nodes(cell->right);
    }
}

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

// void delete(int key) {
void delete(int key, struct Cell *node) {
    while (node && node->val != key) {
        node = (node->val > key) ? node->left : node->right;
    }
    if (!node) {
        printf("Value was not in tree.\n");
        return;
    }
    // struct Cell* node = search(key, root);
    // if (!node) {
    //     return;
    // }
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

void print() {

    struct pair initial;
    initial.first = true;
    initial.second = root;
    struct pair *curr;
    curr = (struct pair[1]){initial};
    int row_length = 1;
    bool flag = true;

    while (flag) {
        flag = false;
        struct pair *new_array = malloc(row_length * 2 * sizeof(struct pair));

        for (int i = 0, j = 0; i < row_length; ++i) {
            if (curr[i].first == true) {
                new_array[j++] = (curr[i].second->left) ?
                    (struct pair){true, curr[i].second->left} :
                    (struct pair){false, curr[i].second};
                new_array[j++] = (curr[i].second->right) ?
                    (struct pair){true, curr[i].second->right} :
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
                    printf("%d, ", curr[i].second->val);
                } else {
                    printf("NaN, ");
                }
            }
        }
        printf("\n");
        curr = new_array;
        row_length *= 2;
    }
    return;
}
