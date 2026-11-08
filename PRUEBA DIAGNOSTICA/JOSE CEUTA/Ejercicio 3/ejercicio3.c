#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Diccionario rudimentario para traducir palabras reservadas
void traducir_palabra(char *palabra) {
    if (strcmp(palabra, "int") == 0) printf("entero ");
    else if (strcmp(palabra, "float") == 0) printf("flotante ");
    else if (strcmp(palabra, "return") == 0) printf("retornar ");
    else if (strcmp(palabra, "if") == 0) printf("si ");
    else if (strcmp(palabra, "else") == 0) printf("sino ");
    else if (strcmp(palabra, "while") == 0) printf("mientras ");
    else if (strcmp(palabra, "void") == 0) printf("vacio ");
    else if (strcmp(palabra, "for") == 0) printf("para ");
    else printf("%s ", palabra); // Si no es reservada, la deja igual
}

int main() {
    // 1. Simulación de carga de código en Memoria Dinámica
    const char *codigo_fuente = "int main() { int x = 5; if (x > 0) return 1; else return 0; }";
    
    // Pedimos a la memoria el tamaño exacto del string + 1 para el carácter nulo
    char *buffer_dinamico = (char *)malloc((strlen(codigo_fuente) + 1) * sizeof(char));
    
    if (buffer_dinamico == NULL) {
        printf("Error de asignacion de memoria.\n");
        return 1;
    }
    
    // Copiamos el texto al bloque dinámico
    strcpy(buffer_dinamico, codigo_fuente);
    
    printf("--- TEXTO ORIGINAL ---\n%s\n", buffer_dinamico);
    printf("\n--- TRADUCCION DE RESERVADAS ---\n");
    
    // 2. Extracción (Tokenización) para evaluar cada palabra
    // Usamos espacios y caracteres especiales de C como delimitadores
    char *token = strtok(buffer_dinamico, " (){};=");
    
    while (token != NULL) {
        traducir_palabra(token);
        token = strtok(NULL, " (){};=");
    }
    printf("\n");

    // 3. Liberar la memoria
    free(buffer_dinamico);
    
    return 0;
}