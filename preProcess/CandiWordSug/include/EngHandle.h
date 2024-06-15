#ifndef __ENGHANDLE_H
#define __ENGHANDLE_H

#include "head.h"
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

class EngHandle
{
public:
    EngHandle();
    ~EngHandle();

    // 初始化停用词表
    void initStopWords();

    // 读取词源统计词频
    void readWords(const string &fileName);

    // 生成词典文件
    void creatDic(const string &fileName);

private:
    // 使用set记录停用词
    set<string> *stopWords;

    // 使用map记录词频
    map<string, int> *wordFreq;

    // 文件读取流
    ifstream inFile;

    // 文件写入流
    ofstream outFile;
    
};

#endif // __ENGHANDLE_H