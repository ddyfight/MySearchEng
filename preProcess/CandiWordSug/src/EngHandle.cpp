#include "../include/EngHandle.h"

using namespace std;

void EngHandle::initStopWords()
{
    inFile.open("../Statics/stop_words_eng.txt");
    if (!inFile)
    {
        std::cerr << "Unable to open StopWordList" << std::endl;
        return;
    }
    string word;
    while (inFile >> word)
    {
        stopWords->insert(word);
    }

    #if 0
    for (auto &stopWord : *stopWords)
    {
        cout << stopWord << endl;
    }
    #endif

    inFile.close();
};

// 读取词源统计词频
void EngHandle::readWords(const string &fileName)
{
    // 打开文件
    ifstream inFile(fileName);
    if (!inFile)
    {
        std::cerr << "Error opening input file." << std::endl;
        exit(EXIT_SUCCESS);
    }
    string word;

    // 开始读
    while (inFile >> word)
    {
        string temp;
        // 去除停用词
        if (stopWords->find(word) != stopWords->end())
        {   
            //cout<<"delete: "<<word<<"\n";
            continue;
        }

        // 去除标点符号，改为小写
        for (auto &ch : word)
        {
            if (isalpha(ch))
            {
                temp += tolower(ch);
            }
        }

        // 去除空字符串
        if (!temp.empty())
        { // 统计词频
            ++(*wordFreq)[temp];
        }
    }
};

// 生成词典文件
void EngHandle::creatDic(const string &fileName)
{   
    initStopWords();
    readWords(fileName);
    outFile.open("../Statics/EngDictionary.txt");
    if (!outFile)
    {
        cerr << "Error opening file " << fileName << endl;
    }
    for (auto &elem : *wordFreq)
    {
        outFile << elem.first << " " << elem.second << endl;
    }
    outFile.close();
};
