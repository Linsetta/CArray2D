default: CArray2D

CArray2D: CArray2D.c makefile
	gcc -o CArray2D -Wall -O0 -g CArray2D.c

clean:
	rm -f CArray2D
	rm -f *~

