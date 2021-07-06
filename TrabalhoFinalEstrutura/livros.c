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
typedef struct LivrosEncontrados {
    struct NoLivro* livroE;
    struct LivrosEncontrados* prox;
} LivroEncontrado;

//Ponteiro que ajudar�o em algoritmos de organiza��o
NoLivro* primeiroLivro = NULL;
NoLivro* atualLivro = NULL;
NoLivro* anteriorLivro = NULL;
NoLivro* proximoLivro = NULL;
NoLivro* temporarioLivro = NULL;

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
    if((quant > 0) && (quant < 10)) {
        for(int i = 0; i < quant; i++)
            cadastro->livro.exemplares[i] = 1;
    } else {
        puts("Quantidade inv�lido, n�meros abaixo de 0, 0 e n�meros acima de 10 n�o s�o permitidos");
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
void modificarLivro(void) {
    char ISBN[18];
    char temp[50];
    int quant, op;
    printf("Insira o ISBN a ser alterado: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    if(pesquisarISBN(ISBN)) {
        printf("\nLivro encontrado:");
        imprimirInfo(atualLivro);

        printf("Deseja modificar algum elemento?\n1 - T�tulo\n2 - Autor\n3 - Sair\n");
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("Insira um novo t�tulo: ");
                fflush(stdin);
                fgets(temp, 50, stdin);
                strcpy(atualLivro->livro.titulo, temp);
                break;
            case 2:
                printf("Insira um novo t�tulo: ");
                fflush(stdin);
                fgets(temp, 50, stdin);
                strcpy(atualLivro->livro.autor, temp);
                break;
            case 3:
                break;
            default:
                puts("Valor inserido inv�lido, tente novamente");
        }
        printf("Resultado: ");
        imprimirInfo(atualLivro);
    } else {
        puts("\nLivro n�o encontrado\n");
    }

    return;
}

//N�o consegui fazer retornar um NoLivro, irei ent�o utilizar para resolver condi��o
//retornando 0 para falso e 1 para verdadeiro
//Caso retorne 1 significa que o atualLivro � o Livro encontrado
//A fun��o via utilizar o atualLivro como ponteiro para resolver passar o valor encontrado
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

void listarLivros(void) {
    atualLivro = primeiroLivro;
    if(atualLivro == NULL) {
        printf("A lista est� vazia\n");
        return;
    }
    organizarTitulo();
    while(atualLivro != NULL) { // Isso n�o est� imprimindo o �ltimo da lista
        imprimirInfo(atualLivro);
        atualLivro = atualLivro->prox;
    }
    return;
}

// https://pt.stackoverflow.com/questions/45642/como-guardar-ler-lista-encadeada-em-arquivo
void salvarInfo(void) {
    if(primeiroLivro == NULL) {
        printf("A lista est� vazia, nada ser� salvo.\n");
        return;
    }
    FILE *fp; // File pointer
    fp = fopen("registro.dat", "wb"); // arquivo tem que ter permiss�o w para escrita e b para abrir como binario
    struct Livro LivrosE[50]; // Livros encontrados
    int contador = 0, esc;
    if (fp != NULL) {
        while(atualLivro->prox != NULL) {
            LivrosE[contador] = atualLivro->livro;
            atualLivro = atualLivro->prox;
        }
        esc = fwrite(LivrosE, sizeof(LivrosE), contador, fp); // Fun��o retorna quantidade de elementos escritos
        if (esc == contador)
            printf("Gravacao de registros com sucesso!\n");
        else
            printf("Foram gravados apenas %d elementos\n", esc);
        fclose(fp);
    } else
        puts("Erro na cria��o do arquivo");

    return;
}
void recuperarInfo(void) {
    FILE *fp;
    fp = fopen("registro.dat", "rb");
    struct Livro LivrosE[50];
    int contador = 0, esc;

    if (fp != NULL) {
        esc = fread(LivrosE, sizeof(LivrosE), contador, fp);
        if (esc == contador) {
            printf("Leitura do registro realizado com sucesso\n");
        }
        else
            printf("Foram lidos apenas %d elementos\n", esc);
        fclose(fp);
    }
    else
        puts("Erro: abertura do arquivo");
}

void organizarTitulo(void) {
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
            x = strcmp(atualLivro->livro.titulo, proximoLivro->livro.titulo);
            if (x > 0) {
                temporarioLivro = atualLivro;
                atualLivro->prox = proximoLivro->prox;
                proximoLivro->prox = temporarioLivro;
            }
            atualLivro = atualLivro->prox;
            proximoLivro = proximoLivro->prox;
        }
    }
}
