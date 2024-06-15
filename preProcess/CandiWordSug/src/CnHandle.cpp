#include "../include/CnHandle.h"
#include "../include/head.h"
#include "../jieba/simhash/cppjieba/Jieba.hpp"

using namespace std;
namespace fs = std::filesystem;

const char *const DICT_PATH = "../jieba/dict/jieba.dict.utf8";
const char *const HMM_PATH = "../jieba/dict/hmm_model.utf8";
const char *const USER_DICT_PATH = "../jieba/dict/user.dict.utf8";
const char *const IDF_PATH = "../jieba/dict/idf.utf8";
const char *const STOP_WORD_PATH = "../jieba/dict/stop_words.utf8";

CnHandle::CnHandle()
{   
    stopWords = new set<string>();
    wordFreq = new unordered_map<string, int>;
}

CnHandle::~CnHandle()
{
    if (stopWords)
    {
        delete stopWords;
        stopWords = nullptr;
    }
    if (wordFreq)
    {
        delete wordFreq;
        wordFreq = nullptr;
    }
}

// 初始化停用词表
void CnHandle::initStopWords()
{
    inFile.open("../Statics/stop_words_cn.txt");
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
}

// 读取词源统计词频
// void CnHandle::readWords(const string &fileName)
// {
//     inFile.open(fileName);
//     if (!inFile)
//     {
//         cerr << "open fail" << fileName << "\n";
//         return;
//     }
//     vector<string> words;
//     string s;
//     while (getline(inFile, s))
//     {
//         jieba.Cut(s, words, true);
//         for (auto &word : words)
//         {
//             if (stopWords->find(word) == stopWords->end())
//             {
//                 (*wordFreq)[word]++;
//             }
//         }
//         words.clear();
//     }
//     inFile.close();
// }

// 生成词典文件
void CnHandle::creatDic(const string &filePath)
{
    initStopWords(); // 初始化停用词表
    cppjieba::Jieba jieba(DICT_PATH,
                          HMM_PATH,
                          USER_DICT_PATH,
                          IDF_PATH,
                          STOP_WORD_PATH);

    // 循环读目录生成词频
    for (const auto &entry : fs::directory_iterator(filePath))
    {
        if (entry.is_regular_file())
        {
            string fileName = entry.path().filename();
            inFile.open(entry.path());
            if (!inFile)
            {
                cerr << "open fail" << fileName << "\n";
                return;
            }
            vector<string> words;
            string s;
            while (getline(inFile, s))
            {
                jieba.Cut(s, words, true);
                for (auto &word : words)
                {
                    if (stopWords->find(word) == stopWords->end())
                    {
                        (*wordFreq)[word]++;
                    }
                }
                words.clear();
            }
            inFile.close();
        }
    }
    // DIR *dir = opendir(filePath.c_str());
    // if (dir == nullptr)
    // {
    //     std::cerr << "Failed to open directory: " << filePath << "\n";
    //     return;
    // }

    // struct dirent *entry;
    // while ((entry = readdir(dir)) != nullptr)
    // {
    //     // 过滤掉 "." 和 ".." 特殊条目
    //     if (std::strcmp(entry->d_name, ".") != 0 && std::strcmp(entry->d_name, "..") != 0)
    //     {
    //         cout << entry->d_name << "\n";
    //         string filePath1("../Statics/art/");
    //         filePath1.append(entry->d_name);
    //         readWords(filePath1);
    //     }
    // }
    // closedir(dir);

    // 生成词典
    outFile.open("../Statics/CnDictionary.txt");
    if (!outFile)
    {
        cerr << "Error opening file " << "\n";
    }
    for (auto &elem : *wordFreq)
    {
        outFile << elem.first << " " << elem.second << "\n";
    }
    outFile.close();
}
