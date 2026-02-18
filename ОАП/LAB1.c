#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void zb(unsigned char *b, int i) {
    b[i / 8] |= (1 << (i % 8));
}


void ub(unsigned char *b, int i) {
    b[i / 8] &= ~(1 << (i % 8));
}


int pb(unsigned char *b, int i) {
    return (b[i / 8] >> (i % 8)) & 1;
}