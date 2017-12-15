
bump:	bump.o heap.o minheap.o
	g++ -o bump bump.o heap.o minheap.o

bump.o:	heap.h bump.cpp minheap.h
	g++ -c bump.cpp

