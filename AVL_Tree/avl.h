#ifndef avl
#define avl


typedef struct Cell {
    struct Cell *left;
    struct Cell *right;
    struct Cell *parent;
    int val;
    int occurrences;
    int gamma;
    int height;
} Cell;

void add_cell(struct Cell *parent, struct Cell *cell); // Adds cells to tree.
void rebalance(struct Cell *cell); // Rebalances tree if it gets uneven.
void update_height(struct Cell *cell); //Updates cell's height after insertions/rotations.
void update_gamma(struct Cell *cell); //Updates cell's gamma after insertions/rotations.
void rotate_left(struct Cell *cell); //Rotates cells, part of rebalancing.
void rotate_right(struct Cell *cell); //Rotates cells, part of rebalancing.
int height(struct Cell *cell); //Returns a cell's height, or -1 if no cell.
int gamma(struct Cell *cell); //Returns a cell's gamma, or 0 if no cell.
void delete(int key, struct Cell *cell); //Searches tree for key, deletes it (1x) if found.
struct Cell *next_smaller(struct Cell *cell); //returns next smaller cell from input.
void print(); //prints the tree. Needs refactoring.
int find_largest(struct Cell *cell); //Finds largest value in tree.
int find_smallest(struct Cell *cell); //Finds smallest value in tree.
char* get_instr(char *instr, int limit); //Reads user instructions.
void search(int num, struct Cell *cell); //searches for a number in the tree.
int number_of_nodes(struct Cell *cell); //Returns # of unique values in the tree.

#endif
