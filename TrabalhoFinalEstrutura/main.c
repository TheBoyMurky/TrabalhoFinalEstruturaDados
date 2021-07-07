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
1.O sistema deve possibilitar o cadastro das entidades (por exemplo: livro, exemplar, associado, empréstimo, reserva, etc.) identificadas
a partir do problema. X

2.Tais  informações  serão armazenadas  em  memória  em  uma  estrutura  de  lista encadeada e ao final do sistema a persistência em disco
deve ser realizada. X

3.O sistema não deve permitir a inclusão de informações duplicadas (por exemplo, dois livros com o mesmo ISBN).
Isso vale para todasas entidades do sistema. Desse modo, cada   instância   da   entidade   deve   possuir   um   valor   (chave)   que
a identifica unicamente. X

4.Deve ainda permitir a exclusão de determinado registro somente se o mesmo não estiver sendo relacionado por outra entidade a qual dependa
dessa informação. X

5.Todas  as  informações  podem  ser  alteradas,  com  exceção  do  campo  que  identifica unicamente determinada entidade (chave). X

6.O sistema deve possibilitar a listagem por algum tipo de ordem das informações de cada entidade. Para tal, cada entidade terá a sua lista
principal e uma lista secundária ordenada por determinado campo que contenha, além do campo que possibilita a ordem, o endereço do nó na
lista principal permitindo o acesso à informação completa. O algoritmo de ordenação Quicksort deve ser utilizado. X

7.O  sistema  deve  ainda  permitir,  para  uma  entidade  específica,  a  localização  de determinado registro pelo campo utilizado no item 6.
O algoritmo de busca binária deve ser utilizado.

8.Ao ser executado posteriormente, o sistema, deve recompor em memória todas as informações previamente armazenadas em disco. !Acho que consegui!

9.Considerando o objetivo principal do sistema (controle de empréstimos de livros) o mesmo deve realizar todas as consistências ou operações
que se caracterizem como uma  regra  de  negócio  (por  exemplo,  verificação  do  limite  de  empréstimo  por usuário, cobrança de multa,
travamento de empréstimo, etc). As regras são descritas na seção II. Universidade do Extremo Sul Catarinense !Realizado ja uma verificação de limite!
Unidade Acadêmica de Ciências, Engenharias e Tecnologias Curso de Ciência da Computação

10.O sistema deve permitir a geração de pelo menos dois relatórios gerenciais em que as  informações  estejam  agrupadas  e  sumarizadas.
Por  exemplo,  os  10  livros  mais emprestados durante um determinado período.
*/

int main()
{
    setlocale(LC_ALL, "portuguese-brazilian");
    sistema();
    return 0;
}
