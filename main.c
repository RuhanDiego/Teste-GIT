#include <stdio.h>
#include <stdlib.h>
#include "contador.h"
#include "util.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo> [palavra]\n", argv[0]);
        return EXIT_FAILURE;
    }

    iniciar_tempo();

    if (argc == 2) {
        contar_todas_palavras(argv[1]);
    } else {
        contar_palavra_especifica(argv[1], argv[2]);
    }

    imprimir_tempo();

    return EXIT_SUCCESS;
}//
// Created by aluno on 05/05/25.
//
