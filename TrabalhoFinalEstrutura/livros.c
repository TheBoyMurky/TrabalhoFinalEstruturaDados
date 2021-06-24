#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>


struct Livro {
    char titulo[50];
    char autor[50];
    //Criar um array para que possa representar cada exemplar
    //em seu próprio array, Ex.:
    //3 exemplares = exemplar = { 0, 1, 1 }
    //1 para quando está em estoque e 0 quando foi emprestado
    int  exemplares;
    //Valor Chave para identificação
    char isbn[18];
};
struct NoLivro {
    struct Livro livro;
    struct NoLivro* prox;
};
struct NoEncontradoLivro {
    struct NoLivro* encontrado;
    struct NoEncontradoLivro* prox;
};

struct NoLivro* primeiro = NULL;
struct NoLivro* atual = NULL;
struct NoLivro* anterior = NULL;
struct NoLivro* proximo = NULL;
struct NoLivro* temporario = NULL;

//Colocar um novo livro no início
void cadastrar(void) {
    char ISBN[18];
    char temp[50];
    //Iniciamos um ponteiro do tipo No para receber o endereço que será alocado por malloc de tamanho que cabe a nossa struct No
    struct NoLivro* cadastro = malloc(sizeof(struct NoLivro)); //malloc é apenas uma função para reservar um espaço em memória de tamanho x e vai retornar o endereço onde reservou
    printf("Insira o título do livro: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    strcpy(cadastro->livro.titulo, strlwr(temp));
    printf("Insira o autor do livro: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    strcpy(cadastro->livro.autor, strlwr(temp));
    printf("Insira o ISBN do livro [Exemplo 978-85-111-2222-3]: ");
    //implementar função pesquisar para retornar bool informando se tem outro cadastro com o mesmo isbn
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    if(strlen(ISBN) == 17) {
        if(!pesquisarISBN(ISBN)) {
            strcpy(cadastro->livro.isbn, ISBN);
        } else {
            puts("Já existe um livro com esse identificador:");
            imprimirInfo(atual);
            puts("Verifique o estoque e tente novamente");
            return;
        }
    } else {
        puts("Tamanho de ISBN incorreto, tente novamente");
        return;
    }
    printf("Insira quantidade de exemplares tem em estoque desse livro: ");
    fflush(stdin);
    scanf("%d", &cadastro->livro.exemplares);

    //Colocar esse livro como o primeiro da lista colocando o prox apontando para o primeiro de antes
    cadastro->prox = primeiro;
    //Depois coloca no variável global qual é o novo primeiro da lista
    primeiro = cadastro;

    printf("\nLivro cadastrado com sucesso!\n\n");
    return;
}

void retirar(char ISBN[18]) {

    if(primeiro == NULL) {
        return;
    }
    atual = primeiro;
    //Quick Search
    while(strcmp(atual->livro.isbn, ISBN) != 0) {
        //Caso o atual for o ultimo, encerra o programa e retorna falso
        if(atual->prox == NULL) {
            return;
        } else {
            //Guarde o ponteiro atual em anterior
            anterior = atual;
            //Caso o atual não for o ultimo, continue a procurar
            atual = atual->prox;
        }
    }

    if(atual == primeiro) {
        //só esquece o primeiro de antes em memória
        primeiro = primeiro->prox;
    } else {
        //Nesse passo será colocado o próximo do atual, para o próximo do anterior, assim, o anterior vai passar em frente ignorando o atual
        anterior->prox = atual->prox;
    }
    printf("Livro retirado com sucesso:\n");
    imprimirInfo(atual);
    return;
}

int pesquisarISBN(char ISBNPesquisado[18]) {

    atual = primeiro;
    if(atual == NULL)
        return 0;

    //Quick Search
    while(strcmp(atual->livro.isbn, ISBNPesquisado) != 0) {
        //Caso o atual for o ultimo, encerra o programa e retorna falso
        if(atual->prox == NULL)
            return 0;
        else
            atual = atual->prox; //Caso o atual não for o ultimo, continue a procurar
    }
    //Caso saia do while loop significa que o ISBN foi encontrado
    return 1;
}

//Ajeitar para que retorne a string para outras funções
void imprimirInfo(struct NoLivro* l) {
    if(l == NULL) {
        puts("Livro Inválido!");
        return;
    }
    printf("\n===Informações Livro===\nTitulo: %sAutor: %sISBN: %s\nExemplares: %d\n\n", l->livro.titulo, l->livro.autor, l->livro.isbn, l->livro.exemplares);
    return;
}

// https://pt.stackoverflow.com/questions/45642/como-guardar-ler-lista-encadeada-em-arquivo
void salvarInfo(void) {
    //Criar uma função para organizar a lista e inserir aqui antes de salvar para um arquivo
    organizar();
    if(primeiro == NULL) {
        printf("A lista está vazia, nada será salvo.\n");
        return;
    }
    FILE *fp;
    fp = fopen("registro.txt", "w");
    atual = primeiro;

    while(atual->prox != NULL) {
        fprintf(fp, "====\nTitulo: %sAutor: %sISBN: %s\nExemplares: %d\n\n", atual->livro.titulo, atual->livro.autor, atual->livro.isbn, atual->livro.exemplares);
        atual = atual->prox;
    }
    //Descobrir depois pq não ta imprimindo o ultimo da lista...
    fprintf(fp, "====\nTitulo: %sAutor: %sISBN: %s\nExemplares: %d\n\n", atual->livro.titulo, atual->livro.autor, atual->livro.isbn, atual->livro.exemplares);
    puts("Escrito para o disco com êxito!");
    fclose(fp);
    return;
}

void organizar(void) {
    if(primeiro == NULL)
        return;

    int tamanhoLista = 0;
    int i, j, k, x;

    for(atual = primeiro; atual->prox != NULL; atual = atual->prox) {
        tamanhoLista++;
    }
    k = tamanhoLista;
    for(i = 0; i < tamanhoLista - 1; i++, k--) {
        atual = primeiro;
        proximo = atual->prox;
        //Organizar por título, implementar uma organização por escolha do usuário
        for ( j = 1 ; j < k ; j++ ) {
            x = strncmp(atual->livro.titulo, proximo->livro.titulo, 50);
            if (x < 0) {
                temporario = atual->prox;
                atual->prox = proximo->prox;
                proximo->prox = temporario;
            }
            atual = atual->prox;
            proximo = proximo->prox;
        }
    }
}
