/*
  AssemScript 1.0 - Token.cpp
  인터프리터 토큰 구현파일
*/

#include "Token.h"

char c = ' ';

Token nextToken(string srcString){
  string tokenString("");
  while(c == ' ') c = nextChar(srcString);

  if('0' <= c && c <= '9'){

  }
  return Token("Test", 0);
}

int pos = 0;
char nextChar(string srcString){
  if(pos == srcString.length()) return '\0';
  return srcString.at(pos++);
}