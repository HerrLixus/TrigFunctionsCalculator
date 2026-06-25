#include <iostream>
#include "Ranges.h"

int main()
{
    std::cout << "Hello World!\n";
    Range range = { RangeSegment(1, false, 2, true), RangeSegment(2, false, 3, true) };
}

int testMethod(int x)
{
    return x;
}