#include <fstream>
#include <tuple>

#include <iomanip>
#include <ctime>
#include <sstream>

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
		{
			Error error(ErrorType::inFileOpenFail, -1);
			error.setFilename(filename);
			res.addError(error);
		}

		return res;
	}

	Result<std::ofstream> openOutFile(const std::string& filename)
	{
		Result<std::ofstream> res;
		std::ofstream output = std::ofstream(filename);

		if (output.is_open())
			res.setValue(std::move(output));
		else
		{
			Error error(ErrorType::outFileCreateFail, -1);
			error.setFilename(filename);
			res.addError(error);
		}

		return res;
	}

	Result<std::tuple<std::ifstream, std::ofstream, std::ofstream>>
		openIOFiles(const std::string& inputFilename, const std::string& outputFilename)
	{
		Result<std::tuple<std::ifstream, std::ofstream, std::ofstream>> res;

		Result<std::ifstream> input = openInFile(inputFilename);
		if (!input.isSuccess())
		{
			Error inputError = Error(ErrorType::inFileOpenFail, -1);
			inputError.setFilename(inputFilename);
			res.addError(inputError);
		}

		Result<std::ofstream> output = openOutFile(outputFilename);
		if (!output.isSuccess())
		{
			Error outputError = Error(ErrorType::outFileCreateFail, -1);
			outputError.setFilename(outputFilename);
			res.addError(outputError);
		}
			

		std::time_t t = std::time(nullptr);
		std::tm tm;
		localtime_s(&tm, &t);

		std::stringstream ss;
		ss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S") << ".txt";

		Result<std::ofstream> logFile = openOutFile(ss.str());
		if (!logFile.isSuccess())
		{
			Error logError = Error(ErrorType::logFileCreateFail, -1);
			logError.setFilename(ss.str());
			res.addError(logError);
		}

		res.setValue(std::make_tuple(std::move(input.getValue()), std::move(output.getValue()), std::move(logFile.getValue())));

		return res;
	}
}