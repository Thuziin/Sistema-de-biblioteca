#include "../include/autor.h"
#include <stdlib.h>

void imprimirAutores (noAutor **listaAutores) {
    noAutor *aux = *listaAutores;
    if (*listaAutores == NULL) {
        printf("\t\tA lista de autores está vazia!\n");
        return ;
    } else {
        printf("\t\tAutores: ");
        while (aux) {
            printf("%s", aux->autor.nome);
            if (aux->proximo) {
                printf(", ");
            }
            aux = aux->proximo;
        }
    }
    printf("\n");
}

void adicionarAutor(noAutor **listaAutor, char nome[], char instituicao[]) {
    noAutor *novoAutor = malloc(sizeof(noAutor)), *aux;
    if (novoAutor) {
        strcpy(novoAutor->autor.nome, nome);
        strcpy(novoAutor->autor.instituicao, instituicao);
        novoAutor->proximo = NULL;

        if (*listaAutor == NULL) {
            *listaAutor = novoAutor;
        } else {
            aux = *listaAutor;
            while (aux->proximo) {
                aux = aux->proximo;
            }
            aux->proximo = novoAutor;
        }
    } else {
        printf("NÃO FOI POSSÍVEL ALOCAR ESPAÇO NA MEMÓRIA\n");
    }
}

void removerAutores(noAutor **listaAutores) {
    noAutor *aux = *listaAutores;
    while (aux) {
        *listaAutores = (*listaAutores)->proximo;
        free(aux);
        aux = *listaAutores;
    }
}

noAutor *remover_autor(noAutor **lista, char nome[]) {
    noAutor *aux = *lista;
    noAutor *remover = NULL;

    if (*lista == NULL) {
        printf("Este livro não possui autoresn\n");
        return remover;
    } else {
        if (strcmp(nome, aux->autor.nome) == 0) {
            remover = aux;
            *lista = aux->proximo;
            return remover;
        } else {
            while (strcmp(nome, aux->proximo->autor.nome) != 0 && (aux->proximo)) {
                aux = aux->proximo;
            }

            if (aux->proximo == NULL) {
                printf("%s não é um autor do livro", nome);
                return remover;
            } else {
                remover = aux;
                *lista = aux->proximo;
                return remover;

            }
        }
    }
}