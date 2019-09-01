default: CArray2D

CArray2D: CArray2D.c makefile
	gcc -o CArray2D -Wall -O0 -g CArray2D.c

CArray2DSimple: CArray2DSimple.c makefile
	gcc -o CArray2DSimple -Wall -O0 -g CArray2DSimple.c

CArray1DReverse: CArray1DReverse.c makefile
	gcc -o CArray1DReverse -Wall -O0 -g CArray1DReverse.c

clean:
	rm -f CArray2D
	rm -f CArray2DSimple
	rm -f CArray1DReverse
	rm -f *~

