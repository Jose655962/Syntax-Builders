#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *ingles;
    char *espanol;
} Diccionario;

Diccionario palabras_reservadas[] = {
    {"int", "entero"}, {"if", "si"}, {"else", "sino"}, 
    {"while", "mientras"}, {"for", "para"}, {"return", "retornar"},
    {"void", "vacio"}, {"char", "caracter"}, {"float", "flotante"}
};

char* traducir(char* palabra) {
    for (int i = 0; i < 9; i++) {
        if (strcmp(palabra, palabras_reservadas[i].ingles) == 0) {
            return palabras_reservadas[i].espanol;
        }
    }
    return palabra;
}

int main() {
    char codigo_fuente[] = "int main ( ) { if ( x > 0 ) return 1 ; else return 0 ; }";
    char *memoria = (char *)malloc(strlen(codigo_fuente) + 1);
    strcpy(memoria, codigo_fuente);
    
    printf("Codigo Original:\n%s\n\n", memoria);
    printf("Traduccion:\n");

    char *token = strtok(memoria, " \n");
    while (token != NULL) {
        printf("%s ", traducir(token));
        token = strtok(NULL, " \n");
    }
    printf("\n");
    free(memoria);
    return 0;
}
