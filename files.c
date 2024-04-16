#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "trim.h"

FILE *entrada, *salida;
int datos = 0;

int escritura(char *remitente, char *destinatario) // FUNCIÓN DE ENTRADA DE UN FICHERO A OTRO
{
    
    entrada = fopen(remitente, "r");
    salida = fopen(destinatario, "a");

    while ((datos = fgetc(entrada)) != EOF)
    {
        fputc(datos, salida);
    }

    fclose(entrada);
    fclose(salida);
    printf("ENTRADA REALIZADA CON ÉXITO...\n");
    return 0;
}

int redireccion(char *remitente, char *destinatario) // FUNCIÓN DE REDIRECCIÓN DE UN FICHERO A OTRO
{
    entrada = fopen(remitente, "r");
    salida = fopen(destinatario, "w");

    while ((datos = fgetc(entrada)) != EOF)
    {
        fputc(datos, salida);
    }

    fclose(entrada);
    fclose(salida);
    printf("REDIRECCIÓN REALIZADA CON ÉXITO...\n");

    return 0;
}

int anexion(char *remitente, char *destinatario) // FUNCIÓN DE ANEXION DE UN FICHERO A OTRO
{
    entrada = fopen(remitente, "r");
    salida = fopen(destinatario, "a");

    while ((datos = fgetc(entrada)) != EOF)
    {
        fputc(datos, salida);
    }

    fclose(entrada);
    fclose(salida);
    printf("ANEXIÓN REALIZADA CON ÉXITO...\n");

    return 0;
}

int separarfiles(char *fichero, char *separador, char *files[]) // SEPARA LOS files PARA REALIZAR LA OPERACIÓN QUE DESEE CON ELLOS
{
    int i = 0;
    char *partes = strtok(fichero, separador);
    while (partes != NULL)
    {
        files[i] = trim(partes);
        partes = strtok(NULL, separador);

        i++;
    }
    if (separador == ">")
    {
        escritura(files[0], files[1]);
    }
    else if (separador == "<")
    {
        anexion(files[0], files[1]);
    }
    else if (separador == ">>")
    {
        redireccion(files[0], files[1]);
    }
    return i;
}

int extraerfiles(char *string) // FUNCIÓN PARA EXTRAER LOS files DEPENDIENDO DE LA ACCIÓN QUE DESEE REALIZAR CON ELLOS
{
    int indice = 0;
    char *files[3];
    while (string[indice] != '\0')
    {
        if (string[indice] == '>' && string[indice + 1] == ' ')
        {
            separarfiles(string, ">", files);
            return 0;
        }
        else if (string[indice] == '<')
        {
            separarfiles(string, "<", files);
            return 0;
        }
        else if (string[indice] == '>' && string[indice + 1] == '>')
        {
            separarfiles(string, ">>", files);
            return 0;
        }
        indice++;
    }
    return 1;
}
