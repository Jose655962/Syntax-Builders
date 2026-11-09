#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    const char *ingles;
    const char *espanol;
} Par;

static const Par TABLA[] = {
    {"auto", "automatico"},        {"break", "romper"},
    {"case", "caso"},              {"char", "caracter"},
    {"const", "constante"},        {"continue", "continuar"},
    {"default", "por_defecto"},    {"do", "hacer"},
    {"double", "doble"},           {"else", "sino"},
    {"enum", "enumeracion"},       {"extern", "externo"},
    {"float", "flotante"},         {"for", "para"},
    {"goto", "ir_a"},              {"if", "si"},
    {"inline", "en_linea"},        {"int", "entero"},
    {"long", "largo"},             {"register", "registro"},
    {"restrict", "restringido"},   {"return", "retornar"},
    {"short", "corto"},            {"signed", "con_signo"},
    {"sizeof", "tamano_de"},       {"static", "estatico"},
    {"struct", "estructura"},      {"switch", "segun"},
    {"typedef", "definir_tipo"},   {"union", "union"},
    {"unsigned", "sin_signo"},     {"void", "vacio"},
    {"volatile", "volatil"},       {"while", "mientras"},
    {"_Alignas", "alinear_como"},  {"_Alignof", "alineacion_de"},
    {"_Atomic", "atomico"},        {"_Bool", "booleano"},
    {"_Complex", "complejo"},      {"_Generic", "generico"},
    {"_Imaginary", "imaginario"},  {"_Noreturn", "sin_retorno"},
    {"_Static_assert", "asercion_estatica"},
    {"_Thread_local", "local_al_hilo"}
};
#define NUM_PAR ((int)(sizeof TABLA / sizeof TABLA[0]))

typedef struct {
    int linea;
    int indice;
} Hallazgo;

static char *cargar_archivo(const char *ruta, size_t *tam) {
    FILE *f = fopen(ruta, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long largo = ftell(f);
    rewind(f);

    char *texto = malloc((size_t)largo + 1);
    if (!texto) { fclose(f); return NULL; }

    *tam = fread(texto, 1, (size_t)largo, f);
    texto[*tam] = '\0';
    fclose(f);
    return texto;
}

static int buscar(const char *p, size_t len) {
    for (int k = 0; k < NUM_PAR; k++) {
        if (strlen(TABLA[k].ingles) == len && strncmp(TABLA[k].ingles, p, len) == 0)
            return k;
    }
    return -1;
}

static Hallazgo *analizar(const char *t, size_t tam, int *cantidad, int *conteo) {
    int capacidad = 16, n = 0, linea = 1;
    Hallazgo *h = malloc(capacidad * sizeof(Hallazgo));
    if (!h) return NULL;

    size_t i = 0;
    while (i < tam) {
        char c = t[i];

        if (c == '\n') {                                   /* salto de linea */
            linea++; i++;
        } else if (c == '/' && i + 1 < tam && t[i + 1] == '/') {   /* comentario // */
            while (i < tam && t[i] != '\n') i++;
        } else if (c == '/' && i + 1 < tam && t[i + 1] == '*') {   /* comentario */
            i += 2;
            while (i + 1 < tam && !(t[i] == '*' && t[i + 1] == '/')) {
                if (t[i] == '\n') linea++;
                i++;
            }
            i += 2;
        } else if (c == '"' || c == '\'') {                /* cadena o caracter */
            char comilla = c;
            i++;
            while (i < tam && t[i] != comilla && t[i] != '\n') {
                if (t[i] == '\\' && i + 1 < tam) i++;      /* secuencia de escape */
                i++;
            }
            if (i < tam && t[i] == comilla) i++;
        } else if (c == '#') {                             /* directiva: saltar su nombre */
            i++;
            while (i < tam && (t[i] == ' ' || t[i] == '\t')) i++;
            while (i < tam && isalpha((unsigned char)t[i])) i++;
        } else if (isdigit((unsigned char)c)) {            /* numero: 1e9, 0x1F, 10UL */
            while (i < tam && (isalnum((unsigned char)t[i]) || t[i] == '.' || t[i] == '_')) i++;
        } else if (isalpha((unsigned char)c) || c == '_') {/* identificador */
            size_t ini = i;
            while (i < tam && (isalnum((unsigned char)t[i]) || t[i] == '_')) i++;

            int k = buscar(t + ini, i - ini);
            if (k >= 0) {
                if (n == capacidad) {                      /* crecer el arreglo */
                    capacidad *= 2;
                    Hallazgo *nuevo = realloc(h, capacidad * sizeof(Hallazgo));
                    if (!nuevo) { free(h); return NULL; }
                    h = nuevo;
                }
                h[n].linea = linea;
                h[n].indice = k;
                n++;
                conteo[k]++;
            }
        } else {
            i++;
        }
    }
    *cantidad = n;
    return h;
}

static void reporte(FILE *f, const char *ruta, size_t tam, Hallazgo *h, int n, int *conteo) {
    fprintf(f, "ANALISIS DE PALABRAS RESERVADAS DE C\n");
    fprintf(f, "Archivo: %s (%zu bytes cargados en memoria dinamica)\n\n", ruta, tam);

    fprintf(f, "--- Apariciones ---\n");
    for (int i = 0; i < n; i++)
        fprintf(f, "Linea %4d: %-15s -> %s\n", h[i].linea,
                TABLA[h[i].indice].ingles, TABLA[h[i].indice].espanol);

    fprintf(f, "\n--- Resumen ---\n");
    int distintas = 0;
    for (int k = 0; k < NUM_PAR; k++) {
        if (conteo[k] > 0) {
            fprintf(f, "%-15s -> %-18s : %d\n", TABLA[k].ingles, TABLA[k].espanol, conteo[k]);
            distintas++;
        }
    }
    fprintf(f, "\nTotal de apariciones: %d\n", n);
    fprintf(f, "Palabras reservadas distintas: %d\n", distintas);
}

int main(int argc, char *argv[]) {
    const char *ruta = (argc > 1) ? argv[1] : "palabras_reservadas.c";

    size_t tam = 0;
    char *texto = cargar_archivo(ruta, &tam);
    if (!texto) {
        fprintf(stderr, "No se pudo abrir el archivo: %s\n", ruta);
        return 1;
    }

    int conteo[NUM_PAR];
    memset(conteo, 0, sizeof conteo);

    int n = 0;
    Hallazgo *h = analizar(texto, tam, &n, conteo);
    if (!h) {
        fprintf(stderr, "Error de memoria\n");
        free(texto);
        return 1;
    }

    reporte(stdout, ruta, tam, h, n, conteo);

    FILE *out = fopen("resultados_palabras.txt", "w");
    if (out) {
        reporte(out, ruta, tam, h, n, conteo);
        fclose(out);
        printf("\nSe escribio resultados_palabras.txt\n");
    }

    free(h);
    free(texto);
    return 0;
}