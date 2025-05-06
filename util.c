#include "util.h"
#include <ctype.h>
#include <string.h>

void para_minusculas(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

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