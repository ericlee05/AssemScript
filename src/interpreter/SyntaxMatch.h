/*
  AssemScript 1.0 - SyntaxMatch.h
  인터프리터 문법 매치 헤더파일
*/

#pragma once
#include <iostream>
#include "Token.h"
#include <vector>

using namespace std;

typedef struct StructSyntax{
  int type;
  vector<AssemToken> args;
} Syntax;

enum SyntaxType{
  NONESYNTAX = 0,
  PRE_ASSET, // 전처리문 에셋
  
  // 명령문
  MOV, RPT, CAL, VAL
};

vector<Syntax> matchSyntax(vector<AssemToken>);