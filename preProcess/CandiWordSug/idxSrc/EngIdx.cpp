#include <iostream>
#include "../idxInclude/EngIndex.h"
#include <utility>

using namespace std;

EngIndex::EngIndex()
{
    src = new vector<pair<string, int>>();
    idx = new unordered_map<string, set<int>>();
}

EngIndex::~EngIndex()
{
    if (src != nullptr)
    {
        delete src;
        src = nullptr;
    }
    if (idx != nullptr)
    {
        delete idx;
        idx = nullptr;
    }
}

void EngIndex::buildIndex()
{   
    //读取词典
    fin.open("../Statics/EngDictionary.txt");
    if (!fin)
    {
        std::cerr << "Unable to open file " << "\n";
        return;
    }
    string word;
    int frequency;
    while (fin >> word >> frequency)
    {
        src->emplace_back(word, frequency);
    }

    //生成索引
    for (auto &elem : *src)
    {
        (*idx)[elem.first].insert(elem.second);
    }

    //输出索引
    fout.open("../Statics/EngIndex.txt");
    if (!fout)
    {
        cerr << "fout is not" << "\n";
    }

    for (auto &elem : *idx)
    {
        fout << elem.first << " ";
        for (auto &elem2 : elem.second)
        {
            fout << elem2 << " ";
        }
        fout << "\n";
    }

    fout.close();
    
    fin.close();
}
