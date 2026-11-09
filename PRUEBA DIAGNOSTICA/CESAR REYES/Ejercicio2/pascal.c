#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
static double ahora(void) {
    LARGE_INTEGER f, c;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&c);
    return (double)c.QuadPart / (double)f.QuadPart;
}
#else
#include <time.h>
static double ahora(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}
#endif

typedef __int128 i128;

/* printf no soporta __int128: imprimimos digito a digito */
void imprimir_i128(FILE *f, i128 v) {
    char buf[48];
    int i = 0;
    int neg = v < 0;
    unsigned __int128 u = neg ? -(unsigned __int128)v : (unsigned __int128)v;
    if (u == 0) { fputc('0', f); return; }
    while (u > 0) { buf[i++] = '0' + (int)(u % 10); u /= 10; }
    if (neg) fputc('-', f);
    while (i > 0) fputc(buf[--i], f);
}

/* Reserva dinamica: fila r tiene r+1 elementos (triangulo "escalonado").
   Cada fila se calcula a partir de la anterior (programacion dinamica). */
i128 **generar_triangulo(int n) {
    i128 **t = malloc((n + 1) * sizeof(i128 *));
    for (int r = 0; r <= n; r++) {
        t[r] = malloc((r + 1) * sizeof(i128));
        t[r][0] = 1;
        t[r][r] = 1;
        for (int k = 1; k < r; k++)
            t[r][k] = t[r - 1][k - 1] + t[r - 1][k];
    }
    return t;
}

void liberar_triangulo(i128 **t, int n) {
    for (int r = 0; r <= n; r++) free(t[r]);
    free(t);
}

void imprimir_polinomio(i128 *coefs, int n) {
    for (int k = 0; k <= n; k++) {
        int grado = n - k;
        if (k > 0) printf(" + ");
        if (grado == 0) {
            imprimir_i128(stdout, coefs[k]);
        } else {
            if (coefs[k] != 1) imprimir_i128(stdout, coefs[k]);
            if (grado == 1) printf("x");
            else printf("x^%d", grado);
        }
    }
    printf("\n");
}

/* Muestra cada termino c * x^grado. Detecta desbordamiento de 128 bits. */
void evaluar_por_pasos(i128 *coefs, int n, long long x) {
    i128 total = 0;
    printf("\nCalculo de f(%lld) = (%lld+1)^%d segun el polinomio:\n", x, x, n);
    for (int k = 0; k <= n; k++) {
        int grado = n - k;
        i128 pot = 1, termino;
        int ovf = 0;
        for (int j = 0; j < grado && !ovf; j++)
            ovf = __builtin_mul_overflow(pot, (i128)x, &pot);
        if (!ovf) ovf = __builtin_mul_overflow(coefs[k], pot, &termino);
        if (!ovf) ovf = __builtin_add_overflow(total, termino, &total);
        if (ovf) {
            printf("  Paso %d: DESBORDAMIENTO (el valor no cabe en 128 bits)\n", k + 1);
            printf("  Usa un x mas pequeno o la version en Python.\n");
            return;
        }
        printf("  Paso %d: ", k + 1);
        imprimir_i128(stdout, coefs[k]);
        printf(" * %lld^%d = ", x, grado);
        imprimir_i128(stdout, termino);
        printf("   (acumulado = ");
        imprimir_i128(stdout, total);
        printf(")\n");
    }
    printf("Resultado: f(%lld) = ", x);
    imprimir_i128(stdout, total);
    printf("\n");
}

int main(void) {
    int n;
    long long x;
    printf("Ingrese n (0 a 120): ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 120) {
        printf("n invalido (con 128 bits el limite seguro es 120)\n");
        return 1;
    }
    printf("Ingrese x: ");
    if (scanf("%lld", &x) != 1) return 1;

    i128 **t = generar_triangulo(n);
    printf("\n(x+1)^%d = ", n);
    imprimir_polinomio(t[n], n);
    evaluar_por_pasos(t[n], n, x);
    liberar_triangulo(t, n);

    /* Medicion: generar los polinomios k = 0..100, 10 repeticiones */
    const int N = 100, REP = 10;
    double tiempos[10], total = 0;
    for (int i = 0; i < REP; i++) {
        double t0 = ahora();
        i128 **tr = generar_triangulo(N);
        tiempos[i] = ahora() - t0;
        liberar_triangulo(tr, N);
        total += tiempos[i];
    }

    FILE *out = fopen("resultados_pascal_c.txt", "w");
    if (!out) { perror("No se pudo crear el archivo"); return 1; }
    fprintf(out, "EJERCICIO 2 - Lenguaje: C\n");
    fprintf(out, "Se generan los polinomios (x+1)^k para k = 0..%d\n\n", N);
    for (int i = 0; i < REP; i++)
        fprintf(out, "Corrida %d: %.9f s\n", i + 1, tiempos[i]);
    fprintf(out, "Total: %.9f s\n", total);
    fprintf(out, "Promedio: %.9f s\n", total / REP);
    fclose(out);

    printf("\nTiempo promedio (n=%d): %.9f s\n", N, total / REP);
    printf("Se escribio resultados_pascal_c.txt\n");
    return 0;
}