/*
  AssemScript 1.0 - Token.h
  인터프리터 토큰 헤더파일
*/

#include <iostream>
using namespace std;

// Token struct
struct Token {
  string txt;
  int type;
  
  Token(string s, int t){
    txt = s;
    type = t;
  }
};

// Token types
enum TokenType {
  NONE = 0, // 아무것도 아님
  INT, // 포인터 값 및 포인터가 가리키는 값

  // 전처리문
  PREPROCESS_SYMBOL, // 전처리 지시문 기호(# 기호)
  STRING, // 전처리문에 사용되는 문자열  

  // 명령어 셋
  _MOV, NXT, PRV,
  _RPT, RPT_START, RPT_END, CUR,
  _CAL,
  _VAL, VAL_SUM, VAL_SUB
};

// 토큰 가져오기
Token nextToken(string);

// 다음 char 가져오기
char nextChar(string);

