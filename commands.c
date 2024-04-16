#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <signal.h>
#include "trim.h"
#include "extraction.h"
#include "commands.h"
#include "prompt.h"
#include "files.h"

#define MAX_INPUT 256
#define SALIR "exit"

void handle_sigint(int sig) // FUNCION PARA MANEJAR LA DETENCION DE CTRL +C
{
    printf("\nNo se puede salir de la consola. Utilice 'exit' o presione ENTER para continuar...\n");
}

int ejecutorComandos(char *string) // FUNCION PARA LA EJECUCION DE COMANDOS - 0 PARA COMANDOS VALIDOS - 1 PARA COMANDOS CON ERROR
{
    char *comandos[5];
    int i = extraerComandos(string, comandos); // EXTRAYENDO EL NÚMERO DE COMANDOS INGRESADOS
    char *params[i][5];
    char *comando[i];

    for (int j = 0; j < i; j++) // SEPARANDO LOS COMANDOS POR SUS REPSECTIVOS PARAMETROS
    {
        extraerParametros(comandos[j], params[j]); // EJECUTANDO LA SEPARACIÓN DE PARAMETROS
        comando[j] = params[j][0];
    }
    // DESCRIPTORES DE ARCHIVOS
    int fd[2];
    int fd_actual = 0;
    // EJECUTANDO COMANDOS Y SUS PARAMETROS
    for (int k = 0; k < i; k++) // LA i REPRESENTA CADA COMANDO INGRESADO, SE RECORREN POR MEDIO DEL FOR
    {
        if (strcmp("cd", comando[0]) == 0 || strcmp("cd..", comando[0]) == 0) // SE VALIDA SI SE INGRESÓ "cd" PARA ENVIAR A LA FUNCIÓN CORRESPONDIENTE
        {
            redireccionar(params[0]); // REDIRECCIONANDO DIRECTORIOS
            return 0;
        }
        else if (strcmp("killall", comando[0]) == 0) // SE VALIDA SI SE INGRESÓ "killall"
        {
            if (params[0][1] != NULL) // SE VALIDA SI SE INGRESÓ EL NOMBRE DEL PROCESO
            {
                if (strcmp("mishell", params[0][1]) == 0) // SE VALIDA SI EL NOMBRE DEL PROCESO ES IGUAL AL DE LA CONSOLA
                {
                    printf("NO se puede eliminar tu propia consola...\n");
                    return 0;
                }
            }
        }

        pipe(fd);       // CREO UNA TUBERÍA POR CADA COMANDO CARGADO EN LA LISTA DE COMANDOS Y RECORRIDO POR EL FOR
        switch (fork()) // REALIZO UN INTERCAMBIO CONSTANTE DE PADRE A HIJO E INCLUSO EN CASO DE ERRORES
        {
        case 0: // CASO HIJO

            dup2(fd_actual, 0);
            if (k + 1 != i) // VALIDACION PARA EL CONTROL DE EL CIERRE FINAL DE LAS TUBERÍAS ESCRITAS
            {               // ESTO SE HACE CON EL FIN DE PODER COMUNICAR TODAS LAS TUBERÍAS Y LOGRAR UNA SOLA SALIDA CON TODOS LOS COMANDOS
                dup2(fd[1], STDOUT_FILENO);
            }
            close(fd[0]);
            if (execvp(comando[k], params[k]) < 0) // SE EJECUTAN LOS COMANDOS AL INSTANTE Y SI DEVUELVEN UN NÚMERO MENOR QUE 0 SIGNIFICA QUE EL COMANDO NO EXISTE
            {
                printf("NO se reconoce el comando...\n");
            }
            exit(1); // SE REALIZA ESTE EXIT PARA CERRAR LOS PROCESOS HIJOS
            break;

        case -1: // CASO DE ERROR

            perror("Error en el fork()\n");
            return 1;

        default:        // CASO DEFINIDO PARA EL PADRE
            wait(NULL); // WAIT PARA ESPERAR A LOS HIJOS
            close(fd[1]);
            fd_actual = fd[0];
            break;
        }
    }
    return 0;
}

int validarComando(char *str) // DEVUELVE 1 EN CASO DE HABER INGRESADO "SALIR" Y 0 EN CASO SE SEGUIR EN PIE
{
    while (strcmp(trim(str), SALIR) != 0) // MIENTRAS NO SE INGRESE LA PALABRA SALIR, LA CONSOLA SEGUIRA CORRIENDO
    {
        if (strcmp(str, "\n") == 0) // AL DETECTAR LAS ENTRADAS POR CONSOLA SE LEERÁ CADA VEZ QUE EL USUARIO INGRESE LA TECLA ENTER
        {
            return 0;
        }
        else if (extraerfiles(str) == 0)
        {
            return 0;
        }
        else
        {
            ejecutorComandos(str); // PROCEDIENDO A EJECUTAR LOS COMANDOS
        }
        return 0;
    }
    return 1;
}