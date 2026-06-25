#include <iostream>
#include "Utils.h"

int main()
{
    std::cout << "Hello World!\n";
    Range range = { RangeSegment(1, false, 2, true), RangeSegment(2, false, 3, true) };

    Result<std::tuple<std::ifstream, std::ofstream, std::ofstream>> i = Utils::openIOFiles("input.txt", "output.txt");
    std::cout << i.isSuccess() << std::endl;

    return 0;
}

int testMethod(int x)
{
    return x;
}