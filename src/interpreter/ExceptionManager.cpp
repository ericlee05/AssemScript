/*
  AssemScript 1.0 - ExceptionManager.cpp
  인터프리터 예외 관리자 구현파일
*/

#include <iostream>
#include "ExceptionManager.h"

using namespace std;

void showException(string code, int pos, string message){
  int line = 0;
  int relativePos = 0;
  for(int i = 0; i < code.length(); i++){
    if(i == pos){
      cout << message << " \'" << code.at(pos - 1) <<
       "\' at line " << line + 1 << ", pos " << relativePos -1 << endl;
    }
    relativePos++;
    if(code.at(i) == '\n'){
       line++;
       relativePos = 0;
    }
  }
}