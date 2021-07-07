#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include "clientes.h"

//David
//Estrutura do Livro
struct Livro {
    char titulo[50];
    char autor[50];
    //Criar um array para que possa representar cada exemplar
    //em seu pr�prio array, Ex.:
    //3 exemplares = exemplar = { 0, 1, 1, 2 }
    //1 para quando est� em estoque, 0 quando foi emprestado e 2 para quebrar  leitura
    int  exemplares[5];
    //Valor Chave para identifica��o
    char isbn[18];
};

//Limite de t�tulos que pode utilizar para a biblioteca, para essa demonstra��o iremos mostrar com at� 10 t�tulos
#define LIMITEBIBLIOTECA 10

//--Listas Linkadas--
// N� principal
typedef struct NoLivros { //typedef � usado para que sempre que declaramos uma variavel do tipo NoLivros, n�o precise ser sempre "struct NoLivros variavel"
    struct Livro livro;
    struct NoLivro* prox;
} NoLivro;
// N� secund�rio que utilizaremos para fun��es de organiza��o
typedef struct LivrosEncontrados {
    struct NoLivro* livroE;
    struct LivrosEncontrados* prox;
} LivroEncontrado;

//Ponteiro que ajudar�o em algoritmos de organiza��o
//Ponteiros da lista principal
NoLivro* primeiroLivro = NULL;
NoLivro* atualLivro = NULL;
NoLivro* anteriorLivro = NULL;
NoLivro* proximoLivro = NULL;
NoLivro* temporarioLivro1 = NULL;
NoLivro* temporarioLivro2 = NULL;
//Ponteiros da lista organizada
LivroEncontrado* primeiroLivroE = NULL;
LivroEncontrado* atualLivroE = NULL;
LivroEncontrado* proximoLivroE = NULL;

//Artur
//Colocar um novo livro no in�cio
void cadastrar(void) {
    char ISBN[18];
    char temp[50];
    int quant, i;
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
    if((quant > 0) && (quant < 5)) {
        for(i = 0; i < quant; i++)
            cadastro->livro.exemplares[i] = 1;
        if(i != 4)
            cadastro->livro.exemplares[i] = 2;
    } else {
        puts("Quantidade inv�lido, n�meros abaixo de 0, 0 e n�meros acima de 5 n�o s�o permitidos");
        return;
    }
    //Iremos Come�ar a criar uma lista que podemos utilizar para organizar
    LivroEncontrado* cadastroE = malloc(sizeof(LivroEncontrado));
    cadastroE->livroE = cadastro;
    //Colocar esse livro como o primeiro da lista colocando o prox apontando para o primeiro de antes
    cadastro->prox = primeiroLivro;
    cadastroE->prox = primeiroLivroE;
    //Depois coloca no vari�vel global qual � o novo primeiro da lista
    primeiroLivro = cadastro;
    primeiroLivroE = cadastroE;

    printf("\nLivro cadastrado com sucesso!\n\n");

    return;
}

void retirar(void) {
    if(primeiroLivro == NULL) {
        return;
    }
    atualLivro = primeiroLivro;
    char ISBN[18];
    printf("Insira o ISBN a ser retirado: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    if(pesquisarISBN(ISBN)) {
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
        for(int i = 0; i < 5; i++) {
            if(atualLivro->livro.exemplares[i] == 0)
                printf("Esse livro n�o pode ser retirado de estoque pois um exemplar foi emprestado\n");
                //Insirir depois com quem est� o livro
                return;
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

    } else
        puts("N�o foi encontrado um livro com esse ISBN, tente novamente");

    return;
}
void modificarLivro(void) {
    char ISBN[18];
    char temp[50];
    int quant, op, emprestado, estoque, quantEstoque, i;
    printf("Insira o ISBN a ser alterado: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    if(pesquisarISBN(ISBN)) {
        printf("\nLivro encontrado:");
        imprimirInfo(atualLivro);

        printf("Deseja modificar algum elemento?\n1 - T�tulo\n2 - Autor\n3 - Exemplares (Alterar quantos tem em estoque)\n4 - Sair\n");
        printf("> ");
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("Insira um novo t�tulo: ");
                fflush(stdin);
                fgets(temp, 50, stdin);
                strcpy(atualLivro->livro.titulo, strlwr(temp));
                break;
            case 2:
                printf("Insira um novo t�tulo: ");
                fflush(stdin);
                fgets(temp, 50, stdin);
                strcpy(atualLivro->livro.autor, strlwr(temp));
                break;

            case 3:
                emprestado = 0;
                quantEstoque = 0;
                for(i = 0; i < 5; i++) {
                    if(atualLivro->livro.exemplares[i] == 2)
                        break;
                    if(atualLivro->livro.exemplares[i] == 1)
                        quantEstoque++;
                    if(atualLivro->livro.exemplares[i] == 0) {
                        emprestado++;
                        quantEstoque++;
                    }
                }
                estoque = 0;

                if(emprestado == 0) {
                    printf("Quantos est�o em estoque (M�ximo 5): ");
                    scanf("%d", &estoque);
                    if(estoque > 5) {
                        puts("Valor inv�lido, tente novamente");
                        break;
                    }
                    for(i = 0; i < estoque; i++)
                        atualLivro->livro.exemplares[i] = 1;
                    if(estoque != 5)
                        atualLivro->livro.exemplares[i] = 2;
                } else {
                    printf("Alguns livros est�o emprestados no momentos, pode apenas adicionar novos exemplares no estoque, ");
                    printf("quantos voc� vai adicionar ao estoque? No momento tem %d exemplares e o m�ximo � 5: ", quantEstoque-1);
                    scanf("%d", &estoque);
                    if(estoque + quantEstoque > 5) {
                        puts("Valor inv�lido, tente novamente");
                        break;
                    } else {
                        for(i = quantEstoque-1; i < quantEstoque + estoque; i++)
                            atualLivro->livro.exemplares[i] = 1;
                        if(estoque != 5)
                            atualLivro->livro.exemplares[i+1] = 2;
                    }
                }
                break;
            case 4:
                return;
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
    int quantEstoque = 0;
    for(int i = 0; i < 5; i++) {
        if(l->livro.exemplares[i] == 2)
            break;
        if(l->livro.exemplares[i] == 1)
            quantEstoque++;
    }
    printf("\n===Informa��es Livro===\nTitulo: %sAutor: %sISBN: %s\nQuantidade em estoque: %d\n\n", l->livro.titulo, l->livro.autor, l->livro.isbn, quantEstoque);
    return;
}

//Bruno
int retirarExemplar(NoLivro* l) {
    for(int i = 0; i < 5; i++) {
        if(l->livro.exemplares[i] == 2) {
            puts("N�o tem mais exemplares desse livro em estoque\n");
            return 0;
        }

        if(l->livro.exemplares[i] == 1) {
            l->livro.exemplares[i] = 0;
            return 1;
        }
    }
}

void listarLivros(void) {
    if(primeiroLivroE == NULL) {
        printf("A lista est� vazia\n");
        return;
    }
    organizarTitulo();
    atualLivroE = primeiroLivroE;
    while(atualLivroE != NULL) {
        imprimirInfo(atualLivroE->livroE);
        atualLivroE = atualLivroE->prox;
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
    struct Livro LivrosE[LIMITEBIBLIOTECA]; // Livros encontrados
    int contador = 0, esc;
    if (fp != NULL) {
        while(atualLivro->prox != NULL) {
            LivrosE[contador] = atualLivro->livro;
            atualLivro = atualLivro->prox;
            contador++;
        }
        esc = fwrite(LivrosE, sizeof(LivrosE), LIMITEBIBLIOTECA, fp); // Fun��o retorna quantidade de elementos escritos
        if (esc == contador)
            printf("Gravacao de registros com sucesso!\n");
        else
            printf("Erro na grava��o de registro!\n");
        fclose(fp);
    } else
        puts("Erro na cria��o do arquivo");

    return;
}
void recuperarInfo(void) {
    FILE *fp;
    fp = fopen("registro.dat", "rb");
    struct Livro LivrosE[LIMITEBIBLIOTECA];
    int esc;

    if (fp != NULL) {
        esc = fread(LivrosE, sizeof(LivrosE), LIMITEBIBLIOTECA, fp);
        if (esc > 0) {
            for (int i = 0; i < esc; i++) {
                NoLivro* reCadastro = malloc(sizeof(NoLivro));
                strcpy(reCadastro->livro.titulo, LivrosE[i].titulo);
                strcpy(reCadastro->livro.autor, LivrosE[i].autor);
                if(primeiroLivro == NULL)
                    primeiroLivro = reCadastro;
                if(anteriorLivro == NULL) {
                    anteriorLivro = reCadastro;
                    continue;
                } else {
                    anteriorLivro->prox = reCadastro;
                    anteriorLivro = reCadastro;
                }
            }
            printf("Leitura do registro realizado com sucesso\n");
        }
        else
            printf("N�o h� registros anteriores para recuperar\n");

        fclose(fp);
    }
    else
        puts("\nN�o h� arquivo de registros anteriores\n");
}

/*
// Redefinir o primeiroLivro no final pois est� excluindo na hora de listar
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
*/
//Organizar corrigido
void organizarTitulo(void) {
    if(primeiroLivroE == NULL)
        return;

    int tamanhoLista = 0;
    int i, j, k, x;

    for(atualLivroE = primeiroLivroE; atualLivroE != NULL; atualLivroE = atualLivroE->prox) {
        tamanhoLista++;
    }

    k = tamanhoLista;

    for ( i = 0 ; i < tamanhoLista - 1 ; i++, k-- ) {
        atualLivroE = primeiroLivroE;
        proximoLivroE = atualLivroE->prox;

        for ( j = 1 ; j < k ; j++ ) {
            //Para que podemos referenciar o Livro na lista de livros organizados "LivrosE", temos que jogar eles
            //para uma vari�vel tempor�rio, nesse caso usaremos o temporarioLivro1 e temporarioLivro2
            temporarioLivro1 = atualLivroE->livroE;
            temporarioLivro2 = proximoLivroE->livroE;
            //Quando compara com strncmp se o primeiro string for igual ao segundo o valor retornado ser� 0
            //Quando o primeiro string for maior que o segundo o valor retornado ser� 1 ( > 0)
            //Quando o primeiro string for menor que o segundo o valor retornado ser� -1 ( < 0)
            int valorComparacao = strncmp(temporarioLivro1->livro.titulo, temporarioLivro2->livro.titulo, 50);
            if ( valorComparacao > 0 ) {
                atualLivroE->livroE = temporarioLivro2;
                proximoLivroE->livroE = temporarioLivro1;
            }

            atualLivroE = atualLivroE->prox;
            proximoLivroE = proximoLivroE->prox;
         }
    }
}

