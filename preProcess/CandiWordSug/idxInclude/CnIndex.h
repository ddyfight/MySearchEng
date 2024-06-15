#ifndef __CNINDEX_H
#define __CNINDEX_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <cstdlib>

using namespace std;

class CnIndex
{
public:
    CnIndex();
    ~CnIndex();

    void buildIndex();
    size_t getByteNum_UTF8(const char byte);

private:
    // 加载词典
    vector<pair<string, int>> src;
    // 暂存索引
    unordered_map<string, set<int>> idx;

    // 文件输入输出流
    ifstream fin;
    ofstream fout;
};

#endif // __CNINDEX_H