#include <iostream>
#include "Utils.h"
#include "IOModule.h"

int main()
{
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());

    Result<double> res = Utils::evaluate(SEC, -32, 0.0000000001);

    ResultPrinter resprinter;
    resprinter.printResult(res);

    return 0;
}

int testMethod(int x)
{
    return x;
}