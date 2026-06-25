#include <iostream>
#include <sstream>
#include "Utils.h"
#include "IOModule.h"

void processInputDataPortion(const ResultPrinter& resultPrinter,
    const std::string& function, const std::string& arg, const std::string& prec)
{
    Result<std::tuple<Functions, double, double>> res =
        Utils::validateInputFormat(function, arg, prec);

    if (!res.isSuccess())
    {
        resultPrinter.printResult(res);
        return;
    }

    Functions name;
    double x;
    double precision;

    std::tie(name, x, precision) = res.getValue();

    Result<double> result = Utils::evaluate(name, x, precision);

    resultPrinter.printResult(result);
}

void processInputFile(const ResultPrinter& resultPrinter, std::ifstream inputStream)
{
    std::string line;
    int lineCounter = 0;
    while (std::getline(inputStream, line))
    {
        std::stringstream ss(line);
        std::vector<std::string> segments;
        std::string token;
        while (ss >> token)
            segments.push_back(token);

        lineCounter++;

        if (segments.size() != 3)
        {
            Result<bool> res;
            res.addError(Error(WrongArgumentCountFile));
            res.setLine(lineCounter);
            resultPrinter.printResult(res);
            continue;
        }

        processInputDataPortion(resultPrinter, segments[0], segments[1], segments[2]);
    }
}

int main(int argc, char* argv[])
{
    ResultPrinter resultPrinter;

    if (argc == 3)
    {
        Result<std::tuple<std::ifstream, std::ofstream, std::ofstream>> files = Utils::openIOFiles(argv[1], argv[2]);

        if (!files.isSuccess())
        {
            resultPrinter.printResult(files);
            return 0;
        }
        
        std::tuple<std::ifstream, std::ofstream, std::ofstream> filestreams = std::move(files.getValue());

        resultPrinter.setStreams(std::move(std::get<1>(filestreams)), std::move(std::get<2>(filestreams)));

        std::ifstream inputstream = std::move(std::get<0>(filestreams));

        processInputFile(resultPrinter, std::move(inputstream));
    }
    else if (argc == 4)
    {
        processInputDataPortion(resultPrinter, argv[1], argv[2], argv[3]);
    }
    else
    {
        Result<bool> res;
        res.addError(Error(WrongArgumentCountConsole));
        resultPrinter.printResult(res);
    }

    return 0;
}
