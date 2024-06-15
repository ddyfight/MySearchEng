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

class EngHandle;

class DictProducer
{
public:
    DictProducer() {}
    ~DictProducer() {}

    void createIndex();
    void store();

private:
    //将词典加载到vector
    vector<string> dic;

    //根据词典生成单字索引
    unordered_map<string, set<int>> index;
    
    //将单字索引存入文件
    ofstream outFile;

    EngHandle *handle;
};

#endif