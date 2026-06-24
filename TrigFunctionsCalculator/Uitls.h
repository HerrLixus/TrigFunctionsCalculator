#pragma once
#include "ErrorHandling.h"


namespace Utils
{
	/// <summary>
	/// Available trigonometric functions
	/// </summary>
	enum Functions { Sin, Cos, Tan, Cot, Sec, Csc, Arcsin, Arccos, Arctan, Arccot, Arcsec, Arccsc };


	static Result<std::tuple<std::ifstream, std::ofstream, std::ofstream>>
		openIOFiles(const std::string& inputFilename, const std::string& outputFilename);

	static Result<std::ifstream> openInFile(const std::string& filename);

	static Result<std::ofstream> openOutFile(const std::string& filename);


	///<summary>Checks whether input data is in correct format and converts it into internal format</summary>
	static Result<std::tuple<Functions, double, double>>
		validateInputFormat(const std::string& name, const std::string& x, const std::string& precision); 

	static bool validateDouble(const std::string& number);

	/// <summary>Dispatches corresponding function and evaluates it</summary>
	static Result<double> evaluate(Functions name, const double x, const double precision);
};