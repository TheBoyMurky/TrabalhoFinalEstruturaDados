#ifndef LIVROS_H_INCLUDED
#define LIVROS_H_INCLUDED

//Modifica Lista
void cadastrar(void);
void retirar(void);
void modificarLivro(void);
void organizar(void);
int retirarExemplar(struct NoLivro* l);
int devolverExemplar(struct NoLivro* l);

//Informativo
int pesquisarISBN(char ISBNPesquisado[18]);
void imprimirInfo(struct NoLivro* l);
void listarLivros(void);

//Salvar em disco informações
void salvarInfo(void);
void recuperarInfo(void);

//Como não consegui retornar o nó em pesquisarISBN, vou utilizar o ponteiro para funções em clientes.c
//https://stackoverflow.com/questions/1045501/how-do-i-share-variables-between-different-c-files
extern struct NoLivro* atualLivro;

#endif // LIVROS_H_INCLUDED
