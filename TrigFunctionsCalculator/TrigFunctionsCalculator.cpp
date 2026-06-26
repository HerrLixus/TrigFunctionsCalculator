#include <iostream>
#include <sstream>
#include "Utils.h"
#include "IOModule.h"

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
        std::string line;

        int lineCounter = 0;
        while (std::getline(inputstream, line))
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
            
            Result<std::tuple<Functions, double, double>> res =
                Utils::validateInputFormat(segments[0], segments[1], segments[2]);
            res.setLine(lineCounter);

            if (!res.isSuccess())
            {
                resultPrinter.printResult(res);
                continue;
            }

            Functions name;
            double x;
            double precision;

            std::tie(name, x, precision) = res.getValue();

            Result<double> result = Utils::evaluate(name, x, precision);
            result.setLine(lineCounter);
            
            resultPrinter.printResult(result);
        }
    }
    else if (argc == 4)
    {
        Result<std::tuple<Functions, double, double>> res =
            Utils::validateInputFormat(argv[1], argv[2], argv[3]);

        if (!res.isSuccess())
        {
            resultPrinter.printResult(res);
            return 0;
        }

        Functions name;
        double x;
        double precision;

        std::tie(name, x, precision) = res.getValue();

        Result<double> result = Utils::evaluate(name, x, precision);

        resultPrinter.printResult(result);
    }
    else
    {
        Result<bool> res;
        res.addError(Error(WrongArgumentCountConsole));
        resultPrinter.printResult(res);
    }

    return 0;
}