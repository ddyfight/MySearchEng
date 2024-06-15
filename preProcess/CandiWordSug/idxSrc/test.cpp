#include <iostream>
#include "../idxInclude/CnIndex.h"
#include "../idxInclude/EngIndex.h"
#include <utility>


using namespace std;

int main()
{
    CnIndex index;
    index.buildIndex();
    // EngIndex index1;
    // index1.buildIndex();
    std::cout << "Hello world" << std::endl;

    return 0;
}

