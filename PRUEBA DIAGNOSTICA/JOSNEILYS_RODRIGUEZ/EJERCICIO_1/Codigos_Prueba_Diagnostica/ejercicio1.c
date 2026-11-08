#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Función para validar la secuencia de movimientos
int validar_movimientos(char *ak, int n, char *c, int print_errors) {
    int col_actual = ak[0] - 'a';
    int fila_actual = ak[1] - '1';
    
    char *cadena_temp = strdup(c);
    char *token = strtok(cadena_temp, " ");
    int mov_count = 1;

    while (token != NULL && mov_count <= n) {
        if (token[0] != 'K') {
            if (print_errors) printf("INCORRECTO falla letra %c no pertenece a un caballo\n", token[0]);
            free(cadena_temp);
            return 0;
        }
        
        int col_siguiente = token[1] - 'a';
        int fila_siguiente = token[2] - '1';

        int dx = abs(col_siguiente - col_actual);
        int dy = abs(fila_siguiente - fila_actual);

        if (!((dx == 1 && dy == 2) || (dx == 2 && dy == 1))) {
            if (print_errors) printf("INCORRECTO falla en el movimiento %d\n", mov_count);
            free(cadena_temp);
            return 0;
        }
        
        col_actual = col_siguiente;
        fila_actual = fila_siguiente;
        token = strtok(NULL, " ");
        mov_count++;
    }
    
    if (print_errors) printf("movimiento CORRECTO\n");
    free(cadena_temp);
    return 1;
}

int main() {
    // Pruebas solicitadas en la guia
    char ak1[] = "a1"; char c1[] = "Kc2 Kd4 Kb3 Kc5";
    printf("Para %s n=4: ", ak1); validar_movimientos(ak1, 4, c1, 1);
    
    char ak8[] = "a1"; char c8[] = "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4";
    printf("Para %s n=10: ", ak8); validar_movimientos(ak8, 10, c8, 1);

    // Experimento
    char c_500[] = "Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8";
    
    clock_t inicio = clock();
    for(int i = 0; i < 10; i++) {
        validar_movimientos("a2", 500, c_500, 0); 
    }
    clock_t fin = clock();
    
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    FILE *f = fopen("tiempos.txt", "w");
    if (f) {
        fprintf(f, "Tiempo C (Caballo - 10 veces 500 movs): %f seg\n", tiempo);
        fclose(f);
    }
    printf("Evaluacion 1 lista. Tiempos guardados.\n");
    return 0;
}
