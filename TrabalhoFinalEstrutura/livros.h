#ifndef LIVROS_H_INCLUDED
#define LIVROS_H_INCLUDED

//Modifica Lista
void cadastrar(void);
void retirar(void);
void modificarLivro(void);
void organizarTitulo(void);

//Informativo
int pesquisarISBN(char ISBNPesquisado[18]);
void imprimirInfo(struct NoLivro* l);
void listarLivros(void);

//Salvar em disco informaçõs
void salvarInfo(void);
void recuperarInfo(void);

#endif // LIVROS_H_INCLUDED
