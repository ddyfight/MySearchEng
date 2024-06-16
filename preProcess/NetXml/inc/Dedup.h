#ifndef __DEDUP_H
#define __DEDUP_H

#include "head.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <bitset>
#include <boost/functional/hash.hpp>
#include <cmath>

using namespace std;

#define SIMHASH_BITS 64 // Simhash指纹的位数

class Dedup
{
public:
    Dedup();
    Dedup(const std::string& outputFilename);
    ~Dedup();

    // 将文章内容分割为单词
    vector<std::string> splitWords(const std::string &content);

    // 计算特征的哈希值，并更新权重向量
    void addWeightedHashes(const std::string &feature, std::vector<int> &weights);

    // 生成Simhash指纹
    std::bitset<SIMHASH_BITS> computeSimhash(const std::vector<std::string> &words);

    // 计算两个Simhash指纹之间的汉明距离
    int hammingDistance(const std::bitset<SIMHASH_BITS> &a, const std::bitset<SIMHASH_BITS> &b);

    // 从文件中读取文章内容
    bool readArticlesFromFile(const std::string &filename, std::vector<std::string> &articles);

    // 添加文章
    bool addArticle(const std::string &content);

    // 将文章保存到文件
    void saveArticleToFile(const std::string &content);

private:
    std::vector<std::string> articles;                // 存储文章内容
    std::vector<std::bitset<SIMHASH_BITS>> simhashes; // 存储Simhash指纹

    const std::string outputFilename;

};

#endif // __DEDUP_H
