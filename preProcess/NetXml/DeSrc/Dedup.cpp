#include "../inc/head.h"
#include "../inc/Dedup.h"


using namespace std;

Dedup::Dedup(const std::string &outputFilename) : outputFilename(outputFilename)
{
}

Dedup::~Dedup()
{
}

// 将文章内容分割为单词
vector<std::string> Dedup::splitWords(const std::string &content)
{
    std::vector<std::string> words;
    std::istringstream stream(content);
    std::string word;
    while (stream >> word)
    {
        words.push_back(word);
    }
    return words;
}

// 计算特征的哈希值，并更新权重向量
void Dedup::addWeightedHashes(const std::string &feature, std::vector<int> &weights)
{
    size_t hash = boost::hash<std::string>()(feature);
    for (int i = 0; i < SIMHASH_BITS; ++i)
    {
        if (hash & (1ull << i))
            weights[i] += 1;
        else
            weights[i] -= 1;
    }
}

// 生成Simhash指纹
std::bitset<SIMHASH_BITS> Dedup::computeSimhash(const std::vector<std::string> &words)
{
    std::vector<int> weights(SIMHASH_BITS, 0);
    for (const auto &word : words)
    {
        addWeightedHashes(word, weights);
    }

    std::bitset<SIMHASH_BITS> hash;
    for (int i = 0; i < SIMHASH_BITS; ++i)
    {
        if (weights[i] > 0)
            hash.set(i);
    }
    return hash;
}

// 计算两个Simhash指纹之间的汉明距离
int Dedup::hammingDistance(const std::bitset<SIMHASH_BITS> &a, const std::bitset<SIMHASH_BITS> &b)
{
    return (a ^ b).count();
}

// 从文件中读取文章内容
bool Dedup::readArticlesFromFile(const std::string &filename, std::vector<std::string> &articles)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        if (!line.empty())
        {
            articles.push_back(line);
        }
    }

    return true;
}

// 添加文章
// bool Dedup::addArticle(const std::string &content)
// {
//     simhash::Simhasher simhash("../inc/include/dict/jieba.dict.utf8", "../inc/include/dict/hmm_model.utf8", "../inc/include/dict/idf.utf8", "../inc/include/dict/stop_words.utf8");
//     size_t topN = 5;
//     uint64_t u64 = 0;
//     auto newSimhash = simhash.make(content,topN,u64);

//     for (const auto &existingSimhash : (simhashes))
//     {
//         if (simhash::Simhasher::isEqual(newSimhash, existingSimhash, topN))
//         {
//             std::cout << "文章重复，未添加。" << std::endl;
//             return false;
//         }
//     }

//     articles.push_back(content);
//     simhashes.push_back(newSimhash);
//     std::cout << "文章已添加。" << std::endl;

//     saveArticleToFile(content);
//     return true;
// }
bool Dedup::addArticle(const std::string &content)
{
    auto words = splitWords(content);
    auto newSimhash = computeSimhash(words);

    for (const auto &existingSimhash : simhashes)
    {
        if (hammingDistance(newSimhash, existingSimhash) <= 10)
        {
            std::cout << "文章重复，未添加。" << std::endl;
            return false;
        }
    }

    articles.push_back(content);
    simhashes.push_back(newSimhash);
    std::cout << "文章已添加。" << std::endl;

    saveArticleToFile(content);
    return true;
}

// 将文章保存到文件
void Dedup::saveArticleToFile(const std::string &content)
{
    std::ofstream outFile(outputFilename, std::ios::app); // 追加模式
    if (!outFile)
    {
        std::cerr << "无法打开文件: " << outputFilename << std::endl;
        std::exit(1);
    }
    outFile << content << "\n"; // 每篇文章一行
}
