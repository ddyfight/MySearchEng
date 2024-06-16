#include <iostream>
#include "../inc/head.h"
#include "../inc/Dedup.h"

using namespace std;


int main()
{
    std::cout << "Hello world" << std::endl;
    const std::string inputFilename = "../Statics/pagelib.xml";
    const std::string outputFilename = "../Statics/deduplicated.xml";

    Dedup deup(outputFilename);

    std::vector<std::string> articles;

    if (!deup.readArticlesFromFile(inputFilename, articles)) {
        return 1; // 读取文件失败，返回错误码
    }

    for (const auto& article : articles) {
        deup.addArticle(article);
    }

    return 0;
}

