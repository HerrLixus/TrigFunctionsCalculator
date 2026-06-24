#pragma once
#include <fstream>
#include <unordered_map>
#include <string>
#include "ErrorHandling.h"


/// <summary>
/// Responsible for outputting results in console or files 
/// </summary>
class ResultPrinter
{
private:
	bool isConsole;                                        ///<summary>Whether results are being outputted to console</summary>
	std::ofstream logFile;                                 ///<summary>File for logging errors</summary>
	std::ofstream outputFile;                              ///<summary>File for outputting correctly computed results</summary>
	std::unordered_map<ErrorType, std::string> errorTexts; 

	std::string generateErrorMessage(Error error);
public:
	void setStreams(std::ofstream logFile, std::ofstream outputFile);
	
	template <typename T>
	bool printResult(Result<T> result);
};