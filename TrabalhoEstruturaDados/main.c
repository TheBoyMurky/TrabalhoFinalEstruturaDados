#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

//Implementar para os clientes
struct Leitor {

};
//Implementar para o estoque
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
//Nós para listas encontradas de autor, ISBN
struct NoEncontrado {
    char encontrado[50];
    struct NoEncontrado* prox;
};
*/

//Provavelmente n vou usar essa função
//int calculaisbn(void);

void sistema(void);
void cadastrar(void);
void retirar(char ISBN[18]);
bool pesquisarISBN(char ISBN[18]);
void imprimirInfo(struct NoLivro* l);
void salvarInfo(void);
void organizar(void);

// Essas 3 variáveis ajudará nos algoritimos de busca
struct NoLivro* primeiro = NULL;
struct NoLivro* atual = NULL;
struct NoLivro* anterior = NULL;


int main()
{
    setlocale(LC_ALL, "portuguese-brazilian");
    sistema();
    return 0;
}

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
                                imprimirInfo(atual);
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

//Colocar um novo livro no início
void cadastrar(void) {
    char ISBN[18];
    //Iniciamos um ponteiro do tipo No para receber o endereço que será alocado por malloc de tamanho que cabe a nossa struct No
    struct NoLivro* cadastro = malloc(sizeof(struct NoLivro)); //malloc é apenas uma função para reservar um espaço em memória de tamanho x e vai retornar o endereço onde reservou
    printf("Insira o título do livro: ");
    fflush(stdin);
    fgets(cadastro->livro.titulo, 50, stdin);
    printf("Insira o autor do livro: ");
    fflush(stdin);
    fgets(cadastro->livro.autor, 50, stdin);
    printf("Insira o ISBN do livro [Exemplo 978-85-111-2222-3]: ");
    //implementar função pesquisar para retornar bool informando se tem outro cadastro com o mesmo isbn
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    if(strlen(ISBN) == 17) {
        if(!pesquisarISBN(ISBN)) {
            strcpy(cadastro->livro.isbn, ISBN);
        } else {
            puts("Já existe um livro com esse identificador:");
            imprimirInfo(atual);
            puts("Verifique o estoque e tente novamente");
            return;
        }
    } else {
        puts("Tamanho de ISBN incorreto, tente novamente");
        return;
    }
    printf("Insira quantidade de exemplares tem em estoque desse livro: ");
    fflush(stdin);
    scanf("%d", &cadastro->livro.exemplares);

    //Colocar esse livro como o primeiro da lista colocando o prox apontando para o primeiro de antes
    cadastro->prox = primeiro;
    //Depois coloca no variável global qual é o novo primeiro da lista
    primeiro = cadastro;

    printf("\nLivro cadastrado com exito!\n\n");
    return;
}

void retirar(char ISBN[18]) {

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
            //Caso o atual não for o ultimo, continue a procurar
            atual = atual->prox;
        }
    }

    if(atual == primeiro) {
        //só esquece o primeiro de antes em memória
        primeiro = primeiro->prox;
    } else {
        //Nesse passo será colocado o próximo do atual, para o próximo do anterior, assim, o anterior vai passar em frente ignorando o atual
        anterior->prox = atual->prox;
    }
    printf("Livro retirado com sucesso:\n");
    imprimirInfo(atual);
    return;
}

bool pesquisarISBN(char ISBN[18]) {

    atual = primeiro;
    if(atual == NULL)
        return false;

    //Quick Search
    while(strcmp(atual->livro.isbn, ISBN) != 0) {
        //Caso o atual for o ultimo, encerra o programa e retorna falso
        if(atual->prox == NULL)
            return false;
        else
            atual = atual->prox; //Caso o atual não for o ultimo, continue a procurar
    }
    //Caso saia do while loop significa que o ISBN foi encontrado
    return true;
}

//Ajeitar para que possa ler um argumento tipo No
void imprimirInfo(struct NoLivro* l) {
    if(l == NULL) {
        puts("Livro Inválido!");
        return;
    }
    printf("\n===Informações Livro===\nTitulo: %sAutor: %sISBN: %s\nExemplares: %d\n\n", l->livro.titulo, l->livro.autor, l->livro.isbn, l->livro.exemplares);
    return;
}

void organizar(void) {
    int tamanhoLista = 0;
    for(atual = primeiro; atual->prox != NULL; atual = atual->prox) {
        tamanhoLista++;
    }
}

void salvarInfo(void) {
    //Criar uma função para organizar a lista e inserir aqui antes de salvar para um arquivo

    FILE *fp;
    fp = fopen("registro.txt", "w");
    if(primeiro == NULL) {
        printf("A lista está vazia, tente novamente mais tarde.\n");
        return;
    }

    atual = primeiro;

    while(atual->prox != NULL) {
        fprintf(fp, "====\nTitulo: %sAutor: %sISBN: %s\nExemplares: %d\n\n", atual->livro.titulo, atual->livro.autor, atual->livro.isbn, atual->livro.exemplares);
        atual = atual->prox;
    }
    //Descobrir depois pq não ta imprimindo o ultimo da lista...
    fprintf(fp, "====\nTitulo: %sAutor: %sISBN: %s\nExemplares: %d\n\n", atual->livro.titulo, atual->livro.autor, atual->livro.isbn, atual->livro.exemplares);
    puts("Escrito para o disco com êxito!");
    fclose(fp);
    return;
}
