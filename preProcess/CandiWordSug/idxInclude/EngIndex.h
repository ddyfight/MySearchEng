#ifndef __ENGINDEX_H
#define __ENGINDEX_H

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

class EngIndex
{
public:
    EngIndex();
    ~EngIndex();

    void buildIndex();

private:
    //加载词典
    vector<pair<string,int>> src;
    //暂存索引
    unordered_map<string,set<int>> idx;

    //文件输入输出流
    ifstream fin;
    ofstream fout;
};

#endif // __ENGINDEX_H