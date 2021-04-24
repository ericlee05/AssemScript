CC = g++
TARGET = assemscript

assemscript : main.o Token.o
	$(CC) -o $(TARGET) build/main.o build/Token.o

main.o : src/main.cpp
	$(CC) -c -o build/main.o src/main.cpp

Token.o : src/interpreter/Token.cpp
	$(CC) -c -o build/Token.o src/interpreter/Token.cpp