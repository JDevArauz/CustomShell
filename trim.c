#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
char *ltrim(char *string) // OMITE LOS ESPACIOS A LA IZQUIERDA DE UNA CADENA - OJO LOS RESTA A NIVEL DE DIRECCIONES DE MEMORIA
{
    while (isspace(*string))
    {
        string++;
    }
    return string;
}

char *rtrim(char *string) // OMITE LOS ESPACIOS A LA DERECHA DE UNA CADENA - OJO LOS RESTA A NIVEL DE DIRECCIONES DE MEMORIA
{
    char *back = string + strlen(string);
    while (isspace(*--back))
        ;
    *(back + 1) = '\0'; // INGRESANDO CARACTER DE TERMINACIÓN DE LÍNEA
    return string;
}

char *trim(char *string) // FUNCION QUE APLICA LAS DOS FUNCIONES DE ARRIBA EN CONJUNTO
{
    return rtrim(ltrim(string));
}
