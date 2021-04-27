/*
  AssemScript 1.0 - main.cpp
  인터프리터 메인
*/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>

#include "./interpreter/SyntaxMatch.h"
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

  vector<AssemToken> tokens;
  struct AssemToken tok = nextToken(code);
  while(tok.type != CEOF){
    if(tok.type != 0 && tok.txt != ""){
      tokens.push_back(tok);
    }
    tok = nextToken(code);
  }

  // 토큰 처리
  vector<Syntax> processedSyntaxList = matchSyntax(tokens);
  
  //토큰 접근 
  for(int i =0; i < processedSyntaxList.size(); i++){
    Syntax syntax = processedSyntaxList.at(i);
    cout << "Syntax " << syntax.type << " :" << endl;
    for(int i =0; i < syntax.args.size(); i++){
      AssemToken token = syntax.args.at(i);
      cout << "Type : " << token.type << " / Txt : \'" << token.txt << "\'" << endl;
    }
    cout << endl;
  }

  // 종료시간
  time_t finishTimestamp = time(0);

  cout << "\n---- AssemScript Finished (" << finishTimestamp - startTimestamp << "ms) ----" << endl;
  
  getchar();
}