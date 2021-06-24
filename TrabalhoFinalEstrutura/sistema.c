#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>

void sistema(void) {

    static int op = 9;
    static int saida1 = 4;
    static int saida2 = 3;
    char ISBN[18];

    while(op != 0) {
        printf("\n ===Sistema Biblioteca===\n");
        printf("1 - Estoque Livro\n");
        printf("2 - Cadastro Cliente\n");
        printf("0 - Sair\n");
        printf("> ");
        scanf("%d", &op);

        switch(op) {
            case 1:
                while(op != saida1) {
                    printf("===Estoque===\n1 - Cadastrar novo livro\n2 - Retirar Livro\n3 - Procurar Livro\n4 - Voltar\n> "); scanf("%d", &op);
                    switch(op) {
                        case 1:
                            cadastrar();
                            break;
                        case 2:
                            printf("Insira o ISBN do livro a ser retirado: ");
                            fflush(stdin);
                            fgets(ISBN, 18, stdin);
                            retirar(ISBN);
                            break;
                        case 3:
                            printf("Insira o ISBN a ser pesquisado: ");
                            fflush(stdin);
                            fgets(ISBN, 18, stdin);
                            if(pesquisarISBN(ISBN)) {
                                //imprimirInfo(atual);
                                puts("Livro encontrado");
                            } else {
                                puts("Livro não encontrado");
                            }
                            break;
                        case 4:
                            break;
                        default:
                            puts("Código inválido");
                    }
                }
                break;
            case 2:
                while(op != saida2) {
                    printf("1 - Cadastrar novo cliente\n2 - Emprestimo Livro\n3 - Voltar\n> "); scanf("%d", &op);
                    switch(op) {
                        case 1:
                            printf("A ser implementado!");
                            break;
                        case 2:
                            printf("A ser implementado!");
                            break;
                        case 3:
                            break;
                        default:
                            puts("Código inválido");
                    }
                }
                break;
            case 0:
                salvarInfo();
                break;
            default:
                puts("Código inválido");
        }
    }
    return;
}
