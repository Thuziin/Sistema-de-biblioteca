#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "autor.h"

#define MAX_CARACTERE 100
#define MAX_DATA 11

int controleLivro = 0;
int controleUsuario = 0;
int controleReserva = 0;

typedef struct {
    long int indetificador;
    char titulo[MAX_CARACTERE];
    struct no_Autor *listaAutores;
    int ano;
    int edicao;
    char editora[MAX_CARACTERE];
} Livro;

typedef struct no_Livros{
    Livro livro;
    struct no_Livros* proximo;
} noLivro;

typedef struct {
    long int indetificador;
    char nome[MAX_CARACTERE];
    char endereco[MAX_CARACTERE];
    long int telefone;
} Usuario;

typedef struct no_Usuario{
    Usuario usuario;
    struct no_Usuario* proximo;
} noUsuario;

typedef struct {
    char dataInicio[MAX_DATA];
    char dataFim[MAX_DATA];
    int identificadorUsuario;
    int identificadorLivro;
} Reserva;

typedef struct no_Reserva{
    Reserva reserva;
    struct no_Reserva* proximo;
} noReserva;


void imprimirLivros(noLivro *listaLivro) {
    if (listaLivro == NULL) {
        printf("\n \t\tLista vazia!\n\n");
        return ;
    } else {

        noLivro *aux = listaLivro;
        printf("\n\t\t------------------------------------------------------- Livros Cadastrados -------------------------------------------------------\n\n");
        int i = 0;
        while (aux != NULL) {
            i++;
            printf("\t\tLivro %d", i);
            printf("\n\t\tIdentificador: %ld\n", aux->livro.indetificador);
            printf("\t\tTitulo: %s\n", aux->livro.titulo);
            printf("\t\tAno de publicação: %d\n", aux->livro.ano);
            imprimirAutores(&(aux->livro.listaAutores));
            printf("\t\tEdição: %d\n", aux->livro.edicao);
            printf("\t\tEditora: %s\n\n", aux->livro.editora);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");

            aux = aux->proximo;
        }
    }

}


void imprimirUsuarios (noUsuario *listaUsuario) {
    if (listaUsuario == NULL) {
        printf("\n \t\tNão há usuários cadastrados.\n\n");
        return ;
    }
    noUsuario *aux = listaUsuario;

    printf("\t\t--------------------------------------------------------- Usuarios Cadastrados ---------------------------------------------------------\n\n");

    int i = 0;
    while (aux) {
        i++;
        printf("\t\t Usuário: %d (Nome: %15s | Endereço %30s | Telefone: %11ld | Identificador: %5ld)\n", i, aux->usuario.nome, aux->usuario.endereco, aux->usuario.telefone, aux->usuario.indetificador);
        aux = aux->proximo;
    }

    printf("\n\t\t-----------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

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

/*
    Método que adiciona um ou mais autores a um determinado livro;
    So é chamada quando um livro está sendo cadastrado, e recebe por parametro uma lista de autores, um nome e uma insituição
*/

void adicionarAutor (noAutor **listaAutor, char nome[], char instituicao[]) {
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

/*
    Método que adiciona livros a memória do programa.
    @param: listaLirvro 
    Recebe por parametro uma lista de livros
*/

void removeMemoriaListaAutores (noAutor **listaAutores) {
    noAutor *aux = *listaAutores;
    while (aux) {
        *listaAutores = (*listaAutores)->proximo;
        free(aux);
        aux = *listaAutores;
    }
}

void adicionarLivro(noLivro **listaLivro) {
    // Pede o indentificador ao user para verificar se já existe algum livro com aquele identificador
    if (controleLivro < 20) {
        noLivro *novoLivro = malloc(sizeof(noLivro)), *aux;

        if (novoLivro) {
            novoLivro->livro.listaAutores = NULL;

            printf("Qual o identificador do livro (XXXXXX): ");
            scanf("%ld", &novoLivro->livro.indetificador);
            getchar();

            aux = *listaLivro;

            while ((aux) && (aux->livro.indetificador != novoLivro->livro.indetificador)) {
                aux = aux->proximo;
            }

            if (aux != NULL) {
                printf("\t\tEsse indetificador já foi utilizado em outro livro !");
                return ;
            }

            printf("Qual o título do livro: ");
            fgets(novoLivro->livro.titulo, MAX_CARACTERE, stdin);
            novoLivro->livro.titulo[strcspn(novoLivro->livro.titulo, "\n")] = '\0'; // Remover o caractere de nova linha

            int qtdAutores;
            printf("Quantos autores o livro tem: ");
            scanf("%d", &qtdAutores);
            getchar();
            if (qtdAutores <= 0) {
                printf("Quantos autores o livro tem: ");
                scanf("%d", &qtdAutores);
                getchar();
            }

            novoLivro->livro.listaAutores = NULL;

            for (int i = 0; i < qtdAutores; i++) {
                char autor[MAX_CARACTERE], instituicao[MAX_CARACTERE];

                printf("%dº autor(a): ", i+1);
                fgets(autor, MAX_CARACTERE, stdin);
                autor[strcspn(autor, "\n")] = '\0';

                printf("Instituição de '%s': ", autor);
                fgets(instituicao, MAX_CARACTERE, stdin);
                instituicao[strcspn(instituicao, "\n")] = '\0';

                adicionarAutor(&(novoLivro->livro.listaAutores), autor, instituicao);
            }


            printf("Ano de publicação do livro: ");
            scanf("%d", &novoLivro->livro.ano);

            printf("Número de edição do livro: ");
            scanf("%d", &novoLivro->livro.edicao);
            getchar();

            printf("Qual a editora do livro: ");
            fgets(novoLivro->livro.editora, MAX_CARACTERE, stdin);
            novoLivro->livro.editora[strcspn(novoLivro->livro.editora, "\n")] = '\0';

            novoLivro->proximo = NULL;

            if (*listaLivro) {
                aux = *listaLivro;
                while (aux->proximo) {
                    aux = aux->proximo;
                } 
                aux->proximo = novoLivro;
            } else {
                *listaLivro = novoLivro;
            }
            controleLivro++;
        } else {
            printf("NÃO FOI POSSÍVEL ALOCAR ESPAÇO NA MEMÓRIA");
        }
    } else {
        printf("\t\tQuantidade máxima de livros atingida\n");
        return ;
    }

}

void adicionarUsuario(noUsuario **listaUsuario) {
    if (controleUsuario < 10) {
        noUsuario *novoUsuario = malloc(sizeof(noUsuario)), *aux;

        if (novoUsuario) {
            printf("Informe o identificador do usuário (XXXXX): ");
            scanf("%ld", &novoUsuario->usuario.indetificador);
            getchar();

            printf("Informe o nome do usuário: ");
            fgets(novoUsuario->usuario.nome, MAX_CARACTERE, stdin);
            novoUsuario->usuario.nome[strcspn(novoUsuario->usuario.nome, "\n")] = '\0';

            printf("Informe o endereço do usuário: ");
            fgets(novoUsuario->usuario.endereco, MAX_CARACTERE, stdin);
            novoUsuario->usuario.endereco[strcspn(novoUsuario->usuario.endereco, "\n")] = '\0';

            printf("Informe o telefone do usuário: ");
            scanf("%ld", &novoUsuario->usuario.telefone);
            getchar();

            novoUsuario->proximo = NULL;

            if (*listaUsuario) {
                aux = *listaUsuario;
                while (aux->proximo) {
                    aux = aux->proximo;
                } 
                aux->proximo = novoUsuario;
            } else {
                *listaUsuario = novoUsuario;
            }
            controleUsuario++;

        } else {
            printf("Não foi possível alocar espaço na memória para usuário\n");
            return ;
        }
    } else {
        printf("\t\t O limite de Usuários no sistema já foi preenchido\n");
        return ;
    }
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
                if (auxUsuario->usuario.indetificador == novaReserva->reserva.identificadorUsuario) {
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
                if (auxLivro->livro.indetificador == novaReserva->reserva.identificadorLivro) {
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

void removerAutores(noAutor **listaAutores) {
    noAutor *aux = *listaAutores;
    while (aux) {
        *listaAutores = (*listaAutores)->proximo;
        free(aux);
        aux = *listaAutores;
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

    if (aux->livro.indetificador == identificacao) {
        remover = aux;
        *listaLivro = aux->proximo;

            printf("\t\t--------------------------------------------------- Removido com sucesso! -----------------------------------------------------\n\n");
            printf("\t\tIdentificador: %ld\n", remover->livro.indetificador);
            printf("\t\tTítulo: %s\n", remover->livro.titulo);
            imprimirAutores(&(remover->livro.listaAutores));
            printf("\t\tAno: %d\n", remover->livro.ano);
            printf("\t\tEdição: %d\n", remover->livro.edicao);
            printf("\t\tEditora: %s\n", remover->livro.editora);
            printf("\t\t-------------------------------------------------------------------------------------------------------------------------------\n\n");

    } else {
        while (aux->proximo && aux->proximo->livro.indetificador != identificacao) {
            aux = aux->proximo;
        }
        if (aux->proximo == NULL) {
            printf("\t\tID de usuário não encontrado\n");
            return ;
        } else {
            remover = aux->proximo;
            aux->proximo = remover->proximo;

            printf("\t\t--------------------------------------------------- Removido com sucesso! -----------------------------------------------------\n\n");
            printf("\t\tIdentificador: %ld\n", remover->livro.indetificador);
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
    excluirReserva_no_excluirLivro(listaReserva, remover->livro.indetificador);
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
    if (aux->usuario.indetificador == identificacao) {
        remover = aux;
        *listaUsuarios = aux->proximo;

        printf("\t\t--------------------------------------------------- Removido com sucesso! -----------------------------------------------------\n\n");
        printf("\t\t (Nome: %15s | Endereço: %30s | Telefone: %11ld | Identificador: %5ld)\n\n", remover->usuario.nome, remover->usuario.endereco, remover->usuario.telefone, remover->usuario.indetificador);
        printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");


    } else {
        while (aux->proximo && aux->proximo->usuario.indetificador != identificacao) {
            aux = aux->proximo;
        }
        if (aux->proximo == NULL) {
            printf("\t\tID de usuário não encontrado\n");
            return ;
        } else {
            remover = aux->proximo;
            aux->proximo = remover->proximo;
            printf("\t\t--------------------------------------------------- Removido com sucesso! -----------------------------------------------------\n\n");
            printf("\t\t (Nome: %15s | Endereço: %30s | Telefone: %11ld | Identificador: %5ld)\n\n", remover->usuario.nome, remover->usuario.endereco, remover->usuario.telefone, remover->usuario.indetificador);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
    }
    controleUsuario--;
    excluirReserva_no_excluirUsuario(listaReservas, remover->usuario.indetificador);
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

void alterarLivro(noLivro **listaLivro) {
    if (*listaLivro == NULL) {
        printf("\n \t\tNão há livros cadastrado para se alterar\n\n");
        return ;
    } else {
        imprimirLivros(*listaLivro);

        int indentificadorLivro;
        printf("Informe o identificador do livro que deseja alterar (XXXXXX): ");
        scanf("%d", &indentificadorLivro);
        getchar();

        noLivro *aux = *listaLivro;

        while ((aux) && (aux->livro.indetificador != indentificadorLivro)) {
            aux = aux->proximo;
        }

        if (aux == NULL) {
            printf("Indentificador não encontrado\n");
            return ;
        } else {
            printf("\t\t------------------------------------------------ Livro escolhido para modificar -------------------------------------------------\n\n");
            printf("\n\t\tIdentificador: %ld\n", aux->livro.indetificador);
            printf("\t\tTitulo: %s\n", aux->livro.titulo);
            printf("\t\tAno de publicação: %d\n", aux->livro.ano);
            imprimirAutores(&(aux->livro.listaAutores));
            printf("\t\tEdição: %d\n", aux->livro.edicao);
            printf("\t\tEditora: %s\n\n", aux->livro.editora);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");

            printf("Informe o novo título: ");
            fgets(aux->livro.titulo, MAX_CARACTERE, stdin);
            aux->livro.titulo[strcspn(aux->livro.titulo, "\n")] = '\0';

            printf("Informe o novo ano: ");
            scanf("%d", &aux->livro.ano);
            getchar();

            printf("Qual a edicao do livro: ");
            scanf("%d", &aux->livro.edicao);

            getchar();

            printf("Qual a editora do livro: ");
            fgets(aux->livro.editora, sizeof(aux->livro.editora), stdin);
            aux->livro.editora[strcspn(aux->livro.editora, "\n")] = '\0'; // Remover o caractere de nova linha

            int qtdAutores;

            removeMemoriaListaAutores(&(aux->livro.listaAutores));
            aux->livro.listaAutores = NULL;
            printf("Quantos autores: ");
            scanf("%d", &qtdAutores);
            getchar();

            for (int i = 1; i <= qtdAutores; i++) {
                char autor[MAX_CARACTERE], instituicao[MAX_CARACTERE];
                printf("%dº Autor(a)\n", i);
                printf("Digite o nome do autor: ");
                fgets(autor, MAX_CARACTERE, stdin);
                autor[strcspn(autor, "\n")] = '\0';
                printf("Digite o nome do intituicao: ");
                fgets(instituicao, MAX_CARACTERE, stdin);
                instituicao[strcspn(instituicao, "\n")] = '\0';
                adicionarAutor(&(aux->livro.listaAutores), autor, instituicao);
            }

            printf("\t\t------------------------------------------------ Livro escolhido para modificar -------------------------------------------------\n\n");
            printf("\n\t\tIdentificador: %ld\n", aux->livro.indetificador);
            printf("\t\tTitulo: %s\n", aux->livro.titulo);
            printf("\t\tAno de publicação: %d\n", aux->livro.ano);
            imprimirAutores(&(aux->livro.listaAutores));
            printf("\t\tEdição: %d\n", aux->livro.edicao);
            printf("\t\tEditora: %s\n\n", aux->livro.editora);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");

        }
        imprimirLivros(*listaLivro);
    }
}

void alteraUsuario(noUsuario **listaUsuario) {
    if (*listaUsuario == NULL) {
        printf("\n \t\t Não há usuários cadastrados\n\n");
        return ;
    }
    imprimirUsuarios(*listaUsuario);

    int identificador;
    printf("Informe o ID do usuário que deseja alterar: ");
    scanf("%d", &identificador);
    getchar();

    noUsuario *aux = *listaUsuario;
    while (aux && aux->usuario.indetificador != identificador) {
        aux = aux->proximo;
    }
    if (aux == NULL) {
        printf("\t\tID de usuário não encontrado\n");
        return ;
    } else {
        printf("\t\t--------------------------------------------------------- Usuario escolhido para alterar ---------------------------------------------------------\n\n");
        printf("\t\t ( Nome: %15s | Endereco: %30s | Telefone: %11ld | Identificador: %5ld )\n",aux->usuario.nome, aux->usuario.endereco, aux->usuario.telefone, aux->usuario.indetificador);
        printf("\n\t\t-----------------------------------------------------------------------------------------------------------------------------------------\n\n");
    }

    printf("Forneça os dados parar realizar as alterações: \n");
    printf("Qual o novo nome do usuário: ");
    fgets(aux->usuario.nome, MAX_CARACTERE, stdin);
    aux->usuario.nome[strcspn(aux->usuario.nome, "\n")] = '\0';

    printf("Qual o novo endereço do usuário: ");
    fgets(aux->usuario.endereco, MAX_CARACTERE, stdin);
    aux->usuario.endereco[strcspn(aux->usuario.endereco, "\n")] = '\0';

    printf("Qual o novo telefone: ");
    scanf("%ld", &aux->usuario.telefone);

    printf("\t\t--------------------------------------------------------- Usuario escolhido para alterar ---------------------------------------------------------\n\n");
    printf("\t\t ( Nome: %15s | Endereco: %30s | Telefone: %11ld | Identificador: %5ld )\n",aux->usuario.nome, aux->usuario.endereco, aux->usuario.telefone, aux->usuario.indetificador);
    printf("\n\t\t-----------------------------------------------------------------------------------------------------------------------------------------\n\n");

    imprimirUsuarios(*listaUsuario);
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

void incluirAutor (noLivro **listaLivro) {
    int identificacaoLivro;
    printf("Informe a identificação do livro em que deseja inlcuir o autor: ");
    scanf("%d", &identificacaoLivro);
    getchar();

    noLivro *aux = *listaLivro;

    while (aux->livro.indetificador != identificacaoLivro) {
        aux = aux->proximo;
    }

    if (aux == NULL) {
        printf("\n \t\tIdentificador não encontrado\n\n");
        return ;
    }

     printf("\t\t------------------------------------------- Livro com autor que sera adicionado --------------------------------------------------\n\n");
            printf("\t\tIdentificador: %ld\n", aux->livro.indetificador);
            printf("\t\tTitulo: %s\n", aux->livro.titulo);
            imprimirAutores(&(aux->livro.listaAutores));
            printf("\t\tAno: %d\n", aux->livro.ano);
            printf("\t\tEdicao: %d\n", aux->livro.edicao);
            printf("\t\tEditora: %s\n",aux->livro.editora);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");

            printf("Digite o nome do autor: ");
            char autor[MAX_CARACTERE];
            fgets(autor, MAX_CARACTERE, stdin);
            printf("Digite o nome da instituicao autor: ");
            char instituicao[MAX_CARACTERE];
            fgets(instituicao, MAX_CARACTERE, stdin);
            adicionarAutor(&(aux->livro.listaAutores), autor, instituicao);

            printf("\t\t--------------------------------------------------- Adicionado com sucesso! -----------------------------------------------------\n\n");
            printf("\t\tIdentificador: %ld\n", aux->livro.indetificador);
            printf("\t\tTitulo: %s\n", aux->livro.titulo);
            imprimirAutores(&(aux->livro.listaAutores));
            printf("\t\tAno: %d\n", aux->livro.ano);
            printf("\t\tEdicao: %d\n", aux->livro.edicao);
            printf("\t\tEditora: %s\n",aux->livro.editora);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");
}

noAutor *remover_autor(noAutor **lista, char nome[]){

    noAutor *aux = *lista;
    noAutor *remover = NULL;

    if(*lista == NULL){
        printf("Nao ha autor neste livro!\n");
        return remover;
    }else{

        if(strcmp(aux->autor.nome, nome) == 0){  //conferir o primeiro elemento da lista

            remover = aux;  // o ponteiro remover recebe o primeiro elemento
            *lista = aux->proximo;  // agora o primeiro elemento da lista sera o proximo da lista
            return remover;

        }else{ // se nao for o primeiro elemento

        while((strcmp(nome, aux->proximo->autor.nome) != 0) && aux->proximo){ // avança enquanto aux->proximo for diferente de NULL ou quando for diferente do nome, assim teremos o elemento anterior do que queremos deletar
            aux = aux->proximo;
        }

        if(aux->proximo == NULL) // se for NULL quer dizer que nao encontrou o autor na lista de autores
        {
            printf("Autor nao encontrado\n");
            return remover;
        }else{
            remover = aux->proximo;
            aux->proximo = remover->proximo; // ou aux->proximo->proximo
            return remover;
        }
        }
    }

}


void excluirAutor (noLivro **listaLivro) {
    if (*listaLivro == NULL) {
        printf("\n \t\tNão há autores para ser excluir\n\n");
        return ;
    }
    int indentificarLivro;
    printf("Qual a identificação do livro que deseja ");
    scanf("%d", &indentificarLivro);
    getchar();

    noLivro *aux = *listaLivro;
    noAutor *remover = NULL;

    while (aux && aux->livro.indetificador != indentificarLivro) {
        aux = aux->proximo;
    }

    if (aux == NULL) {
        printf("\n \t\t Identificador não encontrado! \n\n");
        return;
    }

    printf("\t\t------------------------------------------- Livro com autor que sera removido --------------------------------------------------\n\n");
            printf("\t\tIdentificador: %ld\n", aux->livro.indetificador);
            printf("\t\tTitulo: %s\n", aux->livro.titulo);
            printf("\t\t");
            imprimirAutores(&(aux->livro.listaAutores));
            printf("\t\tAno: %d\n", aux->livro.ano);
            printf("\t\tEdicao: %d\n", aux->livro.edicao);
            printf("\t\tEditora: %s\n",aux->livro.editora);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");


            printf("Digite o nome do autor que queira deletar: ");
            char autor[MAX_CARACTERE];
            fgets(autor, MAX_CARACTERE, stdin);
            autor[strcspn(autor, "\n")] = '\0';
            remover = remover_autor(&(aux->livro.listaAutores), autor);
            free(remover);

            printf("\t\t--------------------------------------------------- Removido com sucesso! -----------------------------------------------------\n\n");
            printf("\t\tIdentificador: %ld\n", aux->livro.indetificador);
            printf("\t\tTitulo: %s\n", aux->livro.titulo);
            printf("\t\t");
            imprimirAutores(&(aux->livro.listaAutores));
            printf("\t\tAno: %d\n", aux->livro.ano);
            printf("\t\tEdicao: %d\n", aux->livro.edicao);
            printf("\t\tEditora: %s\n",aux->livro.editora);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");
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

