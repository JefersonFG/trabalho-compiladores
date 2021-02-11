etapa1: lex.yy.o main.o hash.o
	gcc -Wall -Wextra -O3 -o etapa1 lex.yy.o main.o hash.o
main.o: main.c
	gcc -Wall -Wextra -O3 -c main.c
hash.o: hash.c
	gcc -c hash.c
lex.yy.o: lex.yy.c
	gcc -Wall -Wextra -O3 -c lex.yy.c
lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l 
clean:
	rm *.o lex.yy.c etapa1
