#include "../include/head.h"
#include "../include/CnHandle.h"
#include "../include/head.h"
#include "../jieba/simhash/cppjieba/Jieba.hpp"

using namespace std;

int main()
{

    // EngHandle handler;
    // handler.creatDic("../Statics/The_Holy_Bible.txt");
    // DictProducer producer;

    CnHandle handler;
    handler.creatDic("../Statics/art");
}

#if 0
    for (const auto &entry : fs::directory_iterator("../Statics/art"))
    {
        if (entry.is_regular_file())
        {
            std::cout << entry.path() << std::endl;
        }
        std::cout << "Hello world" << "\n";
    }
#endif

// #if 0
//     ifstream inFile;
//     inFile.open("../Statics/cntest.txt");
//     cppjieba::Jieba jieba(DICT_PATH,
//                           HMM_PATH,
//                           USER_DICT_PATH,
//                           IDF_PATH,
//                           STOP_WORD_PATH);
//     vector<string> *words = new vector<string>();
//     string *s = new string();
//     while (inFile >> *s)
//     {
//         jieba.Cut(*s, *words, true);
//         for (auto &word : *words)
//         {
//             cout << word << "\n";
//         }
//         words->clear();
//     }
//     delete words;
//     delete s;
//     return 0;
//     #endif
