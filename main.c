#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "autor.h"
#include "livro.h"
#include "usuario.h"
#include "reserva.h"


int main () {
    noLivro *listaDeLivros = NULL;
    noUsuario *listaDeUsuarios = NULL;
    noReserva *listaDeReservas = NULL;

    int op;
    bool k = true;

    int opInside;
    while (k) {
        printf("\t\t------------------------------- MENU --------------------------------------\n");
        printf("\t\t| 1- Usuários                                                             |\n");
        printf("\t\t| 2- Livros                                                               |\n");
        printf("\t\t| 3- Reserva                                                              |\n");
        printf("\t\t| 4- Relatórios                                                           |\n");
        printf("\t\t| 5- Sair                                                                 |\n");
        printf("\t\t---------------------------------------------------------------------------\n");
        printf("\n\n");
        printf("Informe sua opção: ");
        scanf("%d", &op);
        switch (op) {
        case 1 :
            printf("\t\t------------------------------- Escolha --------------------------------------\n");
            printf("\t\t| 1- Adicionar Usuário                                                       |\n");
            printf("\t\t| 2- Alterar Usuário                                                         |\n");
            printf("\t\t| 3- Excluir Usuário                                                         |\n");
            printf("\t\t------------------------------------------------------------------------------\n");
            printf("Qual opção deseja: ");
            scanf("%d", &opInside);
            getchar();
            if (opInside == 1) {
                adicionarUsuario(&listaDeUsuarios);
            }
            if (opInside == 2) {
                alteraUsuario(&listaDeUsuarios);
            }
            if (opInside == 3) {
                excluirUsuario(&listaDeUsuarios, &listaDeReservas);
            }
            continue;
        case 2:
            printf("\t\t------------------------------- Escolha --------------------------------------\n");
            printf("\t\t| 1- Adicionar Livro                                                         |\n");
            printf("\t\t| 2- Alterar Livro                                                           |\n");
            printf("\t\t| 3- Incluir Autor                                                           |\n");
            printf("\t\t| 4- Exlcuir Autor                                                           |\n");
            printf("\t\t| 5- Excluir Livro                                                           |\n");
            printf("\t\t------------------------------------------------------------------------------\n");
            printf("Qual opção deseja: ");
            scanf("%d", &opInside);
            getchar();
            if (opInside == 1) {
                adicionarLivro(&listaDeLivros);
            }
            if (opInside == 2) {
                alterarLivro(&listaDeLivros);
            }
            if (opInside == 3) {
                incluirAutor(&listaDeLivros);
            }
            if (opInside == 4) {
                excluirAutor(&listaDeLivros);
            }
            if(opInside == 5) {
                excluirLivro(&listaDeLivros, &listaDeReservas);
            }
            continue;
        case 3:
            printf("\t\t------------------------------- Escolha --------------------------------------\n");
            printf("\t\t| 1- Adicionar Reserva                                                       |\n");
            printf("\t\t| 2- Alterar Reserva                                                         |\n");
            printf("\t\t| 3- Excluir Reserva                                                         |\n");
            printf("\t\t------------------------------------------------------------------------------\n");
            printf("Qual opção deseja: ");
            scanf("%d", &opInside);
            getchar();
            if (opInside == 1) {
                adicionarReserva(&listaDeReservas, &listaDeLivros, &listaDeUsuarios);
            }
            if (opInside == 2) {
                alterarReserva(&listaDeReservas);
            }
            if (opInside == 3) {
                excluirReserva(&listaDeReservas);
            }
            continue;
        case 4:
            printf("\t\t------------------------------- Escolha --------------------------------------\n");
            printf("\t\t| 1- Listar Livro                                                            |\n");
            printf("\t\t| 2- Listar Usuário                                                          |\n");
            printf("\t\t| 3- Listar Usuários com Reserva                                             |\n");
            printf("\t\t------------------------------------------------------------------------------\n");
            printf("Qual opção deseja: ");
            scanf("%d", &opInside);
            getchar();
            if (opInside == 1) {
                imprimirLivros(listaDeLivros);
            }
            if (opInside == 2) {
                imprimirUsuarios(listaDeUsuarios);
            }
            if (opInside == 3) {
                imprimirReserva(listaDeReservas);
            }
            continue;   
        case 5:
            k = false;  
            break;
        }
    }

    return 0;
}