#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>

void sistema(void) {

    static int op = 9;
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
                while(op != 5) {
                    printf("===Estoque===\n1 - Cadastrar novo livro\n2 - Retirar Livro\n3 - Procurar Livro\n4 - Listar Livros\n5 - Voltar\n> "); scanf("%d", &op);
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
                            //Ser� retornado da fun��o pesquisarISBN para retornar o N�, se n�o for igual a NULL ent�o imprime as informa��es
                            if(pesquisarISBN(ISBN) != NULL) {
                                //imprimirInfo(atual);
                                puts("Livro encontrado");
                            } else {
                                puts("Livro n�o encontrado");
                            }
                            break;
                        case 4:
                            //Implementar a fun��o de organiza��o para que possa procurar por Autor, t�tulo e ISBN
                            puts("Para implementar");
                        case 5:
                            break;
                        default:
                            puts("C�digo inv�lido");
                    }
                }
                break;
            case 2:
                while(op != 3) {
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
                            puts("C�digo inv�lido");
                    }
                }
                break;
            case 0:
                salvarInfo();
                break;
            default:
                puts("C�digo inv�lido");
        }
    }
    return;
}
