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
//Ponteiro que ajudarão em algoritmos de organização
struct NoLeitor* primeiroLeitor = NULL;
struct NoLeitor* atualLeitor = NULL;
struct NoLeitor* anteriorLeitor = NULL;
struct NoLeitor* proximoLeitor = NULL;
struct NoLeitor* temporarioLeitor = NULL;


// Funções
void cadastrarCliente(void) {
    //Inicializa as variáveis iniciais
    char ID[10];
    //Iniciamos um ponteiro do tipo NoLeitor chamado cadastro para receber o endereço que será alocado por malloc
    //de tamanho que cabe a nossa struct NoLeitor
    struct NoLeitor* cadastro = malloc(sizeof(struct NoLeitor));
    //Requisito de informações básicas
    printf("Insira o nome completo do cliente: ");
    fflush(stdin);
    fgets(cadastro->leitor.nome, 80, stdin);
    printf("Insira o id do cliente [Exemplo ABCD-1234]: ");
    fflush(stdin);
    fgets(ID, 10, stdin);
    //Verificação de formatação
    if(strlen(ID) == 9) {
        if(!pesquisarID(ID)) { //Verificação de que se ja existe um cliente com esse ID
            strcpy(cadastro->leitor.id, ID);
        } else {
            puts("Já existe um cadastro com esse identificador:");
            return;
        }
    } else {
        puts("ID incorreto, tente novamente");
        return;
    }
    //Colocar esse cliente como o primeiro da lista colocando o "prox" para o primeiro de antes
    cadastro->prox = primeiroLeitor;
    //E troca o ponteiro do primeiro da lista para o novo cadastro
    primeiroLeitor = cadastro;
    printf("\nCliente cadastrado com sucesso!\n\n");
    return;
}

// Luiz
//Função Booleana, retorna 1 caso encontre ou 0 caso não encontre
int pesquisarID(char IDPesquisado[18]) {

    //Verifica se a lista de clientes não está vazio
    if(primeiroLeitor == NULL)
        return 0;
     atualLeitor = primeiroLeitor;

    //Quick Search
    while(strcmp(atualLeitor->leitor.id, IDPesquisado) != 0) {
        //Caso o atual for o ultimo, encerra o programa e retorna falso
        if(atualLeitor->prox == NULL)
            return 0;
        else
            atualLeitor = atualLeitor->prox; //Caso o atual não for o ultimo, continue a procurar
    }
    //Caso saia do while loop significa que o ISBN foi encontrado
    return 1;
}

void emprestarLivro(void) {

    //Inicializa as variáveis iniciais
    char ISBN[18], ID[9];
    int i = 0;

    //Pede os valores chaves (ID para o cliente e ISBN para o livro)
    printf("Insira o ID do cliente que será emprestado o livro: ");
    fflush(stdin);
    fgets(ID, 18, stdin);
    printf("Insira o ISBN do livro que será emprestado: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    //Verifica se existe o ISBN para os livros e o ID para os clientes
    if(pesquisarISBN(ISBN)) {
        if(!pesquisarID(ID)) {
            for(i; i <= 3; i++) {
                if(i == 3) {
                    //Caso o for loop chegue em 3 significa que está com o array de livros emprestados cheios,
                    //avisa o cliente e finaliza a função
                    printf("Cliente ja tem 3 livros que foram emprestados, faça uma devolução para que possa levara outro livro");
                    return;
                }
                //Encontra o primeiro do array de livros emprestado que está em nulo e coloca o endereço no lugar
                if(atualLeitor->leitor.livrosEmprestados[i] == NULL) {
                    if(retirarExemplar(atualLivro)) {
                        atualLeitor->leitor.livrosEmprestados[i] = atualLivro;
                        printf("Livro emprestado com sucesso\n\n");
                        return;
                    }
                }
            }
        } else {
            printf("Não existe um cliente com esse ID, tente novamente\n");
        }
    } else {
        printf("Não foi encontrado um livro com esse ISBN, tente novamente mais tarde\n");
    }
    return;
}

void devolverLivro(void) {
    //Inicializa as variáveis iniciais
    char ISBN[18], ID[9];
    int i = 0;

    //Pede os valores chaves (ID para o cliente e ISBN para o livro)
    printf("Insira o ID do cliente que devolverá o livro: ");
    fflush(stdin);
    fgets(ID, 18, stdin);
    printf("Insira o ISBN do livro que será devolvido: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    //Verifica se existe o ISBN para os livros e o ID para os clientes
    if(pesquisarISBN(ISBN)) {
        if(!pesquisarID(ID)) {
            for(i; i <= 3; i++) {
                if(i == 3) {
                    //Caso o for loop chegue em 3 significa que não foi emprestado um livro para esse cliente com essa ISBN
                    printf("Não foi emprestado para o cliente um livro com esse ISBN, tente novamente\n");
                    return;
                }
                //Utiliza a função devolverExemplar para ajustar os exemplares do array
                if(atualLeitor->leitor.livrosEmprestados[i] == atualLivro) {
                    if(devolverExemplar(atualLivro)) {
                        atualLeitor->leitor.livrosEmprestados[i] = NULL;
                        printf("Livro devolvido com sucesso\n\n");
                        return;
                    }
                }
            }
        } else {
            printf("Não existe um cliente com esse ID, tente novamente\n");
        }
    } else {
        printf("Não foi encontrado um livro com esse ISBN, tente novamente mais tarde\n");
    }

    return;
}
