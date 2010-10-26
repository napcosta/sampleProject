# MAKEFILE

main: RBT.o main.o
	gcc -o $@ $+

RBT.o: RBT.c RBT.h
	gcc -g -c $< -o $@

main.o: main.c RBT.h
	gcc -g -c $< -o $@

clean:
	rm -f *.o main
