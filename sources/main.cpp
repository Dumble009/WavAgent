// ----------STLのinclude----------
#include <iostream> // 入出力
#include "test_lib.h"

int main(void)
{
    std::cout << "Hello World" << std::endl;
    std::cout << "1 + 2 = " << testLib::add(1, 2) << std::endl;
}