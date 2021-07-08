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
    //em seu próprio array, Ex.:
    //3 exemplares = exemplar = { 0, 1, 1, 2 }
    //1 para quando está em estoque, 0 quando foi emprestado e 2 para quebrar  leitura
    int  exemplares[5];
    //Valor Chave para identificação
    char isbn[18];
};

//Limite de títulos que pode utilizar para a biblioteca, para essa demonstração iremos mostrar com até 10 títulos
#define LIMITEBIBLIOTECA 10

//--Listas Linkadas--
// Nó principal
typedef struct NoLivros { //typedef é usado para que sempre que declaramos uma variavel do tipo NoLivros, não precise ser sempre "struct NoLivros variavel"
    struct Livro livro;
    struct NoLivro* prox;
} NoLivro;
// Nó secundário que utilizaremos para funções de organização
typedef struct LivrosEncontrados {
    struct NoLivro* livroE;
    struct LivrosEncontrados* prox;
} LivroEncontrado;

//Ponteiro que ajudarão em algoritmos de organização
//Ponteiros da lista principal
NoLivro* primeiroLivro = NULL;
NoLivro* atualLivro = NULL;
NoLivro* anteriorLivro = NULL;
NoLivro* proximoLivro = NULL;
NoLivro* temporarioLivro1 = NULL;
NoLivro* temporarioLivro2 = NULL;
//Ponteiros da lista organizada
LivroEncontrado* primeiroLivroE = NULL;
LivroEncontrado* ultimoLivroE = NULL;
LivroEncontrado* atualLivroE = NULL;
LivroEncontrado* proximoLivroE = NULL;
LivroEncontrado* anteriorLivroE = NULL;

/*
 * --FUNÇÕES QUE ALTEREM O ESTOQUE--
*/
void cadastrar(void) {
    char ISBN[18];
    char temp[50];
    int quant, i;
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
    if((quant > 0) && (quant < 5)) {
        for(i = 0; i < quant; i++)
            cadastro->livro.exemplares[i] = 1;
        if(i != 4)
            cadastro->livro.exemplares[i] = 2;
    } else {
        puts("Quantidade inválido, números abaixo de 0, 0 e números acima de 5 não são permitidos");
        return;
    }
    //Iremos Começar a criar uma lista que podemos utilizar para organizar
    LivroEncontrado* cadastroE = malloc(sizeof(LivroEncontrado));
    cadastroE->livroE = cadastro;
    //Colocar esse livro como o primeiro da lista colocando o prox apontando para o primeiro de antes
    cadastro->prox = primeiroLivro;
    cadastroE->prox = primeiroLivroE;
    //Depois coloca no variável global qual é o novo primeiro da lista
    primeiroLivro = cadastro;
    if(primeiroLivroE == NULL)
        ultimoLivroE = cadastroE;
    primeiroLivroE = cadastroE;

    printf("\nLivro cadastrado com sucesso!\n\n");

    return;
}

//Ajeitar para que altere a lista secundária
void retirar(void) {
    if(primeiroLivro == NULL) {
        return;
    }
    atualLivro = primeiroLivro;
    char ISBN[18];
    printf("Insira o ISBN a ser retirado: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    while(strcmp(atualLivro->livro.isbn, ISBN) != 0) {
        //Caso o atual for o ultimo, encerra o programa
        if(atualLivro->prox == NULL) {
            printf("Não foi encontrado um livro com esse ISBN, tente novamente mais tarde");
            return;
        } else {
            //Guarde o ponteiro atual em anterior
            anteriorLivro = atualLivro;
            //Caso o atual não for o ultimo, continue a procurar
            atualLivro = atualLivro->prox;
        }
    }
    /* Essa parte ta bugando a função retirar
    for(int i = 0; i < 5; i++) {
        if(atualLivro->livro.exemplares[i] == 0)
            printf("Esse livro não pode ser retirado de estoque pois um exemplar foi emprestado\n");
            return;
    }
    */
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
    int quant, op, emprestado, estoque, quantEstoque, i;
    printf("Insira o ISBN a ser alterado: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    if(pesquisarISBN(ISBN)) {
        printf("\nLivro encontrado:");
        imprimirInfo(atualLivro);

        printf("Deseja modificar algum elemento?\n1 - Título\n2 - Autor\n3 - Exemplares (Alterar quantos tem em estoque)\n4 - Sair\n");
        printf("> ");
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("Insira um novo título: ");
                fflush(stdin);
                fgets(temp, 50, stdin);
                strcpy(atualLivro->livro.titulo, strlwr(temp));
                break;
            case 2:
                printf("Insira um novo autor: ");
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
                    printf("Quantos estão em estoque (Máximo 5): ");
                    scanf("%d", &estoque);
                    if(estoque > 5) {
                        puts("Valor inválido, tente novamente");
                        break;
                    }
                    for(i = 0; i < estoque; i++)
                        atualLivro->livro.exemplares[i] = 1;
                    if(estoque != 5)
                        atualLivro->livro.exemplares[i] = 2;
                } else {
                    printf("Alguns livros estão emprestados no momentos, pode apenas adicionar novos exemplares no estoque, ");
                    printf("quantos você vai adicionar ao estoque? No momento tem %d exemplares e o máximo é 5: ", quantEstoque-1);
                    scanf("%d", &estoque);
                    if(estoque + quantEstoque > 5) {
                        puts("Valor inválido, tente novamente");
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
                puts("Valor inserido inválido, tente novamente");
        }
        printf("Resultado: ");
        imprimirInfo(atualLivro);
    } else {
        puts("\nLivro não encontrado\n");
    }

    return;
}

void organizar(void) {
    if(primeiroLivroE == NULL)
        return;

    int tamanhoLista = 0;
    int i, j, k, x, op;

    //Retirar qualquer elemento na lista que não está apontando para um livro
    while(atualLivroE != NULL) {
        //Caso o atual for o ultimo, encerra o programa e retorna falso
        if(atualLivroE->livroE == NULL) {
            if(atualLivroE == primeiroLivroE) {
                primeiroLivroE = primeiroLivroE->prox;
            } else {
                anteriorLivroE->prox = atualLivroE->prox;
            }
        }
        if(atualLivro->prox == NULL) {
            break;
        } else {
            //Guarde o ponteiro atual em anterior
            anteriorLivroE = atualLivroE;
            //Caso o atual não for o ultimo, continue a procurar
            atualLivroE = atualLivroE->prox;
        }
    }

    for(atualLivroE = primeiroLivroE; atualLivroE != NULL; atualLivroE = atualLivroE->prox) {
        tamanhoLista++;
    }

    k = tamanhoLista;

    printf("Deseja organizar por qual modo?\n1 - Título\n2 - Autor\n3 - Sair\n");
    printf("> ");
    scanf("%d", &op);
    if(op == 3) {
        return;
    } else if(op == 1 || op == 2) {
        for (i = 0 ; i < tamanhoLista - 1 ; i++, k-- ) {
            atualLivroE = primeiroLivroE;
            proximoLivroE = atualLivroE->prox;
            if(op == 1) {
                for ( j = 1 ; j < k ; j++ ) {
                    //Para que podemos referenciar o Livro na lista de livros organizados "LivrosE", temos que jogar eles
                    //para uma variável temporário, nesse caso usaremos o temporarioLivro1 e temporarioLivro2
                    temporarioLivro1 = atualLivroE->livroE;
                    temporarioLivro2 = proximoLivroE->livroE;
                    //Quando compara com strncmp se o primeiro string for igual ao segundo o valor retornado será 0
                    //Quando o primeiro string for maior que o segundo o valor retornado será 1 ( > 0)
                    //Quando o primeiro string for menor que o segundo o valor retornado será -1 ( < 0)
                    //São comparados os valors na tabela ASCII
                    //https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/ASCII-Table-wide.svg/1280px-ASCII-Table-wide.svg.png
                    int valorComparacao = strncmp(temporarioLivro1->livro.titulo, temporarioLivro2->livro.titulo, 50);
                    if ( valorComparacao > 0 ) {
                        atualLivroE->livroE = temporarioLivro2;
                        proximoLivroE->livroE = temporarioLivro1;
                    }

                    atualLivroE = atualLivroE->prox;
                    proximoLivroE = proximoLivroE->prox;
                }
            }
            if(op == 2) {
                for ( j = 1 ; j < k ; j++ ) {
                    temporarioLivro1 = atualLivroE->livroE;
                    temporarioLivro2 = proximoLivroE->livroE;
                    int valorComparacao = strncmp(temporarioLivro1->livro.autor, temporarioLivro2->livro.autor, 50);
                    if ( valorComparacao > 0 ) {
                        atualLivroE->livroE = temporarioLivro2;
                        proximoLivroE->livroE = temporarioLivro1;
                    }

                    atualLivroE = atualLivroE->prox;
                    proximoLivroE = proximoLivroE->prox;
                }
            }
        }
    } else {
        puts("Código inválido, tente novamente");
    }
    return;
}

int retirarExemplar(NoLivro* l) {
    for(int i = 0; i < 5; i++) {
        if(l->livro.exemplares[i] == 2) {
            puts("Não tem mais exemplares desse livro em estoque\n");
            return 0;
        }

        if(l->livro.exemplares[i] == 1) {
            l->livro.exemplares[i] = 0;
            return 1;
        }
    }
}

int devolverExemplar(NoLivro* l) {
    for(int i = 0; i < 5; i++) {
        if(l->livro.exemplares[i] == 0) {
            l->livro.exemplares[i] = 1;
            return 1;
        }
    }
    //Se retornar 0 significa que algo ruim aconteceu
    return 0;
}

/*
 * --FUNÇÕES INFORMATIVOS-- Artur
*/

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

void imprimirInfo(NoLivro* l) {
    if(l == NULL) {
        puts("Livro Inválido!");
        return;
    }
    int quantEstoque = 0;
    for(int i = 0; i < 5; i++) {
        if(l->livro.exemplares[i] == 2)
            break;
        if(l->livro.exemplares[i] == 1)
            quantEstoque++;
    }
    printf("\n===Informações Livro===\nTitulo: %sAutor:  %sISBN:   %s\nEm estoque: %d\n\n", l->livro.titulo, l->livro.autor, l->livro.isbn, quantEstoque);
    return;
}

void listarLivros(void) {
    if(primeiroLivroE == NULL || primeiroLivro == NULL) {
        printf("\nA lista está vazia\n\n");
        return;
    }
    organizar();
    atualLivroE = primeiroLivroE;
    while(atualLivroE != NULL) {
        imprimirInfo(atualLivroE->livroE);
        atualLivroE = atualLivroE->prox;
    }
    return;
}

/*
 * --FUNÇÕES DE PERMANÊNCIA DE DISCO-- Bruno
*/
// https://pt.stackoverflow.com/questions/45642/como-guardar-ler-lista-encadeada-em-arquivo
void salvarInfo(void) {
    if(primeiroLivro == NULL) {
        printf("A lista está vazia, nada será salvo.\n");
        return;
    }
    FILE *fp; // File pointer
    fp = fopen("registro.dat", "wb"); // arquivo tem que ter permissão w para escrita e b para abrir como binario
    struct Livro LivrosArray[LIMITEBIBLIOTECA];
    int contador = 0, esc;

    if (fp != NULL) {
        // Cria um array com as struct Livro
        atualLivro = primeiroLivro;
        while(atualLivro != NULL) {
            strcpy(LivrosArray[contador].titulo, atualLivro->livro.titulo);
            strcpy(LivrosArray[contador].autor, atualLivro->livro.autor);
            for(int i = 0; i < 5; i++)
                LivrosArray[contador].exemplares[i] = atualLivro->livro.exemplares[i];
            strcpy(LivrosArray[contador].isbn, atualLivro->livro.isbn);
            atualLivro = atualLivro->prox;
            contador++;
        }

        esc = fwrite(LivrosArray, sizeof(struct Livro), contador, fp); // Função retorna quantidade de elementos escritos
        if (esc == contador)
            printf("\nGravacao de registros com sucesso\n\n");
        else
            printf("\nErro na gravação de registro\n\n");
        fclose(fp);
    } else
        puts("\nErro na criação do arquivo\n");

    return;
}
void recuperarInfo(void) {
    FILE *fp;
    fp = fopen("registro.dat", "rb");
    struct Livro LivrosArray[LIMITEBIBLIOTECA];
    int esc;

    if (fp != NULL) {
        esc = fread(LivrosArray, sizeof(struct Livro), LIMITEBIBLIOTECA, fp);
        if (esc > 0) {
            for (int i = 0; i < esc; i++) {
                NoLivro* reCadastro = malloc(sizeof(NoLivro));
                strcpy(reCadastro->livro.titulo, LivrosArray[i].titulo);
                strcpy(reCadastro->livro.autor, LivrosArray[i].autor);
                for(int i = 0; i < 5; i++)
                    reCadastro->livro.exemplares[i] = LivrosArray[i].exemplares[i];
                strcpy(reCadastro->livro.isbn, LivrosArray[i].isbn);

                LivroEncontrado* reCadastroE = malloc(sizeof(LivroEncontrado));
                reCadastroE->livroE = reCadastro;
                //Colocar esse livro como o primeiro da lista colocando o prox apontando para o primeiro de antes
                reCadastro->prox = primeiroLivro;
                reCadastroE->prox = primeiroLivroE;
                //Depois coloca no variável global qual é o novo primeiro da lista
                primeiroLivro = reCadastro;
                if(primeiroLivroE == NULL)
                    ultimoLivroE = reCadastroE;
                primeiroLivroE = reCadastroE;
            }
            printf("Leitura do registro realizado com sucesso\n");
        }
        else
            printf("Não há registros anteriores para recuperar\n");

        fclose(fp);
    }
    else
        puts("\nNão há arquivo de registros anteriores\n");
}



