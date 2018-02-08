#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "avl.h"

#define MAXNUM 10
#define MAXNODESIZE 1000000
#define INITIALNODES 100000

struct Cell *root;

int main(void) {

    srand(time(NULL));

    root = (struct Cell*) malloc(sizeof(struct Cell));
    root->val = rand() % MAXNUM;
    root->occurrences = 1;
    root->gamma = 1;
    root->height = 0;
    root->parent = root->left = root->right = NULL;

    for (int i = 0; i < INITIALNODES; ++i) {
        int r = rand() % MAXNODESIZE;

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
                    new->val = i;
                    new->occurrences = 1;
                    new->gamma = 1;
                    new->height = 0;
                    new->left = new->right = new->parent = NULL;
                    add_cell(root, new);
                }
                printf("Cell inserted.\n---\n");
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
    return 0;
}
