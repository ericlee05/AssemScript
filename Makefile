CC = g++
TARGET = assemscript

assemscript : main.o Token.o ExceptionManager.o SyntaxMatch.o AssemRuntime.o
	$(CC) -o $(TARGET) build/main.o build/Token.o build/ExceptionManager.o build/SyntaxMatch.o build/AssemRuntime.o

main.o : src/main.cpp
	$(CC) -c -o build/main.o src/main.cpp

Token.o : src/interpreter/Token.cpp
	$(CC) -c -o build/Token.o src/interpreter/Token.cpp

ExceptionManager.o : src/interpreter/ExceptionManager.cpp
	$(CC) -c -o build/ExceptionManager.o src/interpreter/ExceptionManager.cpp

SyntaxMatch.o : src/interpreter/SyntaxMatch.cpp
	$(CC) -c -o build/SyntaxMatch.o src/interpreter/SyntaxMatch.cpp

AssemRuntime.o : src/interpreter/AssemRuntime.cpp
	$(CC) -c -o build/AssemRuntime.o src/interpreter/AssemRuntime.cpp
