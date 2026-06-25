#pragma once
#include <string>
#include <unordered_set>
#include <fstream>
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
	ErrorType errorType;            ///<summary>Line where error occurs</summary>
	Range allowedRange;    ///<summary>Allowed range. Used for range-related errors</summary>
	std::string filename;  ///<summary>Filename. Used for errors with opening files</summary>

public:
	Error(ErrorType type);

	ErrorType getErrorType() const;
	Range getRange() const;
	std::string getFilename() const;

	void setAllowedRange(Range range);
	void setFilename(std::string name);

	bool operator==(const Error& right) const;
};

namespace std {
	template <>
	struct hash<Error> {
		std::size_t operator()(const Error& e) const noexcept {
			 return std::hash<int>{}(static_cast<int>(e.getErrorType()));
		}
	};
}

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
	int line;

public:
	Result();
	bool isSuccess() const;

	void setValue(T val);
	T& getValue();

	const std::unordered_set<Error>& getErrors() const;
	void addError(Error error);         ///<summary>Add error to list of errors</summary>
	void expandErrors(const Result& res);

	int getLine() const;
	void setLine(int line);

	bool operator==(const Result& right) const;
};

template<typename T>
Result<T>::Result()
{
	success = true;
	errors = std::unordered_set<Error>();
}

template<typename T>
bool Result<T>::isSuccess() const
{
	return success;
}

template<typename T>
T& Result<T>::getValue()
{
	return value;
}

template<typename T>
void Result<T>::setValue(T val)
{
	value = std::move(val);
}

template<typename T>
const std::unordered_set<Error>& Result<T>::getErrors() const
{
	return errors;
}

template<typename T>
void Result<T>::addError(Error error)
{
	success = false;
	errors.insert(error);
}

template<typename T>
void Result<T>::expandErrors(const Result& res)
{
	success = false;
	errors.insert(res.errors.cbegin(), res.errors.cend());
}

template<typename T>
int Result<T>::getLine() const
{
	return line;
}

template<typename T>
void Result<T>::setLine(int line_)
{
	line = line_;
}

template<typename T>
bool Result<T>::operator==(const Result& right) const
{
	if (success != right.success)
		return false;

	if (success)
		return value == right.value;
	else
		return errors == right.errors;
}