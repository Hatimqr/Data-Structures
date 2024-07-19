output: main.o matcomp.o linkedmatrix.o
	g++ main.o matcomp.o linkedmatrix.o -o output
main.o: main.cpp
	g++ -c main.cpp
matcomp.o: matcomp.cpp matcomp.h
	g++ -c matcomp.cpp
linkedmatrix.o: linkedmatrix.cpp linkedmatrix.h
	g++ -c linkedmatrix.cpp
clean:
	rm *.o output