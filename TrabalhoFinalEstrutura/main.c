#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include "sistema.h"
#include "livros.h"
#include "clientes.h"

/*
* Disciplina: Estrutura de Dados
* Professora: Marta Adriana Machado da Silva
* Grupo: Artur Dias, Alysson, Bruno Simon, David Leonardeli, Jannaina e Luiz Gustavo
*/
// Biblioteca do Macaco
/*
1.O sistema deve possibilitar o cadastro das entidades (por exemplo: livro, exemplar, associado, empr�stimo, reserva, etc.) identificadas
a partir do problema. X

2.Tais  informa��es  ser�o armazenadas  em  mem�ria  em  uma  estrutura  de  lista encadeada e ao final do sistema a persist�ncia em disco
deve ser realizada. X

3.O sistema n�o deve permitir a inclus�o de informa��es duplicadas (por exemplo, dois livros com o mesmo ISBN).
Isso vale para todasas entidades do sistema. Desse modo, cada   inst�ncia   da   entidade   deve   possuir   um   valor   (chave)   que
a identifica unicamente. X

4.Deve ainda permitir a exclus�o de determinado registro somente se o mesmo n�o estiver sendo relacionado por outra entidade a qual dependa
dessa informa��o. X

5.Todas  as  informa��es  podem  ser  alteradas,  com  exce��o  do  campo  que  identifica unicamente determinada entidade (chave). X

6.O sistema deve possibilitar a listagem por algum tipo de ordem das informa��es de cada entidade. Para tal, cada entidade ter� a sua lista
principal e uma lista secund�ria ordenada por determinado campo que contenha, al�m do campo que possibilita a ordem, o endere�o do n� na
lista principal permitindo o acesso � informa��o completa. O algoritmo de ordena��o Quicksort deve ser utilizado. X

7.O  sistema  deve  ainda  permitir,  para  uma  entidade  espec�fica,  a  localiza��o  de determinado registro pelo campo utilizado no item 6.
O algoritmo de busca bin�ria deve ser utilizado.

8.Ao ser executado posteriormente, o sistema, deve recompor em mem�ria todas as informa��es previamente armazenadas em disco. !Acho que consegui!

9.Considerando o objetivo principal do sistema (controle de empr�stimos de livros) o mesmo deve realizar todas as consist�ncias ou opera��es
que se caracterizem como uma  regra  de  neg�cio  (por  exemplo,  verifica��o  do  limite  de  empr�stimo  por usu�rio, cobran�a de multa,
travamento de empr�stimo, etc). As regras s�o descritas na se��o II. Universidade do Extremo Sul Catarinense !Realizado ja uma verifica��o de limite!
Unidade Acad�mica de Ci�ncias, Engenharias e Tecnologias Curso de Ci�ncia da Computa��o

10.O sistema deve permitir a gera��o de pelo menos dois relat�rios gerenciais em que as  informa��es  estejam  agrupadas  e  sumarizadas.
Por  exemplo,  os  10  livros  mais emprestados durante um determinado per�odo.
*/

int main()
{
    setlocale(LC_ALL, "portuguese-brazilian");
    sistema();
    return 0;
}
