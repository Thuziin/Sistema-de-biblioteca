#ifndef LIVRO_H
#define LIVRO_H

#include <stdlib.h>

#include "autor.h"

typedef struct Livro {
    int identificador;
    char titulo[100];
    struct noAutor *listaAutores;
    int ano;
    int edicao;
    char editora[100];
} Livro;

typedef struct noLivro {
    Livro livro;
    struct noLivro *proximo;
} noLivro;

void imprimirLivros(noLivro *listaLivro);

void adicionarLivro(noLivro **listaLivro);

// void excluirReserva_no_excluirLivro(noReserva **listaReserva, int idLiv);

// void excluirLivro(noLivro **listaLivro, noReserva **listaReserva); 

void alterarLivro(noLivro **listaLivro);

void incluirAutor(noLivro **listaLivro);

void excluirAutor(noLivro **listaLivro);


#endif