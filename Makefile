CC = g++
TARGET = assemscript

assemscript : main.o
	$(CC) -o $(TARGET) build/main.o

main.o : src/main.cpp
	$(CC) -c -o build/main.o src/main.cpp