#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"
#include <locale.h>

static clock_t tempo_cpu_inicio;
static time_t tempo_real_inicio;

char remover_acento(unsigned char c) {
    switch (c) {
        case 'á': case 'à': case 'â': case 'ã': case 'ä': return 'a';
        case 'Á': case 'À': case 'Â': case 'Ã': case 'Ä': return 'a';
        case 'é': case 'è': case 'ê': case 'ë': return 'e';
        case 'É': case 'È': case 'Ê': case 'Ë': return 'e';
        case 'í': case 'ì': case 'î': case 'ï': return 'i';
        case 'Í': case 'Ì': case 'Î': case 'Ï': return 'i';
        case 'ó': case 'ò': case 'ô': case 'õ': case 'ö': return 'o';
        case 'Ó': case 'Ò': case 'Ô': case 'Õ': case 'Ö': return 'o';
        case 'ú': case 'ù': case 'û': case 'ü': return 'u';
        case 'Ú': case 'Ù': case 'Û': case 'Ü': return 'u';
        case 'ç': case 'Ç': return 'c';
        default: return tolower(c);
    }
}

char *normalizar(const char *str) {
    size_t len = strlen(str);
    char *res = malloc(len + 1);
    if (!res) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isalpha((unsigned char)str[i]) || (unsigned char)str[i] >= 128) {
            res[j++] = remover_acento((unsigned char)str[i]);
        }
    }
    res[j] = '\0';
    return res;
}


void iniciar_tempo() {
    tempo_cpu_inicio = clock();
    tempo_real_inicio = time(NULL);
}

void imprimir_tempo() {
    clock_t tempo_cpu_fim = clock();
    time_t tempo_real_fim = time(NULL);

    printf("\nTempo de CPU (clocks): %ld\n", tempo_cpu_fim - tempo_cpu_inicio);
    printf("Tempo de CPU (segundos): %.3f\n", (double)(tempo_cpu_fim - tempo_cpu_inicio) / CLOCKS_PER_SEC);
    printf("Tempo real (segundos): %.3f\n", difftime(tempo_real_fim, tempo_real_inicio));
}
