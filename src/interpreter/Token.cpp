/*
  AssemScript 1.0 - Token.cpp
  인터프리터 토큰 구현파일
*/

#include <map>
#include "Token.h"
#include "ExceptionManager.h"

char c = ' ';
int pos = 0;

char nextChar(string srcString){
  if(pos == srcString.length()) return '\0';
  char c = srcString.at(pos++);
  return c;
}

Token nextToken(string srcString){
  string tokenString("");
  
  c = nextChar(srcString);

  while(c == ' ') c = nextChar(srcString);

  if(c == '/'){ // 주석
    c = nextChar(srcString);
    if(c == '/'){ // 주석인 경우
      while(c != '\n') c = nextChar(srcString);
    }else{ // 주석이 아닌 경우, 즉 잘못된 경우
      showException(srcString, pos, "Wrong Token");
    }
  }else if(c == '#'){ // 전처리문
    char newC = c;
    return Token(string{newC}, PREPROCESS_SYMBOL);
  }else if('0' <= c && c <= '9'){ // 숫자
    if(c == '0') return Token("0", INT);
    

    while('0' <= c && c <= '9'){
      char newC = c;
      char tmp[4] = {newC};
      tokenString.append(string(tmp));

      c = nextChar(srcString);
    }
    return Token(tokenString, INT);
  }else if(c == '\"'){ // 문자열
    c = nextChar(srcString);
    while(c != '\"'){
      char newC = c;
      tokenString.append(string({newC}));

      c = nextChar(srcString);
    }
    return Token(tokenString, STRING);
  }else if(c == '{' || c == '}'){ // 반복문
    char newC = c;
    tokenString.append(string({newC}));

    switch(c){
      case '{' : 
        return Token(tokenString, RPT_START);
        break;
      case '}' : 
        return Token(tokenString, RPT_END);
        break;
    }
  }else if(('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')){ // 식별자 및 명령어
    while(('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')){
      char newC = c;
      char tmp[4] = {newC};
      tokenString.append(string(tmp));

      c = nextChar(srcString);
    }
    
    map<string, int> commandSet;
    commandSet.insert(make_pair("MOV", _MOV));
    commandSet.insert(make_pair("nxt", NXT));
    commandSet.insert(make_pair("prv", PRV));

    commandSet.insert(make_pair("RPT", _RPT));
    commandSet.insert(make_pair("cur", CUR));

    commandSet.insert(make_pair("CAL", _CAL));

    commandSet.insert(make_pair("VAL", _VAL));
    
    if(commandSet.find(tokenString) == commandSet.end()){
      map<string, int> preprocessSet;
      preprocessSet.insert(make_pair("asset", PREPROCESS_CMD));

      if(preprocessSet.find(tokenString) == preprocessSet.end())
        return Token(tokenString, NONE);

      return Token(tokenString, preprocessSet[tokenString]);
    }

    return Token(tokenString, commandSet[tokenString]);
  }else if(c == '+' || c == '-'){ // 값 또는 연산자
    char cFirst = c;
    c = nextChar(srcString);
    char cSecond = c;

    tokenString.append(string({cFirst}));
    tokenString.append(string({cSecond}));

    if(tokenString == "++"){
      return Token(tokenString, VAL_SUM);
    }else if(tokenString == "--"){
      return Token(tokenString, VAL_SUB);
    }else{
      if(cFirst == '-' && '1' <= cSecond && cSecond <= '9'){ // 숫자
        c = nextChar(srcString);
        while('0' <= c && c <= '9'){
          char newC = c;
          tokenString.append(string({newC}));

          c = nextChar(srcString);
        }
        return Token(tokenString, INT);
      }else{
        string errorString;
        errorString.append(tokenString);
        errorString.append(" is invaild operator");
        showException(srcString, pos, errorString);
      }
    }
  }else if(c == '\0'){ // EOF
    return Token("\0", CEOF);
  }else{ // Others
    return Token("", NONE);
  }
}
