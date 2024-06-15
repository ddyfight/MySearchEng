#include <iostream>
#include "../idxInclude/CnIndex.h"
#include <myheader.h>

using namespace std;

CnIndex::CnIndex()
{
}

CnIndex::~CnIndex()
{
}

size_t CnIndex::getByteNum_UTF8(const char byte)
{
    int byteNum = 0;
    for (size_t i = 0; i < 6; ++i)
    {
        if (byte & (1 << (7 - i)))
            ++byteNum;
        else
            break;
    }
    return byteNum == 0 ? 1 : byteNum;
}

void CnIndex::buildIndex()
{
    // 读取词典
    fin.open("../Statics/CnDictionary.txt");
    if (!fin)
    {
        std::cerr << "Unable to open file " << "\n";
        return;
    }
    string word;
    int frequency;
    while (fin >> word >> frequency)
    {
        src.emplace_back(word, frequency);
    }

    int i = 0;
    // 生成索引
    for (auto elem : src)
    {
        string _word = elem.first;
        size_t charNums = _word.size() / getByteNum_UTF8(_word[0]);
        for (size_t _idx = 0, n = 0; n != charNums; ++_idx, ++n) // 得到字符数
        {
            // 按照字符个数切割
            size_t charLen = getByteNum_UTF8(_word[_idx]);
            string subWord = _word.substr(_idx, charLen); // 按照编码格式，进行拆分
            idx[subWord].insert(i);
            _idx += (charLen - 1);
        }
        i++;
    }

    // 输出索引
    fout.open("../Statics/CnIndex.txt");
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