#include "IOModule.h"
#include <sstream>

std::ostream& operator<<(std::ostream& os, const Range& range)
{
	for (auto iter = range.segments_.cbegin(); iter != range.segments_.cend(); iter++)
	{
		if (iter->minIncluded_) os << "[";
		else os << "(";

		os << iter->min_ << "; " << iter->max_;

		if (iter->maxIncluded_) os << "]";
		else os << ")";

		if (std::next(iter) != range.segments_.cend()) os << " & ";
	}
	
	return os;
}

ResultPrinter::ResultPrinter()
{
	isConsole = true;
}

std::string ResultPrinter::generateErrorMessage(Error error) const
{
	std::stringstream buffer;

	ErrorType errorType = error.getErrorType();

	buffer << errorTexts.at(errorType);

	if (errorType == inFileOpenFail ||
		errorType == outFileCreateFail ||
		errorType == logFileCreateFail)
		buffer << error.getFilename();

	if (errorType == WrongArgValue)
		buffer << error.getRange();

	return buffer.str();
}

void ResultPrinter::setStreams(std::ofstream outputFile, std::ofstream logFile)
{
	isConsole = false;
	logFile_ = std::move(logFile);
	outputFile_ = std::move(outputFile);
}
