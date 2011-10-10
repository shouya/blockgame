all: testsdl perror syntaxtst


testsdl: testsdl.c
	gcc -Wall -ansi -o $@ $< -lSDLmain -lSDL

perror: perror.c
	gcc -Wall -ansi -o $@ $<

syntaxtst: syntaxtst.c
	gcc -Wall -ansi -o $@ $<

clean:
	rm -f *.o
	rm -f testsdl perror syntaxtst