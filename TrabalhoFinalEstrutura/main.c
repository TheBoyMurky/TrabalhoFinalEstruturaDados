#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include "sistema.h"
#include "livros.h"
#include "clientes.h"


int main()
{
    setlocale(LC_ALL, "portuguese-brazilian");
    sistema();
    return 0;
}
