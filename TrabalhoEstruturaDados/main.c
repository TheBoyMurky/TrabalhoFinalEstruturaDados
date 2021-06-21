#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

//Provavelmente n vou usar essa fun��o
//int calculaisbn(void);

void sistema(void);
void cadastrar(void);
bool pesquisarISBN(void);
void imprimirInfo();

struct Leitor {

};

struct Livro {
    char titulo[50];
    char autor[50];
    int  exemplares;
    char isbn[18];
};

//Tipos de No
struct NoLivro {
    struct Livro livro;
    struct NoLivro* prox;
};

//Utilizar futuramente
/*
struct NoLeitor {
    struct Leitor leitor;
    struct NoLeitor* prox;
};
//N�s para listas encontradas de autor, ISBN
struct NoEncontrado {
    char encontrado[50];
    struct NoEncontrado* prox;
};
*/

// Essas 2 vari�veis ajudar� nos algoritimos de busca
struct NoLivro* primeiro = NULL;
struct NoLivro* atual = NULL;
struct NoLivro* anterior = NULL;

//Outras vari�vel para n ter que ficar enchendo mem�ria
static char ISBN[18];

int main()
{
    setlocale(LC_ALL, "portuguese-brazilian");
    sistema();
    return 0;
}

void sistema(void) {

    static int op;
    static int saida1 = 4;
    static int saida2 = 3;


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
                            printf("A ser implementado!");
                            break;
                        case 3:

                            if(pesquisarISBN()) {
                                imprimirInfo(atual);
                            } else {
                                puts("Livro n�o encontrado");
                            }
                            break;
                        case 4:
                            break;
                        default:
                            puts("C�digo inv�lido");
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
                            puts("C�digo inv�lido");
                    }
                }
                break;
            case 0:
                break;
            default:
                puts("C�digo inv�lido");
        }
    }

    return;
}

//Colocar um novo livro no in�cio
void cadastrar(void) {

    //Iniciamos um ponteiro do tipo No para receber o endere�o que ser� alocado por malloc de tamanho que cabe a nossa struct No
    struct NoLivro* cadastro = malloc(sizeof(struct NoLivro)); //malloc � apenas uma fun��o para reservar um espa�o em mem�ria de tamanho x e vai retornar o endere�o onde reservou
    printf("Insira o t�tulo do livro: ");
    fflush(stdin);
    fgets(cadastro->livro.titulo, 50, stdin);
    printf("Insira o autor do livro: ");
    fflush(stdin);
    fgets(cadastro->livro.autor, 50, stdin);
    printf("Insira o ISBN do livro [Exemplo 978-85-111-2222-3]: ");
    //implementar fun��o pesquisar para retornar bool informando se tem outro cadastro com o mesmo isbn
    fflush(stdin);
    fgets(cadastro->livro.isbn, 18, stdin);
    printf("Insira quantidade de exemplares tem em estoque desse livro: ");
    fflush(stdin);
    scanf("%d", &cadastro->livro.exemplares);

    //Colocar esse livro como o primeiro da lista colocando o prox apontando para o primeiro de antes
    cadastro->prox = primeiro;
    //Depois coloca no vari�vel global qual � o novo primeiro da lista
    primeiro = cadastro;

    printf("\nLivro cadastrado com exito!\n\n");
    return;
}

void retirar(void) {
    printf("Insira o ISBN do livro para ser retirado de estoque: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);

    if(primeiro == NULL) {
        return;
    }
    atual = primeiro;
    //Quick Search
    while(strcmp(atual->livro.isbn, ISBN) != 0) {
      //Caso o atual for o ultimo, encerra o programa e retorna falso
      if(atual->prox == NULL) {
         return;
      } else {
         //Guarde o ponteiro atual em anterior
         anterior = atual;
         //Caso o atual n�o for o ultimo, continue a procurar
         atual = atual->prox;
      }
   }

   if(atual == primeiro) {
      //s� esquece o primeiro de antes em mem�ria
      primeiro = primeiro->prox;
   } else {
      //Nesse passo ser� colocado o pr�ximo do atual, para o pr�ximo do anterior, assim, o anterior vai passar em frente ignorando o atual
      anterior->prox = atual->prox;
   }

   return;
}

bool pesquisarISBN() {
    printf("Insira o ISBN a ser procurado: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    if(primeiro == NULL) {
        return false;
    }
    atual = primeiro;
    //Quick Search
    while(strcmp(atual->livro.isbn, ISBN) != 0) {
      //Caso o atual for o ultimo, encerra o programa e retorna falso
      if(atual->prox == NULL) {
         return false;
      } else {
         //Caso o atual n�o for o ultimo, continue a procurar
         atual = atual->prox;
      }
   }
   //Caso saia do while loop significa que o ISBN foi encontrado
   return true;
}

//Ajeitar para que possa ler um argumento tipo No
void imprimirInfo(struct NoLivro* l) {
    if(l == NULL) {
        puts("Livro Inv�lido!");
        return;
    }
    printf("\n===Informa��es Livro===\nTitulo: %sAutor: %sISBN: %s\nExemplares: %d\n\n", l->livro.titulo, l->livro.autor, l->livro.isbn, l->livro.exemplares);
    return;
}