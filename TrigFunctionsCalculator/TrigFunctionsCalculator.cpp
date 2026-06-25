#include <iostream>
#include "Utils.h"
#include <fstream>
#include "IOModule.h"

int main()
{
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());

    std::cout << "Hello World!\n";
    Range range = { RangeSegment(1, false, 2, true), RangeSegment(2, false, 3, true) };

    Result<std::tuple<std::ifstream, std::ofstream, std::ofstream>> i = Utils::openIOFiles("input.txt", "output.txt");
    
    ResultPrinter resprinter;
    resprinter.printResult(std::move(i));

    return 0;
}

int testMethod(int x)
{
    return x;
}