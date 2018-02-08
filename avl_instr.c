#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "avl.h"
#define BUFSIZE 20
char buf[BUFSIZE];
int bufp = 0;

char* get_instr(char *instr, int lim) {
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
