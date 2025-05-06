#include "util.h"
#include <ctype.h>
#include <string.h>

//Como o trabalho pede que tenha apenas int main em main.c, foi criado o arquivo util.c com todas as funções "extras" que são necessárias para que o contador funcione com os parâmetros pedidos na atividade.

//Esta função normaliza todas as palavras de uma string para minúsculas, afim de evitar sua contagem dupla.
void para_minusculas(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}
// Esta função modifica uma string, removendo todos os caracteres que não são letra ou número. Esta função foi desenvolvida, principalmente, para retirar vírgulas, pontos, e hifens que aparecem junto com as palavras.
void limpar_pontuacao(char *str) {
    char *src = str;
    char *dst = str;
    while (*src) {
        if (isalnum((unsigned char)*src) || *src == '-') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

//Esta função percorre a string a procura de um caractere acentuado fornecido no switch case. Se encontrar uma letra acentuada, ela troca para a letra correspondente sem o acento. Esta função trata também o Cedilha (Ç)
void remover_acentos(char *str) {
    char *src = str;
    char *dst = str;
    while (*src) {
        if ((unsigned char)src[0] == 0xC3) {
            switch ((unsigned char)src[1]) {
                case 0xA1: *dst = 'a'; break;
                case 0xA9: *dst = 'e'; break;
                case 0xAD: *dst = 'i'; break;
                case 0xB3: *dst = 'o'; break;
                case 0xA2: *dst = 'a'; break;
                case 0xAA: *dst = 'e'; break;
                case 0xAE: *dst = 'i'; break;
                case 0xB4: *dst = 'o'; break;
                case 0xBA: *dst = 'u'; break;
                case 0xA7: *dst = 'c'; break;
                default: *dst = src[1]; break;
            }
            src += 2;
            dst++;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
}