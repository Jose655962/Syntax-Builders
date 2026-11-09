#include <stdio.h>
// if while for en un comentario no cuentan
int main(void) {
    printf("if for while\n");   /* tampoco aqui: return */
    int x = 1e9;
    if (x > 0) return 0;
    return 1;
}