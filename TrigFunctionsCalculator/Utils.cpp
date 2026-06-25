#include <fstream>
#include <tuple>

#include <iomanip>
#include <ctime>
#include <sstream>
#include <unordered_map>

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


	Result<std::tuple<Functions, double, double>>
		validateInputFormat(const std::string& name, const std::string& x, const std::string& precision)
	{
		Result<std::tuple<Functions, double, double>> res;

		std::unordered_map<std::string, Functions> funcIds =
		{
			{"cos", Functions::Cos},
			{"sin", Functions::Sin},
			{"tan", Functions::Tan},
			{"cot", Functions::Cot},
			{"sec", Functions::Sec},
			{"csc", Functions::Csc},

			{"arccos", Functions::Arccos},
			{"arcsin", Functions::Arcsin},
			{"arctan", Functions::Arctan},
			{"arccot", Functions::Arccot},
			{"arcsec", Functions::Arcsec},
			{"arccsc", Functions::Arccsc}
		};

		Functions func;
		double arg;
		double prec;

		auto funcId = funcIds.find(name);
		if (funcId == funcIds.cend())
			res.addError(Error(WrongFuncIdentifier, -1));
		else
			func = funcId->second;

		if (!validateDouble(x))
			res.addError(Error(WrongArgFormat, -1));
		else
			arg = std::stod(x);

		if (!validateDouble(precision))
			res.addError(Error(WrongPrecisionFormat, -1));
		else
			prec = std::stod(precision);

		res.setValue(std::make_tuple(func, arg, prec));
		return res;
	}

	bool validateDouble(const std::string& number)
	{
		if (number.empty())
			return false;
		if (number.size() > 15)
			return false;

		int dotFlag = false;
		for (int i = 0; i < number.size(); i++)
		{
			if (number[i] == '.')
			{
				if (dotFlag) return false;
				dotFlag = true;
			}
			else if (!isdigit(number[i])) return false;
		}

		return true;
	}

	Result<double> evaluate(Functions name, const double x, const double precision)
	{
		Result<double> res;
		res.setValue(0.0);
		return res;
	}
}