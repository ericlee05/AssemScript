/*
  AssemScript 1.0 - AssemRuntime.h
  인터프리터 런타임 헤더파일
*/

#pragma once
#include <iostream>
#include "SyntaxMatch.h"
#include <vector>

struct Asset {
  int id;
  vector<int> assetValues;
  
  Asset(int i, vector<int> values){
    id = i;
    assetValues = values;
  }
};

class AssemRuntime{
  private :
    vector<Syntax> syntaxList;
    vector<Asset> assetStore;

    int memorySize;
    int* memory;
    int cursor;

    int stringToInt(string);
  
  public :
    AssemRuntime(vector<Syntax>, int);
    
    void destory();

    int getMem(int);

    void setMem(int, int);

    void addAsset(int, vector<int>);

    void copyAsset(int, int);

    void execute();

};