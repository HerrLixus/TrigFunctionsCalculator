#pragma once
#include "ErrorHandling.h"
#include "Calculator.h"

namespace Utils
{
	Result<std::tuple<std::ifstream, std::ofstream, std::ofstream>>
		openIOFiles(const std::string& inputFilename, const std::string& outputFilename);

	Result<std::ifstream> openInFile(const std::string& filename);

	Result<std::ofstream> openOutFile(const std::string& filename);


	///<summary>Checks whether input data is in correct format and converts it into internal format</summary>
	Result<std::tuple<Functions, double, double>>
		validateInputFormat(const std::string& name, const std::string& x, const std::string& precision); 

	bool validateDouble(const std::string& number);

	/// <summary>Dispatches corresponding function and evaluates it</summary>
	Result<double> evaluate(Functions name, const double x, const double precision);
};