#ifndef USUARIO_H
#define USUARIO_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Usuario {
    int identificador;
    char nome[100];
    char endereco[100];
    int telefone;
} Usuario;

typedef struct noUsuario {
    Usuario usuario;
    struct noUsuario *proximo;
} noUsuario;

void imprimirUsuarios(noUsuario *listaUsario);

void adicionarUsuario(noUsuario **listaUsuarios);

void alteraUsuario(noUsuario **listaUsuario);

#endif