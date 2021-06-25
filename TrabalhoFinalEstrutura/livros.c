#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include "clientes.h"

//Estrutura do Livro
struct Livro {
    char titulo[50];
    char autor[50];
    //Criar um array para que possa representar cada exemplar
    //em seu pr�prio array, Ex.:
    //3 exemplares = exemplar = { 0, 1, 1 }
    //1 para quando est� em estoque e 0 quando foi emprestado
    int  exemplares[10];
    //Valor Chave para identifica��o
    char isbn[18];
};
//Listas Linkadas
struct NoLivro {
    struct Livro livro;
    struct NoLivro* prox;
};
struct NoEncontradoLivro {
    struct NoLivro* encontrado;
    struct NoEncontradoLivro* prox;
};
//Talvez criar uma lista para um registro de emprestimo, d�vida, etc.
//struct Registros;

//Ponteiro que ajudar�o em algoritmos de organiza��o
struct NoLivro* primeiroLivro = NULL;
struct NoLivro* atualLivro = NULL;
struct NoLivro* anteriorLivro = NULL;
struct NoLivro* proximoLivro = NULL;
struct NoLivro* temporarioLivro = NULL;

//Colocar um novo livro no in�cio
void cadastrar(void) {
    char ISBN[18];
    char temp[50];
    int quant;
    //Iniciamos um ponteiro do tipo No para receber o endere�o que ser� alocado por malloc de tamanho que cabe a nossa struct No
    struct NoLivro* cadastro = malloc(sizeof(struct NoLivro)); //malloc � apenas uma fun��o para reservar um espa�o em mem�ria de tamanho x e vai retornar o endere�o onde reservou
    printf("Insira o t�tulo do livro: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    strcpy(cadastro->livro.titulo, strlwr(temp));
    printf("Insira o autor do livro: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    strcpy(cadastro->livro.autor, strlwr(temp));
    printf("Insira o ISBN do livro [Exemplo 978-85-111-2222-3]: ");
    //implementar fun��o pesquisar para retornar bool informando se tem outro cadastro com o mesmo isbn
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    if(strlen(ISBN) == 17) {
        if(!pesquisarISBN(ISBN)) {
            strcpy(cadastro->livro.isbn, ISBN);
        } else {
            puts("J� existe um livro com esse identificador:");
            imprimirInfo(atualLivro);
            puts("Verifique o estoque e tente novamente");
            return;
        }
    } else {
        puts("Tamanho de ISBN incorreto, tente novamente");
        return;
    }
    printf("Insira quantidade de exemplares tem em estoque desse livro: ");
    fflush(stdin);
    scanf("%d", &quant);
    if((quant > 0) && !(quant > 10)) {
        for(int i = 0; i < quant; i++)
            cadastro->livro.exemplares[i] = 1;
    } else {
        puts("Quantidade inv�lido, n�meros abaixo de 0, 0 ou n�meros acima de 10 n�o s�o permitidos");
        return;
    }



    //Colocar esse livro como o primeiro da lista colocando o prox apontando para o primeiro de antes
    cadastro->prox = primeiroLivro;
    //Depois coloca no vari�vel global qual � o novo primeiro da lista
    primeiroLivro = cadastro;

    printf("\nLivro cadastrado com sucesso!\n\n");
    return;
}

void retirar(char ISBN[18]) {

    if(primeiroLivro == NULL) {
        return;
    }
    atualLivro = primeiroLivro;
    //Quick Search
    while(strcmp(atualLivro->livro.isbn, ISBN) != 0) {
        //Caso o atual for o ultimo, encerra o programa e retorna falso
        if(atualLivro->prox == NULL) {
            return;
        } else {
            //Guarde o ponteiro atual em anterior
            anteriorLivro = atualLivro;
            //Caso o atual n�o for o ultimo, continue a procurar
            atualLivro = atualLivro->prox;
        }
    }

    if(atualLivro == primeiroLivro) {
        //s� esquece o primeiro de antes em mem�ria
        primeiroLivro = primeiroLivro->prox;
    } else {
        //Nesse passo ser� colocado o pr�ximo do atual, para o pr�ximo do anterior, assim, o anterior vai passar em frente ignorando o atual
        anteriorLivro->prox = atualLivro->prox;
    }
    printf("Livro retirado com sucesso:\n");
    imprimirInfo(atualLivro);
    return;
}

//Implementar para retornar o No encontrado
int pesquisarISBN(char ISBNPesquisado[18]) {

    atualLivro = primeiroLivro;
    if(atualLivro == NULL)
        return 0;

    //Quick Search
    while(strcmp(atualLivro->livro.isbn, ISBNPesquisado) != 0) {
        //Caso o atual for o ultimo, encerra o programa e retorna falso
        if(atualLivro->prox == NULL)
            return 0;
        else
            atualLivro = atualLivro->prox; //Caso o atual n�o for o ultimo, continue a procurar
    }
    //Caso saia do while loop significa que o ISBN foi encontrado
    return 1;
}

//Ajeitar para que retorne a string para outras fun��es
void imprimirInfo(struct NoLivro* l) {
    if(l == NULL) {
        puts("Livro Inv�lido!");
        return;
    }
    printf("\n===Informa��es Livro===\nTitulo: %sAutor: %sISBN: %s\nExemplares: %d\n\n", l->livro.titulo, l->livro.autor, l->livro.isbn, quantExemplares(l));
    return;
}

int quantExemplares(struct NoLivro *l) {
    int contador = 0;
    for(int i = 0; i < 10; i++) {
        if(l->livro.exemplares[i] == 1)
            contador++;
    }
    return contador;
}

void emprestarLivro(void) {
    char ISBN[18], ID[9];
    printf("Insira o ISBN do livro que ser� emprestado: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    printf("Insira o ID do cliente que ser� emprestado o livro: ");
    fflush(stdin);
    fgets(ID, 18, stdin);
    return;
}

// https://pt.stackoverflow.com/questions/45642/como-guardar-ler-lista-encadeada-em-arquivo
void salvarInfo(void) {
    //Criar uma fun��o para organizar a lista e inserir aqui antes de salvar para um arquivo
    organizar();
    if(primeiroLivro == NULL) {
        printf("A lista est� vazia, nada ser� salvo.\n");
        return;
    }
    FILE *fp;
    fp = fopen("registro.txt", "w");
    atualLivro = primeiroLivro;

    while(atualLivro->prox != NULL) {
        fprintf(fp, "====\nTitulo: %sAutor: %sISBN: %s\nExemplares: %d\n\n", atualLivro->livro.titulo, atualLivro->livro.autor, atualLivro->livro.isbn, atualLivro->livro.exemplares);
        atualLivro = atualLivro->prox;
    }
    //Descobrir depois pq n�o ta imprimindo o ultimo da lista...
    fprintf(fp, "====\nTitulo: %sAutor: %sISBN: %s\nExemplares: %d\n\n", atualLivro->livro.titulo, atualLivro->livro.autor, atualLivro->livro.isbn, atualLivro->livro.exemplares);
    puts("Escrito para o disco com �xito!");
    fclose(fp);
    return;
}

void organizar(void) {
    if(primeiroLivro == NULL)
        return;

    int tamanhoLista = 0;
    int i, j, k, x;

    for(atualLivro = primeiroLivro; atualLivro->prox != NULL; atualLivro = atualLivro->prox) {
        tamanhoLista++;
    }
    k = tamanhoLista;
    for(i = 0; i < tamanhoLista - 1; i++, k--) {
        atualLivro = primeiroLivro;
        proximoLivro = atualLivro->prox;
        //Organizar por t�tulo, implementar uma organiza��o por escolha do usu�rio
        for ( j = 1 ; j < k ; j++ ) {
            x = strncmp(atualLivro->livro.titulo, proximoLivro->livro.titulo, 50);
            if (x < 0) {
                temporarioLivro = atualLivro->prox;
                atualLivro->prox = proximoLivro->prox;
                proximoLivro->prox = temporarioLivro;
            }
            atualLivro = atualLivro->prox;
            proximoLivro = proximoLivro->prox;
        }
    }
}
