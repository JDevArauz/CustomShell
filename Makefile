myprompt : files.o trim.o extraction.o prompt.o commands.o  Main.o
	@gcc Main.o files.o trim.o extraction.o prompt.o commands.o -o myprompt
Main.o : Main.c extraction.h prompt.h commands.h
	@gcc -c Main.c
trim.o : trim.c
	@gcc -c trim.c
files.o : files.c trim.h 
	@gcc -c files.c trim.h 
extraction.o : extraction.c trim.h 
	@gcc -c extraction.c trim.h 
prompt.o : prompt.c
	@gcc -c prompt.c
commands.o : commands.c extraction.h prompt.h trim.h files.h
	@gcc -c commands.c extraction.h prompt.h trim.h files.h