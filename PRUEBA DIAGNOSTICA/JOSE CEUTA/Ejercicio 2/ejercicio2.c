#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void generar_polinomio(int n, double x) {
    // Uso de memoria dinámica: solicitamos el espacio exacto para la fila (n+1)
    double *fila = (double*)malloc((n + 1) * sizeof(double));
    if (fila == NULL) {
        printf("Error de memoria dinámica\n");
        return;
    }

    // Lógica del triángulo de Pascal iterativo usando un solo arreglo dinámico
    fila[0] = 1;
    for (int i = 1; i <= n; i++) {
        fila[i] = 1;
        for (int j = i - 1; j > 0; j--) {
            fila[j] = fila[j] + fila[j - 1];
        }
    }

    // Mostrar solo si es menor a 10 para no colapsar la pantalla
    if (n <= 10) {
        printf("Polinomio generado para n = %d:\n", n);
        for (int i = 0; i <= n; i++) {
            printf("%.0fx^%d ", fila[i], n - i);
            if(i != n) printf("+ ");
        }
        printf("\n\nCalculando paso a paso para x = %.2f:\n", x);
        
        double resultado_total = 0;
        for (int i = 0; i <= n; i++) {
            int potencia = n - i;
            double calculo_paso = fila[i] * pow(x, potencia);
            printf("+ %.0f * (%.2f^%d) = %.2f\n", fila[i], x, potencia, calculo_paso);
            resultado_total += calculo_paso;
        }
        printf("Resultado final: %.2f\n", resultado_total);
    }
    
    // Liberar la memoria dinámica al terminar
    free(fila);
}

int main() {
    clock_t inicio = clock();
    generar_polinomio(100, 2.0); // Calculando n=100
    clock_t fin = clock();
    
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("\nTiempo de ejecucion en C (n=100): %f segundos\n", tiempo);
    
    return 0;
}