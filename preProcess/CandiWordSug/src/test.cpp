#include "../include/head.h"

using namespace std;

int main()
{
    
    EngHandle handler;
    handler.creatDic("../Statics/The_Holy_Bible.txt");
    DictProducer producer;
    
    std::cout << "Hello world" << std::endl;
    return 0;
}

