#ifndef RESERVA_H
#define RESERVA_H

#include "livro.h"
#include "usuario.h"

typedef struct Reserva {
    char dataInicio[11];
    char dataFim[11];
    int identificadorUsuario;
    int identificadorLivro;
} Reserva;

typedef struct noReserva{
    Reserva reserva;
    struct noReserva* proximo;
} noReserva;

void imprimirReserva(noReserva *listaReservas);

int verificarColisoesLivros(noReserva **listaReserva, int idLivro);

void adicionarReserva(noReserva **listaReserva, noLivro **listaLivro, noUsuario **listaUsuario);

void excluirReservaNoExcluirUsuario(noReserva **listaReserva, int idUser);

void excluirReservaNoExluirLivro(noReserva **listaReserva, int idLivro);

void excluirLivro(noLivro **listaLivro, noReserva **listaReserva);

void excluirUsuario(noUsuario **listaUsuario, noReserva **listaReservas);

void excluirReserva(noReserva **listaReserva);

void alterarReserva(noReserva **listaReserva);

#endif