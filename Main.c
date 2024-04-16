#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "prompt.h"
#include "commands.h"
#include "extraction.h"
#include "trim.h"

void main()
{
        char input[256] = "";

        struct sigaction sa; // ESTRUCTURA PARA EVITAR DETENER EL PROCESO CON CTRL + C
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigint;
        sigaction(SIGINT, &sa, NULL);
        signal(SIGINT, &handle_sigint);

        while (validarComando(input) != 1) // VALIDACIÓN CONSTANTE PARA REALIZAR LA MUESTRA DE LA CONSOLA
        {
                mostrarPrompt();
                fgets(input, 256, stdin);
        }
        printf("\nSaliendo del terminal...\n\n");
}