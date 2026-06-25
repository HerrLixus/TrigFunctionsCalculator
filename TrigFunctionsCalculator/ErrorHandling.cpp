#include "ErrorHandling.h"

Error::Error(ErrorType type, int occurenceLine)
{
	errorType = type;
	line = occurenceLine;
}

ErrorType Error::getErrorType() const
{
	return errorType;
}

void Error::setAllowedRange(Range range)
{
	allowedRange = range;
}

void Error::setFilename(std::string name)
{
	filename = name;
}

bool Error::operator==(const Error& right) const
{
	return errorType == right.errorType;
}