#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contador.h"
#include "util.h"

//Esta função analisa os argumentos da linha de comando e analisa qual função chamar. Ela também verifica se foi chamado o arquivo, e "pega" o seu nome.
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo> [palavra|--letra letra]\n", argv[0]);
        return 1;
    }

    const char *nome_arquivo = argv[1];

    if (argc == 4 && strcmp(argv[2], "--letra") == 0) {
        contar_por_letra(nome_arquivo, argv[3][0]);
    } else if (argc == 3) {
        contar_ocorrencias(nome_arquivo, argv[2]);
    } else if (argc == 2) {
        contar_ocorrencias(nome_arquivo, NULL);
    } else {
        fprintf(stderr, "Uso inválido dos argumentos.\n");
        return 1;
    }

    return 0;
}