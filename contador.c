#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contador.h"
#include "util.h"

#define MAX_PALAVRAS 1000
#define TAM_LINHA 1024
#define TAM_PALAVRA 100

typedef struct {
    char palavra[TAM_PALAVRA];
    int contagem;
} Palavra;

static int encontrar_palavra(Palavra palavras[], int total, const char *palavra) {
    for (int i = 0; i < total; i++) {
        if (strcmp(palavras[i].palavra, palavra) == 0) {
            return i;
        }
    }
    return -1;
}

void processar_linha(char *linha, Palavra palavras[], int *total, const char *alvo, char letra_filtro, int modo_letra) {
    char *token = strtok(linha, " ,.-\n");
    while (token) {
        limpar_pontuacao(token);
        remover_acentos(token);
        para_minusculas(token);

        if (strlen(token) == 0) {
            token = strtok(NULL, " ,.-\n");
            continue;
        }

        if (alvo && strcmp(token, alvo) != 0) {
            token = strtok(NULL, " ,.-\n");
            continue;
        }

        if (modo_letra && token[0] != letra_filtro) {
            token = strtok(NULL, " ,.-\n");
            continue;
        }

        int idx = encontrar_palavra(palavras, *total, token);
        if (idx >= 0) {
            palavras[idx].contagem++;
        } else if (*total < MAX_PALAVRAS) {
            strncpy(palavras[*total].palavra, token, TAM_PALAVRA);
            palavras[*total].contagem = 1;
            (*total)++;
        }

        token = strtok(NULL, " ,.-\n");
    }
}

void contar_ocorrencias(const char *nome_arquivo, const char *palavra) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Palavra palavras[MAX_PALAVRAS];
    int total = 0;
    char linha[TAM_LINHA];

    if (palavra) {
        char copia[TAM_PALAVRA];
        strncpy(copia, palavra, TAM_PALAVRA);
        limpar_pontuacao(copia);
        remover_acentos(copia);
        para_minusculas(copia);

        while (fgets(linha, sizeof(linha), arquivo)) {
            processar_linha(linha, palavras, &total, copia, 0, 0);
        }

        printf("A palavra '%s' apareceu %d vez(es).\n", copia, total ? palavras[0].contagem : 0);
    } else {
        while (fgets(linha, sizeof(linha), arquivo)) {
            processar_linha(linha, palavras, &total, NULL, 0, 0);
        }

        for (int i = 0; i < total; i++) {
            printf("%s: %d\n", palavras[i].palavra, palavras[i].contagem);
        }
    }

    fclose(arquivo);
}

void contar_por_letra(const char *nome_arquivo, char letra) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Palavra palavras[MAX_PALAVRAS];
    int total = 0;
    char linha[TAM_LINHA];
    letra = tolower(letra);

    while (fgets(linha, sizeof(linha), arquivo)) {
        processar_linha(linha, palavras, &total, NULL, letra, 1);
    }

    printf("Palavras que começam com '%c':\n\n", letra);
    for (int i = 0; i < total; i++) {
        printf("%s: %d\n", palavras[i].palavra, palavras[i].contagem);
    }

    printf("\nTotal: %d palavras distintas encontradas.\n", total);
    fclose(arquivo);
}