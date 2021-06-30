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
    //em seu próprio array, Ex.:
    //3 exemplares = exemplar = { 0, 1, 1 }
    //1 para quando está em estoque e 0 quando foi emprestado
    int  exemplares[10];
    //Valor Chave para identificação
    char isbn[18];
};
//Listas Linkadas
typedef struct NoLivros { //typedef é usado para que sempre que declaramos uma variavel do tipo NoLivros, não precise ser sempre "struct NoLivros variavel"
    struct Livro livro;
    struct NoLivro* prox;
} NoLivro;
typedef struct NoEncontradoLivros {
    struct Livro encontrado;
    struct NoEncontradoLivro* prox;
} NoEncontradoLivro;


//Ponteiro que ajudarão em algoritmos de organização
NoLivro* primeiroLivro = NULL;
NoLivro* atualLivro = NULL;
NoLivro* anteriorLivro = NULL;
NoLivro* proximoLivro = NULL;
NoLivro* temporarioLivro = NULL;
//Esse será uma array que usaremos para salvar, procurar e organizar
NoEncontradoLivro* livrosE[];

//Colocar um novo livro no início
void cadastrar(void) {
    char ISBN[18];
    char temp[50];
    int quant;
    //Iniciamos um ponteiro do tipo No para receber o endereço que será alocado por malloc de tamanho que cabe a nossa struct No
    NoLivro* cadastro = malloc(sizeof(NoLivro)); //malloc é apenas uma função para reservar um espaço em memória de tamanho x e vai retornar o endereço onde reservou
    printf("Insira o título do livro: ");
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
            puts("Já existe um livro com esse identificador:");
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
        puts("Quantidade inválido, números abaixo de 0, 0 ou números acima de 10 não são permitidos");
        return;
    }



    //Colocar esse livro como o primeiro da lista colocando o prox apontando para o primeiro de antes
    cadastro->prox = primeiroLivro;
    //Depois coloca no variável global qual é o novo primeiro da lista
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
            //Caso o atual não for o ultimo, continue a procurar
            atualLivro = atualLivro->prox;
        }
    }

    if(atualLivro == primeiroLivro) {
        //só esquece o primeiro de antes em memória
        primeiroLivro = primeiroLivro->prox;
    } else {
        //Nesse passo será colocado o próximo do atual, para o próximo do anterior, assim, o anterior vai passar em frente ignorando o atual
        anteriorLivro->prox = atualLivro->prox;
    }
    printf("Livro retirado com sucesso:\n");
    imprimirInfo(atualLivro);
    return;
}

//Não consegui fazer retornar um NoLivro, irei então utilizar para resolver condição
//retornando 0 para falso e 1 para verdadeiro
//Caso retorne 1 significa que o atualLivro é o Livro encontrado
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
            atualLivro = atualLivro->prox; //Caso o atual não for o ultimo, continue a procurar
    }
    //Caso saia do while loop significa que o ISBN foi encontrado
    return 1;
}

//Ajeitar para que retorne a string para outras funções
void imprimirInfo(NoLivro* l) {
    if(l == NULL) {
        puts("Livro Inválido!");
        return;
    }
    //Ajeitar para que consegue imprimir a quantidade em estoque
    printf("\n===Informações Livro===\nTitulo: %sAutor: %sISBN: %s\n\n", l->livro.titulo, l->livro.autor, l->livro.isbn);
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
    printf("Insira o ISBN do livro que será emprestado: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    printf("Insira o ID do cliente que será emprestado o livro: ");
    fflush(stdin);
    fgets(ID, 18, stdin);
    return;
}

void listarLivros(void) {

}

// https://pt.stackoverflow.com/questions/45642/como-guardar-ler-lista-encadeada-em-arquivo
void salvarInfo(void) {
    if(primeiroLivro == NULL) {
        printf("A lista está vazia, nada será salvo.\n");
        return;
    }
    FILE *fp;
    fp = fopen("registro.dat", "wb"); // arquivo tem que ter permissão w para escrita e b para abrir como binario
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
        puts("Erro na criação do arquivo");

    return;
}

//Não ta funcionando direito!
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
        //Organizar por título, implementar uma organização por escolha do usuário
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
