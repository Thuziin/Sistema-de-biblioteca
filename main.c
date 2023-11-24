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

typedef struct {
    long identificador;
    char titulo[MAX_CARACTERE_STR];
    char *autores[MAX_CARACTERE_STR];
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

typedef struct no_autor{ // criação do nó para a lista de autores
    Autor autor;
    struct no_autor *proximo;
}No_Autor;

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



/* Funções relacionados aos usuarios, isto é, ADICIONAR - REMOVER - BUSCAR - ALTERAR - IMPRIMIR */

void adicionar(No_Usuario **lista){

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

void imprimir_usuarios(No_Usuario *lista){
    No_Usuario *aux = lista;

    printf("\t\t--------------------------------------------------------- Usuarios Cadastrados ---------------------------------------------------------\n\n");

    int i = 1;

    while(aux) // enquanto aux for diferente de NULL, isto é, enquanto houver elementos na lista
    {
        printf("\t\t Usuario %d ( Nome: %15s | Endereco: %30s | Telefone: %11ld | Identificador: %5d )\n", i, aux->usuario.nome, aux->usuario.endereco, aux->usuario.telefone, aux->usuario.identificador);
        i++;
        aux = aux->proximo;
    }

    printf("\n\t\t-----------------------------------------------------------------------------------------------------------------------------------------\n\n");
}


int main () {

    /* Declarações para inicar a lista, isto é, a lista começarão apontando para NULL, pois ainda nao existe elementos nas listas */

    No_Autor *lista_autores = NULL;
    No_Usuario *lista_usuarios  = NULL;
    No_Livro *lista_livros  = NULL;
    No_Reserva *lista_reservas  = NULL;


    /*

    adicionar(&lista_usuarios);

    imprimir_usuarios(lista_usuarios);

    */






    return 0;
}