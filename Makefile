etapa2: lex.yy.o main.o hash.o y.tab.o
	gcc -Wall -Wextra -O3 -o etapa2 lex.yy.o y.tab.o main.o hash.o
main.o: main.c
	gcc -Wall -Wextra -O3 -c main.c
hash.o: hash.c
	gcc -Wall -Wextra -O3 -c hash.c
y.tab.o : y.tab.c
	gcc -Wall -Wextra -O3 -c y.tab.c
y.tab.c : parser.y
	yacc -d parser.y
lex.yy.o: lex.yy.c
	gcc -Wall -Wextra -O3 -c lex.yy.c
lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l
clean:
	rm *.o lex.yy.c y.tab.c etapa2
