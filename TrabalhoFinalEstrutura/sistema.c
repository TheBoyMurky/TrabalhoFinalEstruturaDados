#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include "livros.h"

void sistema(void) {

    int op = 1;
    int recuperadoInfo = 0; //Quando for igual a 1 foi tentado recuperar os registros de registro.dat
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
                if(recuperadoInfo == 0) {
                    recuperarInfo();
                    recuperadoInfo++;
                }
                while(op != 5) {
                    printf("===Estoque===\n1 - Cadastrar novo livro\n2 - Retirar Livro\n3 - Alterar Cadastro Livro\n4 - Listar Livros\n5 - Voltar\n> "); scanf("%d", &op);
                    switch(op) {
                        case 1:
                            cadastrar();
                            break;
                        case 2:
                            retirar();
                            break;
                        case 3:
                            modificarLivro();
                            break;
                        case 4:
                            //Implementar a função de organização para que possa procurar por Autor, título e ISBN
                            listarLivros();
                            break;
                        case 5:
                            break;
                        default:
                            puts("Código inválido");
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
