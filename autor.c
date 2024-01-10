#include "autor.h"

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