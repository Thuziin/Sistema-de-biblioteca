#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_CARACTERE_STR 100
#define MAX_CARACTERE_DATA 10

/* Criacao das structs das nossas informações */

typedef struct {
    char nome[MAX_CARACTERE_STR];
    char instituicao[MAX_CARACTERE_STR];
}Autor;

typedef struct no_autor{ // criação do nó para a lista de autores
    Autor autor;
    struct no_autor *proximo;
}No_Autor;

typedef struct {
    long identificador;
    char titulo[MAX_CARACTERE_STR];
    struct no_autor *lista_autores;
    int ano;
    int edicao;
    char editora[MAX_CARACTERE_STR];

}Livro;

typedef struct {
    int identificador; // identificador com 5 numeros (XXXXX)
    char nome[MAX_CARACTERE_STR];
    char endereco[MAX_CARACTERE_STR];
    long telefone;
}Usuario;

typedef struct  {
    char dataInicio[MAX_CARACTERE_DATA];
    char dataFim[MAX_CARACTERE_DATA];
    Usuario identificadorUser;  
    Livro identificadorLivro;
} Reserva;

/* Criacao dos nós das listas encadeadas que sera responsavel por organizar nossas informações */

typedef struct no_livro{ // criação do nó para a lista de livros
    Livro livro;
    struct no_livro *proximo;
}No_Livro;

typedef struct no_reserva{ // criação do nó para a lista de reservas
    Reserva reserva;
    struct no_reserva *proximo;
}No_Reserva;

typedef struct no_usuario{ // criação do nó para a lista de usuarios
    Usuario usuario;
    struct no_usuario *proximo;
}No_Usuario;



/* Funções relacionados aos usuarios, isto é, ADICIONAR - REMOVER - ALTERAR - IMPRIMIR */

void imprimir_usuarios(No_Usuario *lista){
    No_Usuario *aux = lista;

    printf("\t\t--------------------------------------------------------- Usuarios Cadastrados ---------------------------------------------------------\n\n");

    int i = 0;

    while(aux) // enquanto aux for diferente de NULL, isto é, enquanto houver elementos na lista
    {
        i++;
        printf("\t\t Usuario %d ( Nome: %15s | Endereco: %30s | Telefone: %11ld | Identificador: %5d )\n", i, aux->usuario.nome, aux->usuario.endereco, aux->usuario.telefone, aux->usuario.identificador);
        aux = aux->proximo;
    }

    printf("\n\t\t-----------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

void adicionar_usuario(No_Usuario **lista){

    /*A FAZER: CONFERIR QUANTOS USUARIOS JA TEM NA LISTA, SE TIVER 10, NAO PODE ADICIONAR MAIS!!!!!!!!!!!!!*/

    /* Parte para adicionar o novo usuario a lista de usuarios */
    
    No_Usuario *novo = malloc(sizeof(No_Usuario));

    if(novo){ // se houver sucesso na alocação de memoria


    /* Parte para entrada das informaçoes em relaçao ao novo usuario cadastrado */

        printf("Qual o nome do novo usuario: ");
        fgets(novo->usuario.nome, sizeof(novo->usuario.nome), stdin);
        novo->usuario.nome[strcspn(novo->usuario.nome, "\n")] = '\0'; // Remover o caractere de nova linha

        printf("Qual o endereco do novo usuario: ");
        fgets(novo->usuario.endereco, sizeof(novo->usuario.endereco), stdin);
        novo->usuario.endereco[strcspn(novo->usuario.endereco, "\n")] = '\0'; // Remover o caractere de nova linha

        printf("Qual o identificador do novo usuario (XXXXX): ");
        scanf("%d", &novo->usuario.identificador);

        printf("Qual o telefone do novo usuario: ");
        scanf("%ld", &novo->usuario.telefone);

        getchar();

        novo->proximo = NULL; //como esta sendo adicionado ao ultimo da lista, entao nao ha proximo, sendo NULL

        if(*lista==NULL) {   // se a lista de usuarios estiver vazia, isto é, estiver NULL, o primeiro elemento sera o novo usuario cadastrado

            *lista = novo;
         }else{ // se falso, vamos pecorrer a lista ate chegar no ultimo, lembrando que o ultimo sera oque aponta para NULL

         No_Usuario *aux = *lista;

         while(aux->proximo != NULL){
            aux = aux->proximo; // pecorrendo a lista
         }
         aux->proximo = novo; // o ultimo agora sera o penultimo e apontara para o novo usuario que agora é o ultimo da lista

         }

    }else{
        printf("Erro ao alocar a memoria!\n");
    }

}


void alterar_usuario(No_Usuario **lista){

    imprimir_usuarios(*lista);

    int identificador_usuario;
    printf("Digite o identificador do usuario que queira alterar: ");
    scanf("%d", &identificador_usuario);
    getchar();

    /*Buscar usuario*/

    No_Usuario *aux = *lista;
    while(aux && aux->usuario.identificador != identificador_usuario){ // se aux nao for nulo e for diferente do identificador, vá para o proximo elemenyp
        aux = aux->proximo;
    }

    if(aux == NULL){ // se for NULL, significa que nao existe o identificador dentro da lista de usuarios
        printf("Nao existe este identificador!\n");
    }else{
        printf("\t\t--------------------------------------------------------- Usuario escolhido para alterar ---------------------------------------------------------\n\n");
        printf("\t\t ( Nome: %15s | Endereco: %30s | Telefone: %11ld | Identificador: %5d )\n",aux->usuario.nome, aux->usuario.endereco, aux->usuario.telefone, aux->usuario.identificador);
        printf("\n\t\t-----------------------------------------------------------------------------------------------------------------------------------------\n\n");
    }

    /*Inserir dados para alterar usuario*/

          printf("Insira os dados para alteracao:\n");

        printf("Qual o nome do novo usuario: ");
        fgets(aux->usuario.nome, sizeof(aux->usuario.nome), stdin);
        aux->usuario.nome[strcspn(aux->usuario.nome, "\n")] = '\0'; // Remover o caractere de nova linha

        printf("Qual o endereco do novo usuario: ");
        fgets(aux->usuario.endereco, sizeof(aux->usuario.endereco), stdin);
        aux->usuario.endereco[strcspn(aux->usuario.endereco, "\n")] = '\0'; // Remover o caractere de nova linha

        printf("Qual o identificador do novo usuario (XXXXX): ");
        scanf("%d", &aux->usuario.identificador);

        printf("Qual o telefone do novo usuario: ");
        scanf("%ld", &aux->usuario.telefone);

        printf("\t\t--------------------------------------------------------- Usuario Alterado ---------------------------------------------------------\n\n");
        printf("\t\t ( Nome: %15s | Endereco: %30s | Telefone: %11ld | Identificador: %5d )\n",aux->usuario.nome, aux->usuario.endereco, aux->usuario.telefone, aux->usuario.identificador);
        printf("\n\t\t-----------------------------------------------------------------------------------------------------------------------------------------\n\n");

        imprimir_usuarios(*lista);

}








/* Funções relacionados aos livros e autores, isto é, ADICIONAR - REMOVER - ALTERAR - IMPRIMIR 
   A autores, deve incluir a função adionar ou deletar! (a fazer)*/


// funçoes para adicionar autor

void adicionar_autor(No_Autor **lista, char nome[100], char instituicao[100]){  // sera responsavel para adicionar na lista encadeada de autores de cada livro


    No_Autor *novo = malloc(sizeof(No_Autor)), *aux;

    if(novo){

        strcpy(novo->autor.nome, nome);
        strcpy(novo->autor.instituicao, instituicao);
        novo->proximo = NULL;

        if(*lista == NULL){
            *lista = novo;
        }else{
            aux = *lista;
            while (aux->proximo)
            {
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }

    }else{
        printf("Erro ao alocar memoria!");
    }
}

No_Autor *remover_autor(No_Autor **lista, char nome[]){

    No_Autor *aux = *lista;
    No_Autor *remover = NULL;

    if(*lista == NULL){
        printf("Nao ha autor neste livro!\n");
        return remover;
    }else{

        if(strcmp(aux->autor.nome, nome) == 0){  //conferir o primeiro elemento da lista

            remover = aux;  // o ponteiro remover recebe o primeiro elemento
            *lista = aux->proximo;  // agora o primeiro elemento da lista sera o proximo da lista
            return remover;

        }else{ // se nao for o primeiro elemento
        
        while(aux->proximo && (strcmp(nome, aux->proximo->autor.nome) != 0)){ // avança enquanto aux->proximo for diferente de NULL ou quando for diferente do nome, assim teremos o elemento anterior do que queremos deletar
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


// função para adicionar livro

void adicionar_livro(No_Livro **lista){

    No_Livro *novo = malloc(sizeof(No_Livro)), *aux;

        if(novo){

            novo->livro.lista_autores = NULL; //vamos comecar declarando a lista de autores como vazia


            printf("Qual o identificador do livro (XXXXX): ");
            scanf("%d", &novo->livro.identificador);

            getchar();

            printf("Qual o titulo do livro: ");
            fgets(novo->livro.titulo, sizeof(novo->livro.titulo), stdin);
            novo->livro.titulo[strcspn(novo->livro.titulo, "\n")] = '\0'; // Remover o caractere de nova linha

            printf("Qual o ano do livro: ");
            scanf("%d", &novo->livro.ano);

            printf("Qual a edicao do livro: ");
            scanf("%d", &novo->livro.edicao);

            getchar();

            printf("Qual a editora do livro: ");
            fgets(novo->livro.editora, sizeof(novo->livro.editora), stdin);
            novo->livro.editora[strcspn(novo->livro.editora, "\n")] = '\0'; // Remover o caractere de nova linha

            int quant_autores;

            printf("Quantos autores: ");

            scanf("%d", &quant_autores);

            getchar();

            for(int i = 0; i < quant_autores; i++){

                char autor[100], instituicao[100];

                printf("Autor %d\n", i+1);

                printf("Digite o nome do autor: ");
                gets(autor);


                printf("Digite a instituicao do autor: ");
                gets(instituicao);


                adicionar_autor(&(novo->livro.lista_autores), autor, instituicao); // vai adicionando na lista de autores (lista encadeada)

            }


            novo->proximo = NULL;


            if(*lista==NULL){

                    *lista = novo;

            }else{

                    aux = *lista;
                    while (aux->proximo)
                    {
                        aux = aux->proximo;
                    }

                    aux->proximo = novo;

            }


        }else{
            printf("Erro ao alocar a memoria!");
        }


}

void imprimir_autores(No_Autor **lista_autores){
    No_Autor *aux = *lista_autores;

    if(*lista_autores == NULL){
        printf("Autor: Desconhecido");
    }else{

        printf("Autores: ");


    while (aux)
    {

        printf("%s", aux->autor.nome);

        if(aux->proximo){
            printf(", ");
        }

        aux = aux->proximo;
    }
    }

    printf("\n");
}

void imprimir_livros(No_Livro *lista){
    No_Livro *aux = lista;

    if(lista == NULL){
        printf("Lista vazia!\n");
    }else{

        printf("\n\t\t--------------------------------------------------------- Livros Cadastrados ------------------------------------------------------\n\n");
        int i = 0;

        while (aux)
        {
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");
            i++;
            printf("\t\tLivro %d Identificador: %d\n",i, aux->livro.identificador);
            printf("\t\tLivro %d Titulo: %s\n",i, aux->livro.titulo);
            printf("\t\tLivro %d ",i);
            imprimir_autores(&(aux->livro.lista_autores));
            printf("\t\tLivro %d Ano: %d\n",i, aux->livro.ano);
            printf("\t\tLivro %d Edicao: %d\n",i, aux->livro.edicao);
            printf("\t\tLivro %d Editora: %s\n",i, aux->livro.editora);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");
            aux = aux->proximo;

        }


    }
}

void adicionar_mais_um_autor_no_livro(No_Livro **lista){
    int identificacao_livro;
    printf("Qual a identificacao do livro em que vc queira adicionar um autor: ");
    scanf("%d", &identificacao_livro);
    getchar();

    /*Buscar o livro*/
    No_Livro *aux = *lista;

    while(aux && aux->livro.identificador != identificacao_livro){ // enquanto aux nao é NULL e aux nao possui identificador: avance um elemento
        aux = aux->proximo;
    }
    if(aux==NULL){
        printf("Identificador nao achado!");
    }else{

            printf("\t\t------------------------------------------- Livro com autor que sera adicionado --------------------------------------------------\n\n");
            printf("\t\tIdentificador: %d\n", aux->livro.identificador);
            printf("\t\tTitulo: %s\n", aux->livro.titulo);
            printf("\t\t");
            imprimir_autores(&(aux->livro.lista_autores));
            printf("\t\tAno: %d\n", aux->livro.ano);
            printf("\t\tEdicao: %d\n", aux->livro.edicao);
            printf("\t\tEditora: %s\n",aux->livro.editora);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");

            printf("Digite o nome do autor: ");
            char autor[MAX_CARACTERE_STR];
            gets(autor);
            printf("Digite o nome da instituicao autor: ");
            char instituicao[MAX_CARACTERE_STR];
            gets(instituicao);
            adicionar_autor(&(aux->livro.lista_autores), autor, instituicao);

            printf("\t\t--------------------------------------------------- Adicionado com sucesso! -----------------------------------------------------\n\n");
            printf("\t\tIdentificador: %d\n", aux->livro.identificador);
            printf("\t\tTitulo: %s\n", aux->livro.titulo);
            printf("\t\t");
            imprimir_autores(&(aux->livro.lista_autores));
            printf("\t\tAno: %d\n", aux->livro.ano);
            printf("\t\tEdicao: %d\n", aux->livro.edicao);
            printf("\t\tEditora: %s\n",aux->livro.editora);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");
    }
}

void remover_um_autor_no_livro(No_Livro **lista){

    int identificacao_livro;
    printf("Qual a identificacao do livro em que vc queira remover um autor: ");
    scanf("%d", &identificacao_livro);
    getchar();

    /*Buscar o livro*/
    No_Livro *aux = *lista;

    No_Autor *remover; // ponteiro para recebermos o elemento que iremos remover

    while(aux && aux->livro.identificador != identificacao_livro){ // enquanto aux nao é NULL e aux nao possui identificador: avance um elemento
        aux = aux->proximo;
    }
    if(aux==NULL){
        printf("Identificador nao achado!");
    }else{

            printf("\t\t------------------------------------------- Livro com autor que sera removido --------------------------------------------------\n\n");
            printf("\t\tIdentificador: %d\n", aux->livro.identificador);
            printf("\t\tTitulo: %s\n", aux->livro.titulo);
            printf("\t\t");
            imprimir_autores(&(aux->livro.lista_autores));
            printf("\t\tAno: %d\n", aux->livro.ano);
            printf("\t\tEdicao: %d\n", aux->livro.edicao);
            printf("\t\tEditora: %s\n",aux->livro.editora);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");
        

            printf("Digite o nome do autor que queira deletar: ");
            char autor[MAX_CARACTERE_STR];
            gets(autor);
            remover = remover_autor(&(aux->livro.lista_autores), autor);
            free(remover);

            printf("\t\t--------------------------------------------------- Removido com sucesso! -----------------------------------------------------\n\n");
            printf("\t\tIdentificador: %d\n", aux->livro.identificador);
            printf("\t\tTitulo: %s\n", aux->livro.titulo);
            printf("\t\t");
            imprimir_autores(&(aux->livro.lista_autores));
            printf("\t\tAno: %d\n", aux->livro.ano);
            printf("\t\tEdicao: %d\n", aux->livro.edicao);
            printf("\t\tEditora: %s\n",aux->livro.editora);
            printf("\t\t-----------------------------------------------------------------------------------------------------------------------------------\n\n");
    }

}


int main () {

    /* Declarações para inicar a lista, isto é, a lista começarão apontando para NULL, pois ainda nao existe elementos nas listas */

    No_Autor *lista_autores = NULL;
    No_Usuario *lista_usuarios  = NULL;
    No_Livro *lista_livros  = NULL;
    No_Reserva *lista_reservas  = NULL;

    /*
    
    adicionar(&lista_usuarios);
    adicionar(&lista_usuarios);

    alterar_usuario(&lista_usuarios);

    */

   adicionar_livro(&lista_livros);
   adicionar_livro(&lista_livros);

   adicionar_mais_um_autor_no_livro(&lista_livros);

   remover_um_autor_no_livro(&lista_livros);
   imprimir_livros(lista_livros);

   



    return 0;
}
 /*A FAZER: remover usuarios, remover livros, adicionar reserva, alterar reserva, remover resevar. Atentar que, nao e obrigatorio, mas poder fazer uma
 função que quando deleta um usuario ou livro, a reserva que esteja com o elemento deletado tambem seja deletado! */