#include <iostream>
#include "../idxInclude/EngIndex.h"
#include <utility>
#include <myheader.h>

using namespace std;

EngIndex::EngIndex()
{
}

EngIndex::~EngIndex()
{
}

void EngIndex::buildIndex()
{

    // 读取词典
    fin.open("../Statics/EngDictionary.txt");
    if (!fin)
    {
        std::cerr << "Unable to open file " << "\n";
        return;
    }

    std::string word;
    int frequency;

    // 读取文件内容，逐行处理
    while (fin >> word >> frequency)
    {

        src.emplace_back(word, frequency);
    }

    for (auto elem : src)
    {
        cout << elem.first << " " << elem.second << "\n";
        sleep(1);
    }

    // 生成索引
    for (size_t i = 0; i < src.size(); ++i)
    {
        const std::string &word = (src)[i].first;
        for (char c : word)
        {
            // 将char转换为string
            std::string charStr(1, c);
            // 添加vector的下标到set中
            idx[charStr].insert(i);
        }
    }
    // 输出索引
    fout.open("../Statics/EngIndex.txt");
    if (!fout)
    {
        cerr << "fout is not" << "\n";
    }

    for (auto &elem : idx)
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
