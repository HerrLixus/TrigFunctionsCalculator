#include <fstream>
#include <tuple>

#include <iomanip>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include <memory>

#include "Utils.h"
#include "Calculator.h"

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
			Error error(ErrorType::inFileOpenFail);
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
			Error error(ErrorType::outFileCreateFail);
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
			Error inputError = Error(ErrorType::inFileOpenFail);
			inputError.setFilename(inputFilename);
			res.addError(inputError);

			return res;
		}

		Result<std::ofstream> output = openOutFile(outputFilename);
		if (!output.isSuccess())
		{
			Error outputError = Error(ErrorType::outFileCreateFail);
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
			Error logError = Error(ErrorType::logFileCreateFail);
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
			{"cos", Functions::COS},
			{"sin", Functions::SIN},
			{"tan", Functions::TAN},
			{"cot", Functions::COT},
			{"sec", Functions::SEC},
			{"csc", Functions::CSC},

			{"arccos", Functions::ARCCOS},
			{"arcsin", Functions::ARCSIN},
			{"arctan", Functions::ARCTAN},
			{"arccot", Functions::ARCCOT},
			{"arcsec", Functions::ARCSEC},
			{"arccsc", Functions::ARCCSC}
		};

		Functions func;
		double arg;
		double prec;

		auto funcId = funcIds.find(name);
		if (funcId == funcIds.cend())
			res.addError(Error(WrongFuncIdentifier));
		else
			func = funcId->second;

		if (!validateDouble(x))
			res.addError(Error(WrongArgFormat));
		else
			arg = std::stod(x);

		if (!validateDouble(precision))
			res.addError(Error(WrongPrecisionFormat));
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
		std::unordered_map<Functions, std::unique_ptr<Evaluator>> funcs;

		funcs[Functions::SIN] = std::move(std::make_unique<Sin>());
		funcs[Functions::COS] = std::move(std::make_unique<Cos>());
		funcs[Functions::TAN] = std::move(std::make_unique<Tan>());
		funcs[Functions::COT] = std::move(std::make_unique<Cot>());
		funcs[Functions::SEC] = std::move(std::make_unique<Sec>());
		funcs[Functions::CSC] = std::move(std::make_unique<Csc>());

		funcs[Functions::ARCSIN] = std::move(std::make_unique<Arcsin>());
		funcs[Functions::ARCCOS] = std::move(std::make_unique<Arccos>());
		funcs[Functions::ARCTAN] = std::move(std::make_unique<Arctan>());
		funcs[Functions::ARCCOT] = std::move(std::make_unique<Arccot>());
		funcs[Functions::ARCSEC] = std::move(std::make_unique<Arcsec>());
		funcs[Functions::ARCCSC] = std::move(std::make_unique<Arccsc>());
		

		return funcs[name]->evaluate(x, precision);
	}
}