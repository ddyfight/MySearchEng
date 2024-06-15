#ifndef __DICTPRODUCER_H
#define __DICTPRODUCER_H

#include "head.h"
#include "EngHandle.h"
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cstdlib>

using namespace std;

class DictProducer
{
public:
    DictProducer() {}
    ~DictProducer() {}

    void engHandler();
    void cnHandler();

private:
    //将词典加载到vector
    vector<string> engDic;
    vector<string> cnDic;

    //根据词典生成单字索引
    unordered_map<string, set<int>> eng_Index;
    unordered_map<string, set<int>> cn_Index;
    
    //将单字索引存入文件
    ofstream enOutFile;
    ofstream cnOutFile;
};

#endif