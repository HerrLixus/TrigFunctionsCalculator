#pragma once
#include <string>
#include <unordered_set>
#include "Ranges.h"

/// <summary>
/// Error types
/// </summary>
enum ErrorType { noError, inFileOpenFail, outFileCreateFail, logFileCreateFail, WrongArgumentCountConsole, WrongArgumentCountFile, WrongFuncIdentifier, WrongArgFormat, WrongArgValue, WrongPrecisionFormat, WrongPrecisionValue, CantAchievePrecision };

/// <summary>
/// Contains information abour error
/// </summary>
class Error
{
private:
	ErrorType errorType;
	int line;              ///<summary>Line where error occurs</summary>
	Range allowedRange;    ///<summary>Allowed range. Used for range-related errors</summary>
	std::string filename;  ///<summary>Filename. Used for errors with opening files</summary>
public:
	Error(ErrorType type, int Occuerenceline);
	void setAllowedRange(Range range);
	void setFilename(std::string name);
};

/// <summary>
/// Describes result of operation
/// </summary>
/// <typeparam name="T">Type of returned value</typeparam>
template<typename T>
class Result
{
private:
	bool success;                       ///<summary>Whether the operation is successful</summary>
	T value;                            ///<summary>Result of operation if it was successful</summary>
	std::unordered_set<Error> errors;   ///<summary>List of errors if it was unsuccessful</summary>

public:
	void addError(Error error);         ///<summary>Add error to list of errors</summary>
	void setValue(T val);
};