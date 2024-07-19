output: main.o inode.o vfs_tree.o MyVector.o MyQueue.o MyStack.o
	g++ main.o inode.o vfs_tree.o MyVector.o MyQueue.o MyStack.o -o output
main.o: main.cpp
	g++ -c main.cpp
inode.o: inode.cpp inode.h
	g++ -c inode.cpp
vfs_tree.o: vfs_tree.cpp vfs_tree.h
	g++ -c vfs_tree.cpp
MyVector.o: MyVector.cpp MyVector.h
	g++ -c MyVector.cpp
MyQueue.o: MyQueue.cpp MyQueue.h
	g++ -c MyQueue.cpp
MyStack.o: MyStack.cpp MyStack.h
	g++ -c MyStack.cpp
clean:
	rm *.o output