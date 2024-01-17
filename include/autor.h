#ifndef AUTOR_H
#define AUTOR_H

#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[100];
    char instituicao[100];
} Autor;

typedef struct noAutor {
    Autor autor;
    struct noAutor* proximo;
} noAutor;

void imprimirAutores(noAutor **listaAutores);

void adicionarAutor(noAutor **listaAutor, char nome[], char instituicao[]);

void removerAutores(noAutor **listaAutores);

// void incluirAutor(noLivro **listaLivro);

noAutor *remover_autor(noAutor **lista, char nome[]);

// void excluirAutor(noLivro **listaLivro);

#endif