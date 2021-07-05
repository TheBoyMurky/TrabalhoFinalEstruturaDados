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
* Grupo: Artur Dias, Bruno Simon, David Leonardeli, Jannaina e Luiz Gustavo
*/

// AutoLibrarian
// "Automatize suas funções na biblioteca com esse programa!"
int main()
{
    setlocale(LC_ALL, "portuguese-brazilian");
    sistema();
    return 0;
}
