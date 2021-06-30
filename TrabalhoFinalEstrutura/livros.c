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
typedef struct NoLivros { //typedef � usado para que sempre que declaramos uma variavel do tipo NoLivros, n�o precise ser sempre "struct NoLivros variavel"
    struct Livro livro;
    struct NoLivro* prox;
} NoLivro;
typedef struct NoEncontradoLivros {
    struct Livro encontrado;
    struct NoEncontradoLivro* prox;
} NoEncontradoLivro;


//Ponteiro que ajudar�o em algoritmos de organiza��o
NoLivro* primeiroLivro = NULL;
NoLivro* atualLivro = NULL;
NoLivro* anteriorLivro = NULL;
NoLivro* proximoLivro = NULL;
NoLivro* temporarioLivro = NULL;
//Esse ser� uma array que usaremos para salvar, procurar e organizar
NoEncontradoLivro* livrosE[];

//Colocar um novo livro no in�cio
void cadastrar(void) {
    char ISBN[18];
    char temp[50];
    int quant;
    //Iniciamos um ponteiro do tipo No para receber o endere�o que ser� alocado por malloc de tamanho que cabe a nossa struct No
    NoLivro* cadastro = malloc(sizeof(NoLivro)); //malloc � apenas uma fun��o para reservar um espa�o em mem�ria de tamanho x e vai retornar o endere�o onde reservou
    printf("Insira o t�tulo do livro: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    strcpy(cadastro->livro.titulo, strlwr(temp));
    printf("Insira o autor do livro: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    strcpy(cadastro->livro.autor, strlwr(temp));
    printf("Insira o ISBN do livro [Exemplo 978-85-111-2222-3]: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    if(strlen(ISBN) == 17) {
        if(pesquisarISBN(ISBN) != NULL) {
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

//N�o consegui fazer retornar um NoLivro, irei ent�o utilizar para resolver condi��o
//retornando 0 para falso e 1 para verdadeiro
//Caso retorne 1 significa que o atualLivro � o Livro encontrado
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
void imprimirInfo(NoLivro* l) {
    if(l == NULL) {
        puts("Livro Inv�lido!");
        return;
    }
    //Ajeitar para que consegue imprimir a quantidade em estoque
    printf("\n===Informa��es Livro===\nTitulo: %sAutor: %sISBN: %s\n\n", l->livro.titulo, l->livro.autor, l->livro.isbn);
    return;
}

int quantExemplares(NoLivro *l) {
    int contador = 0;
    for(int i = 0; i < 10; i++) {
        if(l->livro.exemplares[i] == 1)
            contador++;
    }
    return contador;
}

//Terminar de linkar o livro com o cliente
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

void listarLivros(void) {

}

// https://pt.stackoverflow.com/questions/45642/como-guardar-ler-lista-encadeada-em-arquivo
void salvarInfo(void) {
    if(primeiroLivro == NULL) {
        printf("A lista est� vazia, nada ser� salvo.\n");
        return;
    }
    FILE *fp;
    fp = fopen("registro.dat", "wb"); // arquivo tem que ter permiss�o w para escrita e b para abrir como binario
    NoEncontradoLivro LivrosE[50];
    int contador = 0, ret;
    if (fp != NULL) {
        while(atualLivro->prox != NULL) {
            LivrosE[contador].encontrado = atualLivro->livro;
            atualLivro = atualLivro->prox;
        }
        ret = fwrite(LivrosE, sizeof(NoEncontradoLivro), contador, fp);
        if (ret == contador)
            printf("Gravacao de registros com sucesso!\n");
        else
            printf("Foram gravados apenas %d elementos\n", ret);
        fclose(fp);
    } else
        puts("Erro na cria��o do arquivo");

    return;
}

//N�o ta funcionando direito!
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
