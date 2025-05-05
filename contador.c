#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contador.h"
#include "util.h"

#define MAX_PALAVRAS 1000
#define TAM_LINHA 1024

typedef struct {
    char *palavra;
    int contagem;
} Palavra;

static Palavra palavras[MAX_PALAVRAS];
static int total_palavras = 0;

int encontrar_ou_adicionar(char *palavra_normalizada) {
    for (int i = 0; i < total_palavras; i++) {
        if (strcmp(palavras[i].palavra, palavra_normalizada) == 0) {
            return i;
        }
    }

    if (total_palavras < MAX_PALAVRAS) {
        palavras[total_palavras].palavra = strdup(palavra_normalizada);
        palavras[total_palavras].contagem = 0;
        return total_palavras++;
    }

    return -1;
}

void contar_todas_palavras(const char *nome_arquivo) {
    FILE *fp = fopen(nome_arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char linha[TAM_LINHA];
    int total_palavras_lidas = 0;

    while (fgets(linha, TAM_LINHA, fp)) {
        char *token = strtok(linha, " ,.-\n\r");
        while (token) {
            char *normalizada = normalizar(token);
            int idx = encontrar_ou_adicionar(normalizada);
            if (idx >= 0) {
                palavras[idx].contagem++;
                total_palavras_lidas++;
            }
            free(normalizada);
            token = strtok(NULL, " ,.-\n\r");
        }
    }

    for (int i = 0; i < total_palavras; i++) {
        printf("%s: %d\n", palavras[i].palavra, palavras[i].contagem);
        free(palavras[i].palavra);
    }

    printf("\nTotal de palavras: %d\n", total_palavras_lidas);
    printf("Total de palavras únicas: %d\n", total_palavras);

    fclose(fp);
}

void contar_palavra_especifica(const char *nome_arquivo, const char *palavra) {
    FILE *fp = fopen(nome_arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    int contagem = 0;
    char linha[TAM_LINHA];
    char *normalizada_busca = normalizar(palavra);

    while (fgets(linha, TAM_LINHA, fp)) {
        char *token = strtok(linha, " ,.-\n\r");
        while (token) {
            char *normalizada = normalizar(token);
            if (strcmp(normalizada, normalizada_busca) == 0) contagem++;
            free(normalizada);
            token = strtok(NULL, " ,.-\n\r");
        }
    }

    printf("\"%s\": %d\n", palavra, contagem);
    free(normalizada_busca);
    fclose(fp);
}