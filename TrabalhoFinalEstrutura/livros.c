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
    //em seu próprio array, Ex.:
    //3 exemplares = exemplar = { 0, 1, 1 }
    //1 para quando está em estoque e 0 quando foi emprestado
    int  exemplares[10];
    //Valor Chave para identificação
    char isbn[18];
};
//Listas Linkadas
typedef struct NoLivros { //typedef é usado para que sempre que declaramos uma variavel do tipo NoLivros, não precise ser sempre "struct NoLivros variavel"
    struct Livro livro;
    struct NoLivro* prox;
} NoLivro;
typedef struct LivrosEncontrados {
    struct NoLivro* livroE;
    struct LivrosEncontrados* prox;
} LivroEncontrado;

//Ponteiro que ajudarão em algoritmos de organização
NoLivro* primeiroLivro = NULL;
NoLivro* atualLivro = NULL;
NoLivro* anteriorLivro = NULL;
NoLivro* proximoLivro = NULL;
NoLivro* temporarioLivro = NULL;

//Colocar um novo livro no início
void cadastrar(void) {
    char ISBN[18];
    char temp[50];
    int quant;
    //Iniciamos um ponteiro do tipo No para receber o endereço que será alocado por malloc de tamanho que cabe a nossa struct No
    NoLivro* cadastro = malloc(sizeof(NoLivro)); //malloc é apenas uma função para reservar um espaço em memória de tamanho x e vai retornar o endereço onde reservou
    printf("Insira o título do livro: ");
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
            puts("Já existe um livro com esse identificador:");
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
        puts("Quantidade inválido, números abaixo de 0, 0 e números acima de 10 não são permitidos");
        return;
    }



    //Colocar esse livro como o primeiro da lista colocando o prox apontando para o primeiro de antes
    cadastro->prox = primeiroLivro;
    //Depois coloca no variável global qual é o novo primeiro da lista
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
            //Caso o atual não for o ultimo, continue a procurar
            atualLivro = atualLivro->prox;
        }
    }

    if(atualLivro == primeiroLivro) {
        //só esquece o primeiro de antes em memória
        primeiroLivro = primeiroLivro->prox;
    } else {
        //Nesse passo será colocado o próximo do atual, para o próximo do anterior, assim, o anterior vai passar em frente ignorando o atual
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

        printf("Deseja modificar algum elemento?\n1 - Título\n2 - Autor\n3 - Sair\n");
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("Insira um novo título: ");
                fflush(stdin);
                fgets(temp, 50, stdin);
                strcpy(atualLivro->livro.titulo, temp);
                break;
            case 2:
                printf("Insira um novo título: ");
                fflush(stdin);
                fgets(temp, 50, stdin);
                strcpy(atualLivro->livro.autor, temp);
                break;
            case 3:
                break;
            default:
                puts("Valor inserido inválido, tente novamente");
        }
        printf("Resultado: ");
        imprimirInfo(atualLivro);
    } else {
        puts("\nLivro não encontrado\n");
    }

    return;
}

//Não consegui fazer retornar um NoLivro, irei então utilizar para resolver condição
//retornando 0 para falso e 1 para verdadeiro
//Caso retorne 1 significa que o atualLivro é o Livro encontrado
//A função via utilizar o atualLivro como ponteiro para resolver passar o valor encontrado
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
            atualLivro = atualLivro->prox; //Caso o atual não for o ultimo, continue a procurar
    }
    //Caso saia do while loop significa que o ISBN foi encontrado
    return 1;
}

//Ajeitar para que retorne a string para outras funções
void imprimirInfo(NoLivro* l) {
    if(l == NULL) {
        puts("Livro Inválido!");
        return;
    }
    //Ajeitar para que consegue imprimir a quantidade em estoque
    printf("\n===Informações Livro===\nTitulo: %sAutor: %sISBN: %s\n\n", l->livro.titulo, l->livro.autor, l->livro.isbn);
    return;
}

void listarLivros(void) {
    atualLivro = primeiroLivro;
    if(atualLivro == NULL) {
        printf("A lista está vazia\n");
        return;
    }
    organizarTitulo();
    while(atualLivro != NULL) { // Isso não está imprimindo o último da lista
        imprimirInfo(atualLivro);
        atualLivro = atualLivro->prox;
    }
    return;
}

// https://pt.stackoverflow.com/questions/45642/como-guardar-ler-lista-encadeada-em-arquivo
void salvarInfo(void) {
    if(primeiroLivro == NULL) {
        printf("A lista está vazia, nada será salvo.\n");
        return;
    }
    FILE *fp; // File pointer
    fp = fopen("registro.dat", "wb"); // arquivo tem que ter permissão w para escrita e b para abrir como binario
    struct Livro LivrosE[50]; // Livros encontrados
    int contador = 0, esc;
    if (fp != NULL) {
        while(atualLivro->prox != NULL) {
            LivrosE[contador] = atualLivro->livro;
            atualLivro = atualLivro->prox;
        }
        esc = fwrite(LivrosE, sizeof(LivrosE), contador, fp); // Função retorna quantidade de elementos escritos
        if (esc == contador)
            printf("Gravacao de registros com sucesso!\n");
        else
            printf("Foram gravados apenas %d elementos\n", esc);
        fclose(fp);
    } else
        puts("Erro na criação do arquivo");

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
        //Organizar por título, implementar uma organização por escolha do usuário
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
