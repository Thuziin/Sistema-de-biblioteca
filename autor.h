#ifndef AUTOR_H
#define AUTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char instituicao[100];
} Autor;

typedef struct noAutor {
    Autor autor;
    struct noAutor* proximo;
} noAutor;

void imprimirAutores (noAutor **listaAutores);

#endif