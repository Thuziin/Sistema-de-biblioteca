#include "../include/livro.h"

int controle = 0;

void imprimirLivros(noLivro *listLivro) {
    if (listLivro == NULL) {
        printf("\n \t\tLista de livros vazia!\n\n");
        return ;
    } else {
        noLivro *aux = listLivro;
        while (aux != NULL) {
            printf("\n\t\tIdentificador: %d\n", aux->livro.identificador);
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

void adicionarLivro(noLivro **listaLivro) {
    if (controle < 20) {
        noLivro *novoLivro = malloc(sizeof(noLivro)), *aux;
        if (novoLivro) {
            int identificador;
            
            printf("Qual o identificador do livro (XXXXX): ");
            scanf("%d", &identificador);
            getchar();

            aux = *listaLivro;

            while((aux) && (aux->livro.identificador != identificador)) {
                aux = aux->proximo;
            }

            if (aux != NULL) {
                printf("t\t\tEsse identificador pertence a outro livro!");
                return ;
            }
            novoLivro->livro.listaAutores = NULL;
            novoLivro->livro.identificador = identificador;
            printf("Qual o título do livro: ");

            fgets(novoLivro->livro.titulo, 100, stdin);
            novoLivro->livro.titulo[strcspn(novoLivro->livro.titulo, "\n")] = '\0';

            int qtdAutores;
            printf("Quantos autores o livro tem: ");
            scanf("%d", &qtdAutores);
            getchar();
            if (qtdAutores <= 0) {
                printf("Quantos autores o livro tem: ");
                scanf("%d", &qtdAutores);
                getchar();
            }

            for (int i = 0; i < qtdAutores; i++) {
                char autor[100], instituicao[100];

                printf("%dº autor(a): ", i+1);
                fgets(autor, 100, stdin);
                autor[strcspn(autor, "\n")] = '\0';

                printf("Instituição de '%s': ", autor);
                fgets(instituicao, 100, stdin);
                instituicao[strcspn(instituicao, "\n")] = '\0';

                adicionarAutor(&(novoLivro->livro.listaAutores), autor, instituicao);
            }

            printf("Ano de publicação do livro: ");
            scanf("%d", &novoLivro->livro.ano);

            printf("Número de edição do livro: ");
            scanf("%d", &novoLivro->livro.edicao);
            getchar();

            printf("Qual a editora do livro: ");
            fgets(novoLivro->livro.editora, 100, stdin);
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
            controle++;

        } else {
            printf("\t\tNÃO FOI POSSÍVEL ALOCAR ESPAÇO NA MEMÓRIA!");
            return ;
        }
    } else {
        printf("\t\tQuantidade máxima de livros atingida\n");
        return ;
    }
}

void alterarLivro(noLivro **listaLivro) {
    if (*listaLivro == NULL) {
        printf("\n \t\tNão há livros cadastrados para ser alterado\n\n");
        return ;
    } else {
        imprimirLivros(*listaLivro);
        int identificador;
        printf("Informe o identificador do livro que deseja alterar(XXXXX): ");
        scanf("%d", &identificador);
        getchar();

        noLivro *aux = *listaLivro;
        while ((aux) && (aux->livro.identificador != identificador)) {
            aux = aux->proximo;
        }

        if (aux == NULL) {
            printf("O identificador informado não corresponde a nenhum livro\n");
            return ;
        }
        printf("\t\t------------------------------------------------ Livro escolhido para modificar -------------------------------------------------\n\n");
        printf("\n\t\tIdentificador: %d\n", aux->livro.identificador);
        printf("\t\tTitulo: %s\n", aux->livro.titulo);
        printf("\t\tAno de publicação: %d\n", aux->livro.ano);
        imprimirAutores(&(aux->livro.listaAutores));
        printf("\t\tEdição: %d\n", aux->livro.edicao);
        printf("\t\tEditora: %s\n\n", aux->livro.editora);
        printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");

        printf("Informe o novo título: ");
        fgets(aux->livro.titulo, 100, stdin);
        aux->livro.titulo[strcspn(aux->livro.titulo, "\n")] = '\0';

        printf("Informe o novo ano: ");
        scanf("%d", &aux->livro.ano);
        getchar();

        printf("Qual a edicao do livro: ");
        scanf("%d", &aux->livro.edicao);
        getchar();

        printf("Qual a editora do livro: ");
        fgets(aux->livro.editora, sizeof(aux->livro.editora), stdin);
        aux->livro.editora[strcspn(aux->livro.editora, "\n")] = '\0';

        int qtdAutores;

        removerAutores(&(aux->livro.listaAutores));
        aux->livro.listaAutores = NULL;
        printf("Quantos autores: ");
        scanf("%d", &qtdAutores);
        getchar();  
              
        for (int i = 1; i <= qtdAutores; i++) {
            char autor[100], instituicao[100];
            printf("%dº Autor(a)\n", i);
            printf("Digite o nome do autor: ");
            fgets(autor, 100, stdin);
            autor[strcspn(autor, "\n")] = '\0';
            printf("Digite o nome do intituicao: ");
            fgets(instituicao, 100, stdin);
            instituicao[strcspn(instituicao, "\n")] = '\0';
            adicionarAutor(&(aux->livro.listaAutores), autor, instituicao);
        }

        printf("\t\t------------------------------------------------ Livro escolhido para modificar -------------------------------------------------\n\n");
        printf("\n\t\tIdentificador: %d\n", aux->livro.identificador);
        printf("\t\tTitulo: %s\n", aux->livro.titulo);
        printf("\t\tAno de publicação: %d\n", aux->livro.ano);
        imprimirAutores(&(aux->livro.listaAutores));
        printf("\t\tEdição: %d\n", aux->livro.edicao);
        printf("\t\tEditora: %s\n\n", aux->livro.editora);
        printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");

        imprimirLivros(*listaLivro);
    
    }
}

void incluirAutor(noLivro **listaLivro) {
    int identificador;
    printf("Informe o identificador do livro que deseja incluir o autor: ");
    scanf("%d", &identificador);
    getchar();
    
    noLivro *aux = *listaLivro;
    while (aux->livro.identificador != identificador) {
        aux = aux->proximo;
    }

    if (aux == NULL) {
        printf("\n \t\tNão há livros com o identificador informado!\n\n");
        return ;
    }

    printf("\t\t------------------------------------------- Livro com autor que sera adicionado --------------------------------------------------\n\n");
    printf("\t\tIdentificador: %d\n", aux->livro.identificador);
    printf("\t\tTitulo: %s\n", aux->livro.titulo);
    imprimirAutores(&(aux->livro.listaAutores));
    printf("\t\tAno: %d\n", aux->livro.ano);
    printf("\t\tEdicao: %d\n", aux->livro.edicao);
    printf("\t\tEditora: %s\n",aux->livro.editora);
    printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");

    printf("Digite o nome do autor: ");
    char autor[100];
    fgets(autor, 100, stdin);
    printf("Digite o nome da instituicao autor: ");
    char instituicao[100];
    fgets(instituicao, 100, stdin);
    adicionarAutor(&(aux->livro.listaAutores), autor, instituicao);
    
    printf("\t\t--------------------------------------------------- Adicionado com sucesso! -----------------------------------------------------\n\n");
    printf("\t\tIdentificador: %d\n", aux->livro.identificador);
    printf("\t\tTitulo: %s\n", aux->livro.titulo);
    imprimirAutores(&(aux->livro.listaAutores));
    printf("\t\tAno: %d\n", aux->livro.ano);
    printf("\t\tEdicao: %d\n", aux->livro.edicao);
    printf("\t\tEditora: %s\n",aux->livro.editora);
    printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");
}

void excluirAutor(noLivro **listaLivro) {
    if (*listaLivro == NULL) {
        printf("\n \t\tNão existem autores para ser excluido");
        return ;
    }
    int identificador;
    printf("Informe o identificador do livro que deseja excluir: ");
    scanf("%d", &identificador);
    getchar();

    noLivro *aux = *listaLivro;
    noAutor *remover = NULL;
    
    while ((aux) && aux->livro.identificador != identificador) {
        aux = aux->proximo;
    }

    if (aux == NULL) {
        printf("\n \t\t Não foi possível encontrar livro com o identificador fornecido!\n\n");
        return ;
    }

    printf("\t\t------------------------------------------- Livro com autor que sera removido --------------------------------------------------\n\n");
    printf("\t\tIdentificador: %d\n", aux->livro.identificador);
    printf("\t\tTitulo: %s\n", aux->livro.titulo);
    printf("\t\t");
    imprimirAutores(&(aux->livro.listaAutores));
    printf("\t\tAno: %d\n", aux->livro.ano);
    printf("\t\tEdicao: %d\n", aux->livro.edicao);
    printf("\t\tEditora: %s\n",aux->livro.editora);
    printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");


    printf("Digite o nome do autor que queira deletar: ");
    char autor[100];
    fgets(autor, 100, stdin);
    autor[strcspn(autor, "\n")] = '\0';
    remover = remover_autor(&(aux->livro.listaAutores), autor);
    free(remover);

    printf("\t\t--------------------------------------------------- Removido com sucesso! -----------------------------------------------------\n\n");
    printf("\t\tIdentificador: %d\n", aux->livro.identificador);
    printf("\t\tTitulo: %s\n", aux->livro.titulo);
    printf("\t\t");
    imprimirAutores(&(aux->livro.listaAutores));
    printf("\t\tAno: %d\n", aux->livro.ano);
    printf("\t\tEdicao: %d\n", aux->livro.edicao);
    printf("\t\tEditora: %s\n",aux->livro.editora);
     printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");
}