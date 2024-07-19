output: main.o dochashtable.o MyList.o Heap.o
	g++ main.o dochashtable.o MyList.o Heap.o -o output
main.o: main.cpp
	g++ -c main.cpp
dochashtable.o: dochashtable.cpp dochashtable.h
	g++ -c dochashtable.cpp
MyList.o: MyList.cpp MyList.h
	g++ -c MyList.cpp
Heap.o: Heap.cpp Heap.h
	g++ -c Heap.cpp
clean:
	rm *.o output