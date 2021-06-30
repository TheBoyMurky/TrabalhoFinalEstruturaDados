#ifndef LIVROS_H_INCLUDED
#define LIVROS_H_INCLUDED

void cadastrar(void);
void retirar(char ISBN[18]);
int pesquisarISBN(char ISBNPesquisado[18]);
void imprimirInfo(struct NoLivro* l);
void emprestarLivro(void);
void listarLivros(void);
void salvarInfo(void);
void organizar(void);

#endif // LIVROS_H_INCLUDED
