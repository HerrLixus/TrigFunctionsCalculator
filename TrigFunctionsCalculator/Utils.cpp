#include <fstream>
#include <tuple>

#include <iomanip>
#include <ctime>
#include <sstream>

#include <iostream>

#include "Utils.h"

namespace Utils
{

	Result<std::ifstream> openInFile(const std::string& filename)
	{
		Result<std::ifstream> res;
		std::ifstream input = std::ifstream(filename);

		if (input.is_open())
			res.setValue(std::move(input));
		else
			res.addError(Error(ErrorType::inFileOpenFail, -1));

		return res;
	}

	Result<std::ofstream> openOutFile(const std::string& filename)
	{
		Result<std::ofstream> res;
		std::ofstream output = std::ofstream(filename);

		if (output.is_open())
			res.setValue(std::move(output));
		else
			res.addError(Error(ErrorType::outFileCreateFail, -1));

		return res;
	}

	Result<std::tuple<std::ifstream, std::ofstream, std::ofstream>>
		openIOFiles(const std::string& inputFilename, const std::string& outputFilename)
	{
		Result<std::tuple<std::ifstream, std::ofstream, std::ofstream>> res;

		Result<std::ifstream> input = openInFile(inputFilename);
		if (!input.isSuccess())
			res.addError(Error(ErrorType::inFileOpenFail, -1));

		Result<std::ofstream> output = openOutFile(outputFilename);
		if (!output.isSuccess())
			res.addError(Error(ErrorType::outFileCreateFail, -1));

		std::time_t t = std::time(nullptr);
		std::tm tm;
		localtime_s(&tm, &t);

		std::stringstream ss;
		ss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S") << ".txt";

		std::cout << ss.str() << std::endl;

		Result<std::ofstream> logFile = openOutFile(ss.str());
		if (!logFile.isSuccess())
			res.addError(Error(ErrorType::logFileCreateFail, -1));

		res.setValue(std::make_tuple(std::move(input.getValue()), std::move(output.getValue()), std::move(logFile.getValue())));

		return res;
	}
}