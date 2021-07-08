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
    //3 exemplares = exemplar = { 0, 1, 1, 2, 0 }
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
//Ponteiros da lista secund�rio que ser� representado com um E no final (Encontrado)
LivroEncontrado* primeiroLivroE = NULL;
//LivroEncontrado* ultimoLivroE = NULL; //Seria utilizado no BubbleSort
LivroEncontrado* atualLivroE = NULL;
LivroEncontrado* proximoLivroE = NULL;
LivroEncontrado* anteriorLivroE = NULL;

/*
 * --FUN��ES QUE ALTEREM O ESTOQUE--
*/
void cadastrar(void) {
    char ISBN[18];
    char temp[50];
    int quant, i;
    //Iniciamos um ponteiro do tipo NoLivro para receber o endere�o que ser� alocado por malloc de tamanho que cabe a nossa struct No
    NoLivro* cadastro = malloc(sizeof(NoLivro)); //malloc � apenas uma fun��o para reservar um espa�o em mem�ria de tamanho x e vai retornar o endere�o onde reservou
    //Requisito de informa��es b�sicas
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
    //Verifica��o de formata��o
    if(strlen(ISBN) == 17) {
        //Verifica��o se ja existe um livro com esse ISBN, se retornasse 1 (Verdadeiro) significa que encontrou
        if(!pesquisarISBN(ISBN)) {
            strcpy(cadastro->livro.isbn, ISBN);
        } else {
            //Caso ja exista ele vai ler as informa��es de tal livro
            puts("J� existe um livro com esse identificador:");
            imprimirInfo(atualLivro);
            puts("Verifique o estoque e tente novamente");
            return;
        }
    } else {
        puts("Tamanho de ISBN incorreto, tente novamente");
        return;
    }
    //Aqui � como � constru�do o array de exemplares, como o exemplo no in�cio do arquivo
    printf("Insira quantidade de exemplares tem em estoque desse livro: ");
    fflush(stdin);
    scanf("%d", &quant);
    //Para essa apresenta��o utilizaremos no m�ximo 5 exemplares
    if((quant > 0) && (quant <= 5)) {
        for(i = 0; i < quant; i++)
            cadastro->livro.exemplares[i] = 1;
        //Caso o loop termine e n�o preenche o array, ser� finalizado com um 2 que representa o final
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
    //Verifica antes se a lista est� vazia
    if(primeiroLivro == NULL) {
        printf("A lista est� vazia, tente novamente mais tarde\n");
        return;
    }
    //Visto que a lista n�o est� vazia ser� usado a vari�vel atualLivro como ponteiro de qual livro retirar
    atualLivro = primeiroLivro;
    //Pede o valor chave unico do livro
    char ISBN[18];
    printf("Insira o ISBN a ser retirado: ");
    fflush(stdin);
    fgets(ISBN, 18, stdin);
    //Quick search
    while(strcmp(atualLivro->livro.isbn, ISBN) != 0) {
        //Caso o atual for o ultimo, encerra o programa
        if(atualLivro->prox == NULL) {
            printf("N�o foi encontrado um livro com esse ISBN, tente novamente mais tarde");
            return;
        } else {
            //Guarde o ponteiro atual em anterior
            anteriorLivro = atualLivro;
            //Caso o atual n�o for o ultimo, continue a procurar
            atualLivro = atualLivro->prox;
        }
    }
    /* Essa parte ta bugando a fun��o retirar
    for(int i = 0; i < 5; i++) {
        if(atualLivro->livro.exemplares[i] == 0)
            printf("Esse livro n�o pode ser retirado de estoque pois um exemplar foi emprestado\n");
            return;
    }
    */
    if(atualLivro == primeiroLivro) {
        //Apenas esquece o primeiro de antes em mem�ria jogando o ponteiro do primeiro da lista para o pr�ximo
        primeiroLivro = primeiroLivro->prox;
    } else {
        //Nesse passo ser� colocado o pr�ximo do atual, para o pr�ximo do anterior, assim, o anterior vai passar em frente ignorando o ponteiro atualLivro
        anteriorLivro->prox = atualLivro->prox;
    }
    printf("Livro retirado com sucesso:\n");
    imprimirInfo(atualLivro);

    return;
}

void modificarLivro(void) {
    //Inicializa algumas vari�veis
    char ISBN[18];
    char temp[50];
    int quant, op, emprestado, estoque, quantEstoque, i;

    //Pede o valor chave unico do livro
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
                printf("Insira um novo autor: ");
                fflush(stdin);
                fgets(temp, 50, stdin);
                strcpy(atualLivro->livro.autor, strlwr(temp));
                break;

            case 3:
                emprestado = 0;
                quantEstoque = 0;
                //Aqui ser� contados quantos exemplares tem e quantos foram emprestados
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

                //Caso nenhum exemplar foi emprestado pode se alterar o valor completo dos exemplares
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
                } else { //Caso tiver alguns exemplares que ja foram emprestados n�o pode alterar quantos est�o em estoque, apenas adicionar
                    printf("Alguns livros est�o emprestados no momentos, pode apenas adicionar novos exemplares no estoque, ");
                    printf("quantos voc� vai adicionar ao estoque? No momento tem %d exemplares e o m�ximo � 5: ", quantEstoque-1);
                    scanf("%d", &estoque);
                    //Verifica se na soma n�o passou de 5 exemplares
                    if(estoque + quantEstoque > 5) {
                        puts("Valor inv�lido, tente novamente");
                        break;
                    } else { //Aqui ent�o � tirado o 2 sinalizando o final e troca at� o final que � adicionado
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
        printf("Resultado: "); //Aqui imprime os resultados finais da modifica��o
        imprimirInfo(atualLivro);
    } else {
        puts("\nLivro n�o encontrado\n");
    }

    return;
}

void organizar(void) {
    //Verifica se a lista n�o est� vazia
    if(primeiroLivroE == NULL)
        return;

    //Inicializa algumas vari�veis
    int tamanhoLista = 0;
    int i, j, k, x, op;

    //Retirar qualquer elemento na lista que n�o est� apontando para um livro
    while(atualLivroE != NULL) {
        //Verifica se o elemento n�o est� apontando para um n� livro
        if(atualLivroE->livroE == NULL) {
            if(atualLivroE == primeiroLivroE) { //Caso for o primeiro, ser� passa o ponteiro primeiroLivroE para o pr�ximo
                primeiroLivroE = primeiroLivroE->prox;
            } else { //Caso n�o for o primeiro ser� retirado como feito na fun��o retirar
                anteriorLivroE->prox = atualLivroE->prox;
            }
        }
        //Caso for o ultimo elemento quebra o loop
        if(atualLivro->prox == NULL) {
            break;
        } else {
            //Guarde o ponteiro atual em anterior
            anteriorLivroE = atualLivroE;
            //Caso o atual n�o for o ultimo, continue a procurar
            atualLivroE = atualLivroE->prox;
        }
    }

    //Conta quantos elementos tem na lista secund�rio
    for(atualLivroE = primeiroLivroE; atualLivroE != NULL; atualLivroE = atualLivroE->prox)
        tamanhoLista++;

    k = tamanhoLista; //k ser� para o segundo for loop do QuickSort

    printf("Deseja organizar por qual modo?\n1 - T�tulo\n2 - Autor\n3 - Sair\n");
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
                    //para uma vari�vel tempor�rio, nesse caso usaremos o temporarioLivro1 e temporarioLivro2
                    temporarioLivro1 = atualLivroE->livroE;
                    temporarioLivro2 = proximoLivroE->livroE;
                    //Quando compara com strncmp se o primeiro string for igual ao segundo o valor retornado ser� 0
                    //Quando o primeiro string for maior que o segundo o valor retornado ser� 1 ( > 0)
                    //Quando o primeiro string for menor que o segundo o valor retornado ser� -1 ( < 0)
                    //S�o comparados os valors na tabela ASCII
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
        puts("C�digo inv�lido, tente novamente");
    }
    return;
}

//Verifica se tem exemplares em estoque (1 do nosso array exemplares[])
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

//Troca o primeiro exemplar emprestado (0) para 1
int devolverExemplar(NoLivro* l) {
    for(int i = 0; i < 5; i++) {
        if(l->livro.exemplares[i] == 0) {
            l->livro.exemplares[i] = 1;
            return 1;
        }
    }
    //Dificilmente pode aconter de retornar 0, mas para que podemos avaliar caso haja um erro deixamos que retorne 0
    return 0;
}

/*
 * --FUN��ES INFORMATIVOS-- Artur
*/

//N�o consegui fazer retornar um NoLivro, irei ent�o utilizar para resolver condi��o
//retornando 0 para falso e 1 para verdadeiro
//Caso retorne 1 significa que o atualLivro � o Livro encontrado
//A fun��o via utilizar o atualLivro como ponteiro para resolver passar o valor encontrado
int pesquisarISBN(char ISBNPesquisado[18]) {
    //Verifica se a lista est� vazia
    if(primeiroLivro == NULL)
        return 0;
    atualLivro = primeiroLivro;

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

void imprimirInfo(NoLivro* l) {
    //Verifica se o n� est� apontando para um livro
    if(l == NULL) {
        puts("Livro Inv�lido!");
        return;
    }
    //Verifica a quantidade que est� em estoque (Que n�o foram emprestados)
    int quantEstoque = 0;
    for(int i = 0; i < 5; i++) {
        if(l->livro.exemplares[i] == 2)
            break;
        if(l->livro.exemplares[i] == 1)
            quantEstoque++;
    }
    printf("\n==Informa��es Livro==\n");
    printf("Titulo:     %s", l->livro.titulo);
    printf("Autor:      %s", l->livro.autor);
    printf("ISBN:       %s", l->livro.isbn);
    printf("Em estoque: %d\n\n", quantEstoque)

    return;
}

void listarLivros(void) {
    //Verifica se nas duas listas est�o vazias
    if(primeiroLivroE == NULL || primeiroLivro == NULL) {
        printf("\nA lista est� vazia\n\n");
        return;
    }
    //Organiza a lista secund�rio
    organizar();

    atualLivroE = primeiroLivroE;
    //Imprime todos os elementos da lista secund�rio
    while(atualLivroE != NULL) {
        imprimirInfo(atualLivroE->livroE);
        atualLivroE = atualLivroE->prox;
    }
    return;
}

/*
 * --FUN��ES DE PERMAN�NCIA DE DISCO-- Bruno
*/
// https://pt.stackoverflow.com/questions/45642/como-guardar-ler-lista-encadeada-em-arquivo
void salvarInfo(void) {
    if(primeiroLivro == NULL) {
        printf("A lista est� vazia, nada ser� salvo.\n");
        return;
    }
    FILE *fp; // ponteiro para o arquivo (ser� usado em fun��es de leitura e escrita)
    fp = fopen("registro.dat", "wb"); // arquivo tem que ter permiss�o w para escrita e b para abrir como binario
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

        esc = fwrite(LivrosArray, sizeof(struct Livro), contador, fp); // Fun��o retorna quantidade de elementos escritos
        if (esc == contador) //Verifica se todos os elementos do array foram registrados
            printf("\nGravacao de registros com sucesso\n");
        else
            printf("\nErro na grava��o de registro\n"); //Caso n�o, ser� representado por esse erro
        fclose(fp);
    } else
        puts("\nErro na cria��o do arquivo\n");

    return;
}
void recuperarInfo(void) {
    FILE *fp;
    fp = fopen("registro.dat", "rb");
    struct Livro LivrosArray[LIMITEBIBLIOTECA];
    int esc;

    if (fp != NULL) {
        esc = fread(LivrosArray, sizeof(struct Livro), LIMITEBIBLIOTECA, fp);
        if (esc > 0) { //Caso for recuperado, o esc ir� representar a quantidade de elementos do array
            for (int i = 0; i < esc; i++) {
                //Aqui ser� refeito as aloca��es como seria na fun��o cadastrar
                NoLivro* reCadastro = malloc(sizeof(NoLivro));
                strcpy(reCadastro->livro.titulo, LivrosArray[i].titulo);
                strcpy(reCadastro->livro.autor, LivrosArray[i].autor);
                for(int i = 0; i < 5; i++)
                    reCadastro->livro.exemplares[i] = LivrosArray[i].exemplares[i];
                strcpy(reCadastro->livro.isbn, LivrosArray[i].isbn);

                LivroEncontrado* reCadastroE = malloc(sizeof(LivroEncontrado));
                reCadastroE->livroE = reCadastro;
                reCadastro->prox = primeiroLivro;
                reCadastroE->prox = primeiroLivroE;
                primeiroLivro = reCadastro;
                primeiroLivroE = reCadastroE;
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



