#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <ctime>

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

  // 소요시간 측정
  time_t startTimestamp = time(0);

  Token tok = nextToken(code);
  while(tok.type != CEOF){
    if(tok.type != 0 && tok.txt != "")
      cout << "Type : " << tok.type << " / Txt : " << tok.txt << endl;
    tok = nextToken(code);
  }

  // 종료시간
  time_t finishTimestamp = time(0);

  cout << "\n---- AssemScript Finished (" << finishTimestamp - startTimestamp << "ms) ----" << endl;
  
  getchar();
}