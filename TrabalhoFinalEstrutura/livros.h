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

//Emprestimo
int retirarExemplar(struct NoLivro* l);

//Como não consegui retornar o nó em pesquisarISBN, vou utilizar o ponteiro para facilitar a vida
//https://stackoverflow.com/questions/1045501/how-do-i-share-variables-between-different-c-files
extern struct NoLivro* atualLivro;

#endif // LIVROS_H_INCLUDED
