#include "reserva.h"

void imprimirReserva(noReserva *listaReserva) {
    if (listaReserva == NULL) {
        printf("\t\t Não há reservas cadastradas no sistema. \n");
        return ;
    }
    noReserva *aux = listaReserva;

    printf("\t\t---------------------------------------------------- Reservas Cadastrados ------------------------------------\n\n");
    int i = 0;

    while (aux) {
        i++;
        printf("\t\t Reserva %d (Data Início: %15s | Data do Fim: %15s | ID do usuário: %5d | ID do livro: %5d)\n", i, aux->reserva.dataInicio, aux->reserva.dataFim, aux->reserva.identificadorUsuario, aux->reserva.identificadorLivro);
        aux = aux->proximo;
    }

    printf("\t\t--------------------------------------------------------------------------------------------------------------\n\n");

}

int verificarColisoesLivros(noReserva **listaReserva, int idLivro) {
    if(*listaReserva != NULL) {
        noReserva *aux = *listaReserva;
        int identificador = 1;

        while (aux) {
            if (aux->reserva.identificadorLivro == idLivro){
                identificador = 0;
            }
            aux = aux->proximo;
        }

        return identificador;
    } else {
        return 1;
    }
}

void adicionarReserva(noReserva **listaReserva, noLivro **listaLivro, noUsuario **listaUsuario) {
    if (*listaLivro == NULL || *listaUsuario == NULL) {
        printf("\t\tNão é possível realizar reservas sem livros ou autores no arcevo\n");
        return ;
    }
    
    noReserva *novaReserva = malloc(sizeof(noReserva)), *aux;
    if (novaReserva) {
        printf("Informe a data que está sendo realizada a reserva (dd/mm/aaaa): ");
        fgets(novaReserva->reserva.dataInicio, 11, stdin);
        novaReserva->reserva.dataInicio[strcspn(novaReserva->reserva.dataInicio, "\n")] = '\n';

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

        noLivro *auxLivro = *listaLivro;
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

        if(!verificarColisoesLivros(listaReserva, novaReserva->reserva.identificadorLivro)) {
            printf("\n\t\tJá se foi cadastrado esse livro!\n\n");
            return ;
        }

        printf("Informe a data de entrega (dd/mm/aaaa): ");
        fgets(novaReserva->reserva.dataFim, 11, stdin);
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
    } else {
        printf("Não foi possível alocar espaço na memória para reserva\n");
        return;
    }
}

void excluirReservaNoExcluirUsuario(noReserva **listaReserva, int idUser) {
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
            printf("\t\t ID do livro ou do Usuário não encontrado\n");
            return ;
        } else {
            remover = aux->proximo;
            aux->proximo = remover->proximo;
            printf("\n\t\t------------------------------------------- Removido reserva do usuario deletado! ----------------------------------------------\n\n");
            printf("\t\t (Data início: %s | Data fim: %s | ID usuário: %d | ID livro: %d\n\n)", remover->reserva.dataInicio, remover->reserva.dataFim, remover->reserva.identificadorUsuario, remover->reserva.identificadorUsuario);
            printf("\t\t----------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
    }
    free(remover);
}

void excluirReservaNoExluirLivro(noReserva **listaReserva, int idLivro) {
    noReserva *aux = *listaReserva, *remover = NULL;
    if (aux->reserva.identificadorLivro == idLivro) {
            remover = aux;
            *listaReserva = aux->proximo;
            printf("\n\t\t------------------------------------------- Removido reserva do livro deletado! ---------------------------------------------\n\n");
            printf("\t\t(Data início: %s | Data fim: %s | ID usuário: %d | ID livro: %d\n\n)", remover->reserva.dataInicio, remover->reserva.dataFim, remover->reserva.identificadorUsuario, remover->reserva.identificadorUsuario);
            printf("\t\t-------------------------------------------------------------------------------------------------------------------------------\n\n");
        } else {
            while (aux->proximo && aux->proximo->reserva.identificadorLivro != idLivro) {
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
    excluirReservaNoExluirLivro(listaReserva, remover->livro.identificador);
    free(remover);
}

void excluirUsuario(noUsuario **listaUsuario, noReserva **listaReservas) {
    if (*listaUsuario == NULL) {
        printf("\n\t\tNão há usuários cadastrados\n\n");
        return ;
    }
    imprimirUsuarios(*listaUsuario);

    int identificacao;
    printf("Informe a identificação do usuário: ");
    scanf("%d", &identificacao);
    getchar();

    noUsuario *aux = *listaUsuario, *remover = NULL;
    if (aux->usuario.identificador == identificacao) {
        remover = aux;
        *listaUsuario = aux->proximo;

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
    excluirReservaNoExcluirUsuario(listaReservas, remover->usuario.identificador);
    free(remover);
}

void excluirReserva(noReserva **listaReserva) {
    noReserva *aux = *listaReserva, *remover = NULL;

    if (*listaReserva == NULL) {
        printf("\n \t\tNão existem reservas no sistemas\n\n");
        return ;
    } else {
        imprimirReserva(*listaReserva);

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
        free(remover);
    }
}

void alterarReserva(noReserva **listaReserva) {
    if (*listaReserva == NULL) {
        printf("\n \t\tNão existem reservas no sistemas\n\n");
        return ;
    } else {
        imprimirReserva(*listaReserva);

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
        fgets(aux->reserva.dataInicio, 11, stdin);
        aux->reserva.dataInicio[strcspn(aux->reserva.dataInicio, "\n")] = '\0';
        getchar();

        printf("Informe a nova data do fim da reserva: ");
        fgets(aux->reserva.dataFim, 11, stdin);
        aux->reserva.dataFim[strcspn(aux->reserva.dataFim, "\n")] = '\0';

        printf("\t\t--------------------------------------------------------- Reserva escolhida para alterar ---------------------------------------------------------\n\n");
        printf("\t\t ( Data início: %15s | Data Fim: %15s | ID Usuario: %5d | ID Livro: %5d )\n",aux->reserva.dataInicio, aux->reserva.dataFim, aux->reserva.identificadorUsuario, aux->reserva.identificadorLivro);
        printf("\n\t\t-----------------------------------------------------------------------------------------------------------------------------------------\n\n");
    }

    imprimirReserva(*listaReserva);
}