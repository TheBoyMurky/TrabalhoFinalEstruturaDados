#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include "livros.h"

//Alyssonn
//Struct Leitor
struct Leitor {
    char nome[80];
    //Valor Chave
    //Ex.: AAAA-1111
    char id[9];
    struct NoLivro* livrosEmprestados[3];
};
//Listas Linkadas
struct NoLeitor {
    struct Leitor leitor;
    struct NoLeitor* prox;
};
struct NoLeitorEncontrado {
    struct Leitor* leitor;
    struct NoLeitorEncontrado* prox;
};
//Ponteiro que ajudar�o em algoritmos de organiza��o
struct NoLeitor* primeiroLeitor = NULL;
struct NoLeitor* atualLeitor = NULL;
struct NoLeitor* anteriorLeitor = NULL;
struct NoLeitor* proximoLeitor = NULL;
struct NoLeitor* temporarioLeitor = NULL;


// Fun��es
void cadastrarCliente(void) {
    char ID[10];
    struct NoLeitor* cadastro = malloc(sizeof(struct NoLeitor));
    printf("Insira o nome completo do cliente: ");
    fflush(stdin);
    fgets(cadastro->leitor.nome, 80, stdin);
    printf("Insira o id do cliente [Exemplo ABCD-1234]: ");
    fflush(stdin);
    fgets(ID, 10, stdin);
    if(strlen(ID) == 9) {
        if(!pesquisarID(ID)) {
            strcpy(cadastro->leitor.id, ID);
        } else {
            puts("J� existe um cadastro com esse identificador:");
            return;
        }
    } else {
        puts("ID incorreto, tente novamente");
        return;
    }
    cadastro->prox = primeiroLeitor;
    primeiroLeitor = cadastro;
    printf("\nCliente cadastrado com sucesso!\n\n");
    return;
}

// Luiz
//Fun��o Booleana, retorna 1 caso encontre ou 0 caso n�o encontre
int pesquisarID(char IDPesquisado[18]) {

    atualLeitor = primeiroLeitor;
    if(atualLeitor == NULL)
        return 0;

    //Quick Search
    while(strcmp(atualLeitor->leitor.id, IDPesquisado) != 0) {
        //Caso o atual for o ultimo, encerra o programa e retorna falso
        if(atualLeitor->prox == NULL)
            return 0;
        else
            atualLeitor = atualLeitor->prox; //Caso o atual n�o for o ultimo, continue a procurar
    }
    //Caso saia do while loop significa que o ISBN foi encontrado
    return 1;
}

//Terminar de linkar o livro com o cliente
void emprestarLivro(void) {
    char ISBN[18], ID[9];
    int i = 0;

    printf("Insira o ID do cliente que ser� emprestado o livro: ");
    fflush(stdin);
    fgets(ID, 18, stdin);
    printf("Insira o ISBN do livro que ser� emprestado: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    if(!pesquisarISBN(ISBN)) {
        if(!pesquisarID(ID)) {
            for(i; i <= 3; i++) {
                if(i == 3) {
                    printf("Cliente ja tem 3 livros que foram emprestados, fa�a uma devolu��o para que possa levara outro livro");
                    return;
                }
                if(atualLeitor->leitor.livrosEmprestados[i] == NULL) {
                    if(retirarExemplar(atualLivro) == 1) {
                        atualLeitor->leitor.livrosEmprestados[i] = &atualLivro;
                        printf("Livro emprestado com sucesso\n");
                        return;
                    }
                }
            }
        } else {
            printf("N�o existe um cliente com esse ID, tente novamente\n");
        }
    } else {
        printf("N�o foi encontrado um livro com esse ISBN, tente novamente mais tarde\n");
    }
    return;
}

void devolverLivro(void) {
    char ISBN[18], ID[9];
    int i = 0;

    printf("Insira o ID do cliente que ser� emprestado o livro: ");
    fflush(stdin);
    fgets(ID, 18, stdin);
    printf("Insira o ISBN do livro que ser� emprestado: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    if(!pesquisarISBN(ISBN)) {
        if(!pesquisarID(ID)) {
            for(i; i <= 3; i++) {
                if(i == 3) {
                    printf("N�o foi emprestado para o cliente um livro com esse ISBN, tente novamente");
                    return;
                }
                if(atualLeitor->leitor.livrosEmprestados[i] == atualLivro) {
                    if(devolverExemplar(atualLivro) == 1) {
                        atualLeitor->leitor.livrosEmprestados[i] = NULL;
                        printf("Livro devolvido com sucesso\n");
                        return;
                    }
                }
            }
        } else {
            printf("N�o existe um cliente com esse ID, tente novamente\n");
        }
    } else {
        printf("N�o foi encontrado um livro com esse ISBN, tente novamente mais tarde\n");
    }

    return;
}
