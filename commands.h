#ifndef COMMANDS_H
#define COMMANDS_H
void handle_sigint(int sig);
int ejecutorComandos(char *string);
int validarComando(char *str);
#endif