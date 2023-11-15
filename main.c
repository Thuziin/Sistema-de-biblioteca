#include <stdio.h>

typedef struct {
    char nome[150];
    char instituicao[150];
} Autor;

struct Livro {
    char identificador[150];
    char *autores[150];
};



int main () {
    return 0;
}