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

  int tokenSize = 1;
  cout << "first malloc" << endl;
  Token* tokens = (Token*)malloc(sizeof(Token) * tokenSize);
  Token firstToken = nextToken(code);
  *tokens = firstToken;
  cout << "addr : " << &firstToken << endl;
  cout << "finished assign" << endl;

  // parse tokens
  while(1){
    Token* tok =(Token*) malloc(sizeof(Token));
    *tok = nextToken(code);

    if((*tok).type == CEOF) break;

    if((*tok).txt != ""){
      cout << "before realloc" << endl;
      tokens = (Token*)realloc(tokens, sizeof(Token) * (tokenSize + 1)); // 공간 1개 늘리기
      cout << "after realloc" << endl;
      tokens[tokenSize] = *tok;
      tokenSize++;
    }
  }

  // access tokens
  for(int i = 0; i < tokenSize; i++){
    cout << "access realloc" << endl;
    Token token = tokens[i];
    cout << "Type : " << token.type << " / Txt : " << token.txt << endl;
    //free(tokens + i);
  }
  free(tokens);

  // 종료시간
  time_t finishTimestamp = time(0);

  cout << "\n---- AssemScript Finished (" << finishTimestamp - startTimestamp << "ms) ----" << endl;
  
  getchar();
}