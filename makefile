default: CArray2D CArray2DSimple CArray1DReverse CArray1DPointersAndIndices CArray1DSort CLinkedList CBinaryTree

CArray2D: CArray2D.c makefile
	gcc -o CArray2D -Wall -O0 -g CArray2D.c

CArray2DSimple: CArray2DSimple.c makefile
	gcc -o CArray2DSimple -Wall -O0 -g CArray2DSimple.c

CArray1DReverse: CArray1DReverse.c makefile
	gcc -o CArray1DReverse -Wall -O0 -g CArray1DReverse.c

CArray1DPointersAndIndices: CArray1DPointersAndIndices.c makefile
	gcc -o CArray1DPointersAndIndices -Wall -O0 -g CArray1DPointersAndIndices.c

CArray1DSort: CArray1DSort.c makefile
	gcc -o CArray1DSort -Wall -O0 -g CArray1DSort.c

CLinkedList: CLinkedList.c makefile
	gcc -o CLinkedList -Wall -O0 -g CLinkedList.c

CBinaryTree: CBinaryTree.c makefile
	gcc -o CBinaryTree -Wall -O0 -g CBinaryTree.c

clean:
	rm -f CArray2D
	rm -f CArray2DSimple
	rm -f CArray1DReverse
	rm -f CArray1DSort
	rm -f CArray1DPointersAndIndices
	rm -f CLinkedList
	rm -f CBinaryTree
	rm -f *~

