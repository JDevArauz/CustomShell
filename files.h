#ifndef files_H
#define files_H
int escritura(char *remitente, char *destinatario);
int redireccion(char *remitente, char *destinatario);
int anexion(char *remitente, char *destinatario);
int extraerfiles(char *string);
int separarfiles(char *fichero, char *separador, char *files[]);
#endif