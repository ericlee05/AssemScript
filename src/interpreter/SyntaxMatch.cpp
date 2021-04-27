/*
  AssemScript 1.0 - SyntaxMatch.cpp
  인터프리터 문법 매치 구현파일
*/

#include <iostream>
#include <vector>

#include "SyntaxMatch.h"
#include "Token.h"

using namespace std;

void _matcher(int* offsetP, int* rulesArr, int rulelen, int type, vector<Syntax>* syntaxResult, vector<AssemToken>* tokens){
  if((*offsetP) + (rulelen) <= (*tokens).size()){
      int vaild = 1;

      //cout << (*offsetP) << " to " << (*offsetP) + rulelen << endl;

      for(int i = (*offsetP); i < (*offsetP) + rulelen; i++){
        if((*tokens).at(i).type != ANY && (*tokens).at(i).type != rulesArr[i - (*offsetP)]){
          vaild = 0;
        }
      }

      if(vaild){
        vector<AssemToken> tokenArgs;
        for(int i = (*offsetP); i < (*offsetP) + rulelen; i++){
          //cout << (*tokens).at(i).txt << " ";

          tokenArgs.push_back((*tokens).at(i));
        }
      Syntax syntaxItem = {
        type, tokenArgs
      };

      (*syntaxResult).push_back(syntaxItem);
      //cout << " / Push item!" << endl;
      (*offsetP) += rulelen;
    }

  }
}

vector<Syntax> matchSyntax(vector<AssemToken> tokens){
  vector<Syntax> syntaxResult;

  // rules
  int preAsset1[] =  { PREPROCESS_SYMBOL, PREPROCESS_CMD, INT, STRING };

  int mov1[] =  { _MOV, INT };
  int mov2[] =  { _MOV, NXT };
  int mov3[] =  { _MOV, PRV };

  int rpt1[] =  { _RPT, INT, RPT_START, ANY, RPT_END };
  int rpt2[] =  { _RPT, CUR, RPT_START, ANY, RPT_END };

  int cal1[] = { _CAL };

  int val1[] = { _VAL, INT };
  int val2[] = { _VAL, VAL_SUM };
  int val3[] = { _VAL, VAL_SUM };

  // Checking
  int offset = 0;
  while(offset < tokens.size()){

    // preAsset
    _matcher(&offset, preAsset1, sizeof(preAsset1) / sizeof(int), PRE_ASSET, 
    &syntaxResult, &tokens);

    // mov
    _matcher(&offset, mov1, sizeof(mov1) / sizeof(int), MOV,
     &syntaxResult, &tokens);
    _matcher(&offset, mov2, sizeof(mov2) / sizeof(int), MOV,
     &syntaxResult, &tokens);
    _matcher(&offset, mov3, sizeof(mov3) / sizeof(int), MOV,
     &syntaxResult, &tokens);
    
    // rpt
    _matcher(&offset, rpt1, sizeof(rpt1) / sizeof(int), RPT, 
    &syntaxResult, &tokens);
    _matcher(&offset, rpt2, sizeof(rpt2) / sizeof(int), RPT,
     &syntaxResult, &tokens);
    
    // cal
    _matcher(&offset, cal1, sizeof(cal1) / sizeof(int), CAL, 
    &syntaxResult, &tokens);

    // val
    _matcher(&offset, val1, sizeof(val1) / sizeof(int), VAL,
     &syntaxResult, &tokens);
    _matcher(&offset, val2, sizeof(val2) / sizeof(int), VAL,
     &syntaxResult, &tokens);
    _matcher(&offset, val3, sizeof(val3) / sizeof(int), VAL,
     &syntaxResult, &tokens);
    
    //cout << "================================" << endl; //<< "next token : " << tokens.at(offset).txt << "(" << tokens.at(offset).type << ")" << endl;
  }

  return syntaxResult;
}

// SyntaxMatch syntaxList[] = {
//   SyntaxMatch(PRE_ASSET, { PREPROCESS_SYMBOL, PREPROCESS_CMD, INT, STRING }, 4),

//   // MOV
//   SyntaxMatch(MOV, { _MOV, INT}),
//   SyntaxMatch(MOV, { _MOV, NXT}),
//   SyntaxMatch(MOV, { _MOV, PRV}),

//   // RPT
//   SyntaxMatch(RPT, { _RPT, INT, RPT_START, ANY, RPT_END }),
//   SyntaxMatch(RPT, { _RPT, CUR, RPT_START, ANY, RPT_END }),
  
//   // CAL
//   SyntaxMatch(CAL, { _CAL }),

//   // VAL
//   SyntaxMatch(VAL, { _VAL, INT }),
//   SyntaxMatch(VAL, { _VAL, VAL_SUM }),
//   SyntaxMatch(VAL, { _VAL, VAL_SUB })
// };
