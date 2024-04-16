#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "trim.h"
#include "files.h"

int extraerComandos(char *string, char *cmds[]) // SEPARADOR DE COMANDOS POR CADA PIPE |
{
    char i = 0;
    char *partes = strtok(string, "|");
    while (partes != NULL)
    {
        cmds[i] = trim(partes);
        partes = strtok(NULL, "|");
        i++;
    }
    return i; // SE REALIZA UN RETORNO DE LA CANTIDAD DE COMANDOS EXTRAÍDOS
}

int extraerParametros(char *string, char *cmds[]) // EXTRACTOR DE PARÁMETROS
{
    int i = 0;
    char *param = strtok(string, " "); // AÑADIENDO TOKEN A STRING PARA SEPARARLO
    while (param != NULL)
    {
        cmds[i] = trim(param); // SEPARANDO TOKENS DEL STRING POR MEDIO DE LA FUNCION TRIM
        param = strtok(NULL, " ");
        i++;
    }
    cmds[i] = NULL;
    return i; // SE RELIZA UN RETORNO DE LA CANTIDAD DE PARÁMETROS UTILIZADOS
}