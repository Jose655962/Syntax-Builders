#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Reloj de alta resolución (equivalente a perf_counter de Python) */
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

/* Devuelve 1 si todos los movimientos son correctos, 0 si no.
   En msg deja el mensaje de salida. Se detiene en el primer error. */
int verificar(const char *inicio, char **movs, int n, char *msg, size_t tam) {
    int col = inicio[0] - 'a';
    int fila = inicio[1] - '1';

    for (int i = 0; i < n; i++) {
        const char *m = movs[i];

        if (m[0] != 'K') {
            snprintf(msg, tam, "INCORRECTO falla letra %c no pertenece a un caballo", m[0]);
            return 0;
        }
        if (strlen(m) != 3 || m[1] < 'a' || m[1] > 'h' || m[2] < '1' || m[2] > '8') {
            snprintf(msg, tam, "INCORRECTO falla en el movimiento %d", i + 1);
            return 0;
        }

        int nc = m[1] - 'a';
        int nf = m[2] - '1';
        int dc = abs(nc - col);
        int df = abs(nf - fila);

        if (!((dc == 1 && df == 2) || (dc == 2 && df == 1))) {
            snprintf(msg, tam, "INCORRECTO falla en el movimiento %d", i + 1);
            return 0;
        }
        col = nc;
        fila = nf;
    }
    strcpy(msg, "movimiento CORRECTO");
    return 1;
}

/* Mide 'veces' repeticiones; guarda cada tiempo en tiempos[] */
void medir(const char *inicio, char **movs, int n, int veces, double *tiempos, char *msg) {
    for (int i = 0; i < veces; i++) {
        double t0 = ahora();
        verificar(inicio, movs, n, msg, 128);
        double t1 = ahora();
        tiempos[i] = t1 - t0;
    }
}

void escribir_bloque(FILE *out, int veces, double *tiempos) {
    double total = 0;
    fprintf(out, "--- %d repeticiones ---\n", veces);
    for (int i = 0; i < veces; i++) {
        fprintf(out, "Corrida %d: %.9f s\n", i + 1, tiempos[i]);
        total += tiempos[i];
    }
    fprintf(out, "Total: %.9f s\n", total);
    fprintf(out, "Promedio: %.9f s\n\n", total / veces);
}

int main(void) {
    /* 1) Leer cadena.txt completo en memoria dinámica */
    FILE *f = fopen("cadena.txt", "r");
    if (!f) { perror("No se pudo abrir cadena.txt"); return 1; }

    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    rewind(f);

    char *texto = malloc(tam + 1);
    size_t leidos = fread(texto, 1, tam, f);
    texto[leidos] = '\0';
    fclose(f);

    /* 2) Separar en palabras (como split() en Python) con arreglo dinámico */
    int capacidad = 64, n = 0;
    char **movs = malloc(capacidad * sizeof(char *));
    for (char *tok = strtok(texto, " \t\r\n"); tok; tok = strtok(NULL, " \t\r\n")) {
        if (n == capacidad) {
            capacidad *= 2;
            movs = realloc(movs, capacidad * sizeof(char *));
        }
        movs[n++] = tok;
    }
    printf("Movimientos leidos: %d\n", n);

    /* 3) Buscar casillas iniciales que den CORRECTO */
    char msg[128];
    char validas[64][3];
    int nvalidas = 0;
    for (char c = 'a'; c <= 'h'; c++) {
        for (char r = '1'; r <= '8'; r++) {
            char ini[3] = {c, r, '\0'};
            if (verificar(ini, movs, n, msg, sizeof msg)) {
                strcpy(validas[nvalidas++], ini);
            }
        }
    }
    printf("Casillas iniciales que dan CORRECTO:");
    for (int i = 0; i < nvalidas; i++) printf(" %s", validas[i]);
    printf("\n");

    if (nvalidas == 0) {
        printf("Ninguna casilla funciona: revisa cadena.txt\n");
        return 1;
    }
    const char *inicio = validas[0];

    /* 4) Medir */
    double t10[10], t100[100];
    medir(inicio, movs, n, 10, t10, msg);
    medir(inicio, movs, n, 100, t100, msg);

    /* 5) Escribir resultados_c.txt */
    FILE *out = fopen("resultados_c.txt", "w");
    if (!out) { perror("No se pudo crear resultados_c.txt"); return 1; }

    fprintf(out, "EJERCICIO 1 - Lenguaje: C\n");
    fprintf(out, "Casilla inicial usada: %s\n", inicio);
    fprintf(out, "Movimientos verificados: %d\n", n);
    fprintf(out, "Resultado: %s\n\n", msg);
    escribir_bloque(out, 10, t10);
    escribir_bloque(out, 100, t100);
    fclose(out);

    printf("Listo: se escribio resultados_c.txt\n");

    free(movs);
    free(texto);
    return 0;
}