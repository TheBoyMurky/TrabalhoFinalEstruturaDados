#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>

struct Leitor {
    char nome[50];
    //Valor Chave
    //Ex.: AAAA-1234
    char id[9];
    struct NoLivro* livrosEmprestados[3];
};
struct NoLeitor {
    struct Leitor leitor;
    struct NoLeitor* prox;
};
struct NoLeitorEncontrado {
    struct Leitor* leitor;
    struct NoLeitorEncontrado* prox;
};

void cadastrarCliente(void);
void emprestarLivro(char ISBN[18]);
