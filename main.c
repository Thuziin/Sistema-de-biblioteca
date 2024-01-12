#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "autor.h"
#include "livro.h"
#include "usuario.h"

#define MAX_CARACTERE 100
#define MAX_DATA 11

int controleLivro = 0;
int controleUsuario = 0;
int controleReserva = 0;

typedef struct {
    char dataInicio[MAX_DATA];
    char dataFim[MAX_DATA];
    int identificadorUsuario;
    int identificadorLivro;
} Reserva;

typedef struct noReserva{
    Reserva reserva;
    struct noReserva* proximo;
} noReserva;

void imprimirReservas (noReserva *listaReservas) {
    noReserva *aux = listaReservas;

    printf("\t\t---------------------------------------------------- Reservas Cadastrados ------------------------------------\n\n");
    int i = 0;

    while (aux) {
        i++;
        printf("\t\t Reserva %d (Data Início: %15s | Data do Fim: %15s | ID do usuário: %5d | ID do livro: %5d)\n", i, aux->reserva.dataInicio, aux->reserva.dataFim, aux->reserva.identificadorUsuario, aux->reserva.identificadorLivro);
        aux = aux->proximo;
    }

    printf("\t\t--------------------------------------------------------------------------------------------------------------\n\n");

}

int verificar_colisoes_livros(noReserva **listaReserva, int idLiv){
    if(*listaReserva != NULL){
        noReserva *aux = *listaReserva;
        int indetificador = 1;

        while(aux){

            if(aux->reserva.identificadorLivro == idLiv){

                indetificador = 0;

            }

            aux = aux->proximo;
        }

        return indetificador;

    }else{
        return 1;
    }
}

void adicionarReserva(noReserva **listaReserva, noLivro **listaLivros, noUsuario **listaUsuario) {
    if (*listaLivros == NULL || *listaUsuario == NULL) {
        printf("\t\tNão é possível realizar reservas sem livros ou autores no arcevo\n");
        return ;
    }
    if (controleReserva < 20) {
        noReserva *novaReserva = malloc(sizeof(noReserva)), *aux;

        if (novaReserva) {
            printf("Informe a data da reserva (dd/mm/aa): ");
            fgets(novaReserva->reserva.dataInicio, MAX_DATA, stdin);
            novaReserva->reserva.dataInicio[strcspn(novaReserva->reserva.dataInicio, "\n")] = '\0';


            printf("Informe o identificador do usuário (XXXXX): ");
            scanf("%d", &novaReserva->reserva.identificadorUsuario);
            getchar();

            noUsuario *auxUsuario = *listaUsuario;
            while (auxUsuario) {
                if (auxUsuario->usuario.identificador == novaReserva->reserva.identificadorUsuario) {
                    break;
                }
                auxUsuario = auxUsuario->proximo;
            }

            if (auxUsuario == NULL) {
                printf("\t\tID de usuário não identificado\n");
                return ;
            }

            printf("Informe o identificador do livro (XXXXX): ");
            scanf("%d", &novaReserva->reserva.identificadorLivro);
            getchar();

            noLivro *auxLivro = *listaLivros;
            while (auxLivro) {
                if (auxLivro->livro.identificador == novaReserva->reserva.identificadorLivro) {
                    break;
                }
                auxLivro = auxLivro->proximo;
            }

            if (auxLivro == NULL) {
                printf("\t\tID de livro não identificado\n");
                return ;
            }

            if(!verificar_colisoes_livros(listaReserva, novaReserva->reserva.identificadorLivro)){
                printf("\n\t\tJá se foi cadastro este livro!\n\n");
                return;
            }

            printf("Informe a data de entrega (dd/mm/aa): ");
            fgets(novaReserva->reserva.dataFim, MAX_DATA, stdin);
            novaReserva->reserva.dataFim[strcspn(novaReserva->reserva.dataFim, "\n")] = '\0';

            novaReserva->proximo = NULL;

            if (*listaReserva) {
                aux = *listaReserva;
                while (aux->proximo) {
                    aux = aux->proximo;
                } 
                aux->proximo = novaReserva;
            } else {
                *listaReserva = novaReserva;
            }
            controleReserva++;
        } else {
            printf("Não foi possível alocar espaço na memória para reserva");
            return ;
        }
    } else {
        printf("Limite de reservas atingido!");
        return ;
    }
}

void excluirReserva_no_excluirUsuario(noReserva **listaReserva, int idUser) {
    noReserva *aux = *listaReserva, *remover = NULL;

   
        if (aux->reserva.identificadorUsuario == idUser) {
            remover = aux;
            *listaReserva = aux->proximo;
            printf("\n\t\t------------------------------------------- Removido reserva do usuario deletado! ---------------------------------------------\n\n");
            printf("\t\t(Data início: %s | Data fim: %s | ID usuário: %d | ID livro: %d\n\n)", remover->reserva.dataInicio, remover->reserva.dataFim, remover->reserva.identificadorUsuario, remover->reserva.identificadorUsuario);
            printf("\t\t---------------------------------------------------------------------------------------------------------------------------------\n\n");
        } else {
            while (aux->proximo && aux->proximo->reserva.identificadorUsuario != idUser) {
                aux = aux->proximo;
            }
            if (aux->proximo == NULL) {
                printf("\t\tID do livro ou do Usuário não encontrado\n");
                return ;
            } else {
                remover = aux->proximo;
                aux->proximo = remover->proximo;
                printf("\n\t\t------------------------------------------- Removido reserva do usuario deletado! ----------------------------------------------\n\n");
                printf("\t\t (Data início: %s | Data fim: %s | ID usuário: %d | ID livro: %d\n\n)", remover->reserva.dataInicio, remover->reserva.dataFim, remover->reserva.identificadorUsuario, remover->reserva.identificadorUsuario);
                printf("\t\t----------------------------------------------------------------------------------------------------------------------------------\n\n");
            }
        }
        controleReserva--;
        free(remover);
    
}

void excluirReserva_no_excluirLivro(noReserva **listaReserva, int idLiv) {
    noReserva *aux = *listaReserva, *remover = NULL;

   
        if (aux->reserva.identificadorLivro == idLiv) {
            remover = aux;
            *listaReserva = aux->proximo;
            printf("\n\t\t------------------------------------------- Removido reserva do livro deletado! ---------------------------------------------\n\n");
            printf("\t\t(Data início: %s | Data fim: %s | ID usuário: %d | ID livro: %d\n\n)", remover->reserva.dataInicio, remover->reserva.dataFim, remover->reserva.identificadorUsuario, remover->reserva.identificadorUsuario);
            printf("\t\t-------------------------------------------------------------------------------------------------------------------------------\n\n");
        } else {
            while (aux->proximo && aux->proximo->reserva.identificadorLivro != idLiv) {
                aux = aux->proximo;
            }
            if (aux->proximo == NULL) {
                printf("\t\tID do livro ou do Usuário não encontrado\n");
                return ;
            } else {
                remover = aux->proximo;
                aux->proximo = remover->proximo;
                printf("\n\t\t------------------------------------------- Removido reserva do livro deletado! ----------------------------------------------\n\n");
                printf("\t\t (Data início: %s | Data fim: %s | ID usuário: %d | ID livro: %d\n\n)", remover->reserva.dataInicio, remover->reserva.dataFim, remover->reserva.identificadorUsuario, remover->reserva.identificadorUsuario);
                printf("\t\t--------------------------------------------------------------------------------------------------------------------------------\n\n");
            }
        }
        controleReserva--;
        free(remover);
    
}

void excluirLivro(noLivro **listaLivro, noReserva **listaReserva) {
    if (*listaLivro == NULL) {
        printf("\n \t\tA lista de livros está vazia\n\n");
        return ;
    }

    imprimirLivros(*listaLivro);

    int identificacao;
    printf("Informe a identificação do livro que deseja excluir: ");
    scanf("%d", &identificacao);
    getchar();

    noLivro *aux = *listaLivro, *remover = NULL;

    if (aux->livro.identificador == identificacao) {
        remover = aux;
        *listaLivro = aux->proximo;

            printf("\t\t--------------------------------------------------- Removido com sucesso! -----------------------------------------------------\n\n");
            printf("\t\tIdentificador: %d\n", remover->livro.identificador);
            printf("\t\tTítulo: %s\n", remover->livro.titulo);
            imprimirAutores(&(remover->livro.listaAutores));
            printf("\t\tAno: %d\n", remover->livro.ano);
            printf("\t\tEdição: %d\n", remover->livro.edicao);
            printf("\t\tEditora: %s\n", remover->livro.editora);
            printf("\t\t-------------------------------------------------------------------------------------------------------------------------------\n\n");

    } else {
        while (aux->proximo && aux->proximo->livro.identificador != identificacao) {
            aux = aux->proximo;
        }
        if (aux->proximo == NULL) {
            printf("\t\tID de usuário não encontrado\n");
            return ;
        } else {
            remover = aux->proximo;
            aux->proximo = remover->proximo;

            printf("\t\t--------------------------------------------------- Removido com sucesso! -----------------------------------------------------\n\n");
            printf("\t\tIdentificador: %d\n", remover->livro.identificador);
            printf("\t\tTítulo: %s\n", remover->livro.titulo);
            imprimirAutores(&(remover->livro.listaAutores));
            printf("\t\tAno: %d\n", remover->livro.ano);
            printf("\t\tEdição: %d\n", remover->livro.edicao);
            printf("\t\tEditora: %s\n", remover->livro.editora);
            printf("\t\t-------------------------------------------------------------------------------------------------------------------------------\n\n");

        }
    }
    
    removerAutores(&(remover->livro.listaAutores));
    controleLivro--;
    excluirReserva_no_excluirLivro(listaReserva, remover->livro.identificador);
    free(remover);
}

void excluirUsuario(noUsuario **listaUsuarios, noReserva **listaReservas) {
    if (*listaUsuarios == NULL) {
        printf("\n\t\tNão há usuários cadastrados\n\n");
        return ;
    }
    imprimirUsuarios(*listaUsuarios);

    int identificacao;
    printf("Informe a identificação do usuário: ");
    scanf("%d", &identificacao);
    getchar();

    noUsuario *aux = *listaUsuarios, *remover = NULL;
    if (aux->usuario.identificador == identificacao) {
        remover = aux;
        *listaUsuarios = aux->proximo;

        printf("\t\t--------------------------------------------------- Removido com sucesso! -----------------------------------------------------\n\n");
        printf("\t\t (Nome: %15s | Endereço: %30s | Telefone: %11d | Identificador: %5d)\n\n", remover->usuario.nome, remover->usuario.endereco, remover->usuario.telefone, remover->usuario.identificador);
        printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");


    } else {
        while (aux->proximo && aux->proximo->usuario.identificador != identificacao) {
            aux = aux->proximo;
        }
        if (aux->proximo == NULL) {
            printf("\t\tID de usuário não encontrado\n");
            return ;
        } else {
            remover = aux->proximo;
            aux->proximo = remover->proximo;
            printf("\t\t--------------------------------------------------- Removido com sucesso! -----------------------------------------------------\n\n");
            printf("\t\t (Nome: %15s | Endereço: %30s | Telefone: %11d | Identificador: %5d)\n\n", remover->usuario.nome, remover->usuario.endereco, remover->usuario.telefone, remover->usuario.identificador);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
    }
    controleUsuario--;
    excluirReserva_no_excluirUsuario(listaReservas, remover->usuario.identificador);
    free(remover);
}

void excluirReserva(noReserva **listaReserva) {
    noReserva *aux = *listaReserva, *remover = NULL;

    if (*listaReserva == NULL) {
        printf("\n \t\tNão existem reservas no sistemas\n\n");
        return ;
    } else {
        // imprimiReserva();

        int idUser, idLivro;
        printf("Informe o ID do usuário: ");
        scanf("%d", &idUser);
        getchar();

        printf("Informe o ID do livro: ");
        scanf("%d", &idLivro);
        getchar();

        if (aux->reserva.identificadorUsuario == idUser && aux->reserva.identificadorLivro == idLivro) {
            remover = aux;
            *listaReserva = aux->proximo;
            printf("\t\t--------------------------------------------------- Removido com sucesso! -----------------------------------------------------\n\n");
            printf("\t\t(Data início: %s | Data fim: %s | ID usuário: %d | ID livro: %d\n\n)", remover->reserva.dataInicio, remover->reserva.dataFim, remover->reserva.identificadorUsuario, remover->reserva.identificadorUsuario);
            printf("\t\t-------------------------------------------------------------------------------------------------------------------------------\n\n");
        } else {
            while (aux->proximo && aux->proximo->reserva.identificadorUsuario != idUser && aux->proximo->reserva.identificadorLivro != idLivro) {
                aux = aux->proximo;
            }
            if (aux->proximo == NULL) {
                printf("\t\tID do livro ou do Usuário não encontrado\n");
                return ;
            } else {
                remover = aux->proximo;
                aux->proximo = remover->proximo;
                printf("\t\t--------------------------------------------------- Removido com sucesso! -----------------------------------------------------\n\n");
                printf("\t\t (Data início: %s | Data fim: %s | ID usuário: %d | ID livro: %d\n\n)", remover->reserva.dataInicio, remover->reserva.dataFim, remover->reserva.identificadorUsuario, remover->reserva.identificadorUsuario);
                printf("\t\t-------------------------------------------------------------------------------------------------------------------------------\n\n");
            }
        }
        controleReserva--;
        free(remover);
    }
}

void alterarReserva(noReserva **listaReserva) {

    if (*listaReserva == NULL) {
        printf("\n \t\tNão existem reservas no sistemas\n\n");
        return ;
    } else {
        imprimirReservas(*listaReserva);

        noReserva *aux = *listaReserva;

        int idUser, idLivro;
        printf("Informe o ID do usuário: ");
        scanf("%d", &idUser);
        getchar();

        printf("Informe o ID do livro: ");
        scanf("%d", &idLivro);
        getchar();

        while (aux && aux->reserva.identificadorUsuario != idUser && aux->reserva.identificadorLivro != idLivro) {
            aux = aux->proximo;
        }
        if (aux == NULL) {
            printf("\t\tReserva não encontrada\n");
            return ;
        } else {
            printf("\t\t--------------------------------------------------------- Reserva escolhida para alterar ---------------------------------------------------------\n\n");
            printf("\t\t ( Data início: %15s | Data Fim: %15s | ID Usuario: %5d | ID Livro: %5d )\n",aux->reserva.dataInicio, aux->reserva.dataFim, aux->reserva.identificadorUsuario, aux->reserva.identificadorLivro);
            printf("\n\t\t-----------------------------------------------------------------------------------------------------------------------------------------\n\n");
        }

        printf("Informe a nova data do início da reserva: ");
        fgets(aux->reserva.dataInicio, MAX_DATA, stdin);
        aux->reserva.dataInicio[strcspn(aux->reserva.dataInicio, "\n")] = '\0';
        getchar();

        printf("Informe a nova data do fim da reserva: ");
        fgets(aux->reserva.dataFim, MAX_DATA, stdin);
        aux->reserva.dataFim[strcspn(aux->reserva.dataFim, "\n")] = '\0';

        printf("\t\t--------------------------------------------------------- Reserva escolhida para alterar ---------------------------------------------------------\n\n");
        printf("\t\t ( Data início: %15s | Data Fim: %15s | ID Usuario: %5d | ID Livro: %5d )\n",aux->reserva.dataInicio, aux->reserva.dataFim, aux->reserva.identificadorUsuario, aux->reserva.identificadorLivro);
        printf("\n\t\t-----------------------------------------------------------------------------------------------------------------------------------------\n\n");
    }

    imprimirReservas(*listaReserva);
}

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
                imprimirReservas(listaDeReservas);
            }
            continue;   
        case 5:
            k = false;  
            break;
        }
    }

    return 0;
}