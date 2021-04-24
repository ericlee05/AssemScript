#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

#include "./interpreter/Token.h"

using namespace std;

int main(){
  string code("");

  ifstream codeReader;
  codeReader.open("HelloWorld.asc");
  if(codeReader.is_open()){
    while(!codeReader.eof()){
      string line;
      getline(codeReader, line);
      line.append("\n");

      code.append(line);
    }
    //code.append("\0");
    codeReader.close();
  } else {
    printf("File not found");
    exit(0);
  }

  /*char testC = ' ';
  while(testC != '\0'){
    testC = nextChar(code);
    printf("%c", testC);
  }*/
  
  getchar();
}