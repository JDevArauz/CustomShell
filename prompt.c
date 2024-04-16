#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h> 
#include <errno.h>
#include "prompt.h"

void mostrarPrompt() // FUNCIÓN PARA MOSTRAR LA CONSOLA
{
    char *buf; // VARIABLE PUNTERO PARA ALMACENAR LA RUTA
    char *ptr; // VARIABLE PUNTERO PARA OBTENER EL DIRECTORIO ACTUAL
    long size; // VARIABLE PARA OBTENER EL TAMAÑO DE LA RUTA

    size = pathconf(".", _PC_PATH_MAX);               // DIRECCIÓN DE LA RUTA
    if ((buf = (char *)malloc((size_t)size)) != NULL) // ASIGNANDO MEMORIA
    {
        ptr = getcwd(buf, (size_t)size); // OBTENIENDO EL DIRECTORIO ACTUAL
        struct passwd *getpwuid(uid_t uid); // SE CREA LA ESTRUCTURA PARA OBTENER EL USUARIO
        struct passwd *p; 
        uid_t uid = 0; // ASIGNANDO EL USUARIO
        if ((p = getpwuid(uid)) == NULL)
        {
            perror("getpwuid() No se pudo obtener el usuario"); // MOSTRANDO ERROR SI NO SE PUEDE OBTENER EL USUARIO
        }
        else
        {
            printf("%s@%s > ", p->pw_name, ptr); // MOSTRANDO EL PROMPT CON EL USUARIO Y DIRECTORIO
        }

        free(buf); // LIBERANDO MEMORIA
    }
}

void redireccionar(char *comando[]) // FUNCION PARA REDIRECCIONAR LOS DIRECTORIOS CON "CD"
{
    struct passwd *pwd;
    char *path = comando[1]; // ASIGNANDO LOS PARAMETROS AL PATH DEL COMANDO CD INGRESADO
    if (path == NULL)
    {
        pwd = getpwuid(getuid());
        path = pwd->pw_dir;
    }
    errno = chdir(path);
    if (errno != 0)
    {
        printf("ERROR: No se pudo cambiar el directorio, revisa que el nombre esté escrito correctamente...\n");
    }
}
