#include "../include/usuario.h"

void imprimirUsuarios(noUsuario *listaUsuario) {
    if (listaUsuario == NULL) {
        printf("\n\t\tNão há usuários cadastrados no banco de dados\n\n");
        return ;
    }
    noUsuario *aux = listaUsuario;

    printf("\t\t--------------------------------------------------------- Usuarios Cadastrados ---------------------------------------------------------\n\n");
    int i = 0;
    i++;
    while (aux) {
        i++;
        printf("\t\t Usuário: %d (Nome: %15s | Endereço %30s | Telefone: %11d | Identificador: %5d)\n", i, aux->usuario.nome, aux->usuario.endereco, aux->usuario.telefone, aux->usuario.identificador);
        aux = aux->proximo;
    }
    printf("\t\t--------------------------------------------------------- Usuarios Cadastrados ---------------------------------------------------------\n\n");
}

void adicionarUsuario(noUsuario **listaUsuarios) {
    noUsuario *novoUsuario = malloc(sizeof(noUsuario)), *aux;

    if (novoUsuario) {
        printf("Informe o identificador do usuário (XXXXX): ");
        scanf("%d", &novoUsuario->usuario.identificador);
        getchar();

        printf("Informe o nome do usuário: ");
        fgets(novoUsuario->usuario.nome, 100, stdin);
        novoUsuario->usuario.nome[strcspn(novoUsuario->usuario.nome, "\n")] = '\0';

        printf("Informe o endereço do usuário: ");
        fgets(novoUsuario->usuario.endereco, 100, stdin);
        novoUsuario->usuario.endereco[strcspn(novoUsuario->usuario.endereco, "\n")] = '\0';
    
        printf("Informe o telefone do usuário: ");
        scanf("%d", &novoUsuario->usuario.telefone);
        getchar();

        novoUsuario->proximo = NULL;

        if (*listaUsuarios) {
            aux = *listaUsuarios;
            while(aux->proximo) {
                aux = aux->proximo;
            }
            aux->proximo = novoUsuario;
        } else {
            *listaUsuarios = novoUsuario;
        }
    } else {
        printf("Não foi possível alocar espaço na memória para usuário.");
        return ;
    }
}

void alteraUsuario(noUsuario **listaUsuario) {
    if (*listaUsuario == NULL) {
        printf("Não existem usuários cadastrados!");
        return ;
    }
    imprimirUsuarios(*listaUsuario);

    int identificador;
    printf("Informe o identificador do usuário que queira alterar(XXXXX): ");
    scanf("%d", &identificador);
    getchar();

    noUsuario *aux = *listaUsuario;
    while((aux) && (aux->usuario.identificador) != identificador) {
        aux = aux->proximo->proximo;
    }

    if (aux == NULL) {
        printf("O identificador fornecido não foi encontrado na base de dados.");
        return ;
    }

    printf("\t\t--------------------------------------------------------- Usuario escolhido para alterar ---------------------------------------------------------\n\n");
    printf("\t\t ( Nome: %15s | Endereco: %30s | Telefone: %11d | Identificador: %5d )\n",aux->usuario.nome, aux->usuario.endereco, aux->usuario.telefone, aux->usuario.identificador);
    printf("\n\t\t-----------------------------------------------------------------------------------------------------------------------------------------\n\n");

    printf("Forneça os dadso para realizar as alterações: \n");
    printf("Qual o nome do usuário: ");
    fgets(aux->usuario.nome, 100, stdin);
    aux->usuario.nome[strcspn(aux->usuario.nome, "\n")] = '\0';

    printf("Endereço do usuário: ");
    fgets(aux->usuario.endereco, 100, stdin);
    aux->usuario.endereco[strcspn(aux->usuario.endereco, "\n")] = '\0';

    printf("Qual o telefone do usuário: ");
    scanf("%d", &aux->usuario.telefone);

    imprimirUsuarios(*listaUsuario);
}