#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include "livros.h"

//Struct Leitor
struct Leitor {
    char nome[80];
    //Valor Chave
    //Ex.: AAAA-1234
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
    char ID[9];
    struct NoLeitor* cadastro = malloc(sizeof(struct NoLeitor));
    printf("Insira o nome completo do cliente: ");
    fflush(stdin);
    fgets(cadastro->leitor.nome, 80, stdin);
    printf("Insira o id do cliente [Exemplo ABCD-1234]: ");
    fflush(stdin);
    fgets(ID, 9, stdin);
    if(strlen(ID) == 9) {
        if(pesquisarID(ID)) {
            strcpy(cadastro->leitor.id, ID);
        } else {
            puts("Já existe um cadastro com esse identificador:");
            return;
        }
    } else {
        puts("Tamanho de ISBN incorreto, tente novamente");
        return;
    }
}


//Função Booleana, retorna 1 caso encontre ou 0 caso não encontre
//Implementar que retorne o No encontrado, caso não encontre retorne NULL
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
            atualLeitor = atualLeitor->prox; //Caso o atual não for o ultimo, continue a procurar
    }
    //Caso saia do while loop significa que o ISBN foi encontrado
    return 1;
}
