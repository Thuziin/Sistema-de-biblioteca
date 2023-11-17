#include <stdio.h>

typedef struct {
    char nome[150];
    char instituicao[150];
} Autor;

typedef struct {
    char identificador[150];
    char titulo[150];
    char *autores[150];
    int ano;
    int edicao;
    char editora[50];

}Livro;

typedef struct {
    char identificador[150];
    char nome[150];
    char endereço[250];
    int telefone;
} Usuario;

typedef struct  {
    char dataInicio[9];
    char dataFim[9];
    Usuario *identificadorUser;
    Livro *identificadorLivro;
} Reserva;


int main () {
    return 0;
}
