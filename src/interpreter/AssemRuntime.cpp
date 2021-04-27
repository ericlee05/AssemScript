/*
  AssemScript 1.0 - AssemRuntime.cpp
  인터프리터 런타임 구현파일
*/

#include <iostream>
#include <math.h>
#include "SyntaxMatch.h"
#include "AssemRuntime.h"
#include <vector>

AssemRuntime::AssemRuntime(vector<Syntax> list, int memSize){
  cursor = 0;
  memorySize = memSize;
  memory = (int*)malloc(memorySize * sizeof(int));
  for(int i = 0; i < memSize; i++)
    memory[i] = 0; // 메모리 초기화

  syntaxList = list;
}

int AssemRuntime::stringToInt(string str){
  int n = 0;
  int unit = 1;
  for(int i = 0; i < str.length(); i++){
    if(str.at(i) == '-') continue;

    n += (str.at(i) - 48) * unit;
    unit *= 10;
  }
  if(str.at(0) == '-') n = -(n);

  return n;
}

void AssemRuntime::destory(){
  free(memory);
}

int AssemRuntime::getMem(int pos){
  int absoluteCenter = memorySize / 2;
  int absolutePosition = absoluteCenter + pos;
  
  return memory[absolutePosition];
}

void AssemRuntime::setMem(int pos, int val){
  int absoluteCenter = memorySize / 2;
  int absolutePosition = absoluteCenter + pos;

  memory[absolutePosition] = val;
}

void AssemRuntime::addAsset(int id, vector<int> values){
  Asset asset = Asset(id, values);
  assetStore.push_back(asset);
}

void AssemRuntime::copyAsset(int id, int copyTo){
  for(int i = 0; i < assetStore.size(); i++){
    if(assetStore.at(i).id == id){

      for(int j = 0; j < assetStore.at(i).assetValues.size(); j++){
        setMem(copyTo + j, assetStore.at(i).assetValues.at(j));
      }

    }
  }
}

void AssemRuntime::execute(){
  // 문법 접근
  for(int syntaxIndex = 0; syntaxIndex < syntaxList.size(); syntaxIndex++){
    Syntax syntax = syntaxList.at(syntaxIndex);
    //cout << "Current Cursor : " << cursor << " / value " << getMem(cursor) << endl;

    // 명령어 분류
    switch(syntax.type){
      case PRE_ASSET : {
        vector<int> assetData;
        if(syntax.args.at(3).type == INT){
          assetData.push_back(stringToInt(syntax.args.at(3).txt));
        } else if(syntax.args.at(3).type == STRING){
          for(int i = 0; i < syntax.args.at(3).txt.length(); i++){
            assetData.push_back(syntax.args.at(3).txt.at(i));
          }
        }

        Asset newAsset = Asset(stringToInt(syntax.args.at(2).txt), assetData);
        assetStore.push_back(newAsset);
      }
        break;
      case MOV :{
        int prevCur = cursor;
        if(syntax.args.at(1).type == INT){
          cursor = stringToInt(syntax.args.at(1).txt);
        }else if(syntax.args.at(1).type == NXT){
          cursor++;
        }else if(syntax.args.at(1).type == PRV){
          cursor--;
        }
        //cout << "cursor changed from " << prevCur << " to " << cursor << endl;
      }
        break;
      case RPT :{

      }
        break;
      case CAL :{
        int callNum = getMem(0);
      }
        break;
      case VAL :{
        int prevVal = getMem(cursor);
        if(syntax.args.at(1).type == INT){
          setMem(cursor, stringToInt(syntax.args.at(1).txt));
        }else if(syntax.args.at(1).type == VAL_SUM){
          setMem(cursor, getMem(cursor) + 1);
        }else if(syntax.args.at(1).type == VAL_SUB){
          setMem(cursor, getMem(cursor) - 1);
        }
        //cout << "value changed from " << prevVal << " to " << getMem(cursor) << endl;
      }
        break;
    }

    //cout << "Type : " << token.type << " / Txt : \'" << token.txt << "\'" << endl;

  }
}