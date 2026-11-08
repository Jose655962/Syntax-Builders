#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void generar_polinomio_y_evaluar(int n, double x) {
    double *coef = (double *)malloc((n + 1) * sizeof(double));
    coef[0] = 1;
    for (int i = 1; i <= n; i++) {
        coef[i] = 1;
        for (int j = i - 1; j > 0; j--) {
            coef[j] = coef[j] + coef[j - 1];
        }
    }

    printf("(x+1)^%d = ", n);
    for (int i = 0; i <= n; i++) {
        printf("%.0fx^%d", coef[i], n - i);
        if (i < n) printf(" + ");
    }
    printf("\n\n");

    double resultado = 0;
    printf("Evaluacion para x = %.2f:\n", x);
    for (int i = 0; i <= n; i++) {
        double termino = coef[i] * pow(x, n - i);
        resultado += termino;
        printf("Paso %d: %.0f * (%.2f^%d) = %.2f | Acumulado = %.2f\n", i+1, coef[i], x, n - i, termino, resultado);
    }
    printf("Resultado Final: %.2f\n\n", resultado);
    free(coef);
}

int main() {
    generar_polinomio_y_evaluar(5, 2.0); 

    clock_t inicio = clock();
    double *coef_100 = (double *)malloc((100 + 1) * sizeof(double));
    coef_100[0] = 1;
    for (int i = 1; i <= 100; i++) {
        coef_100[i] = 1;
        for (int j = i - 1; j > 0; j--) {
            coef_100[j] = coef_100[j] + coef_100[j - 1];
        }
    }
    clock_t fin = clock();
    free(coef_100);

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    FILE *f = fopen("tiempos.txt", "a");
    if(f) {
        fprintf(f, "Tiempo C (Pascal n=100): %f seg\n", tiempo);
        fclose(f);
    }
    return 0;
}
