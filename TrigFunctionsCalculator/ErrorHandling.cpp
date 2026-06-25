#include "ErrorHandling.h"

Error::Error(ErrorType type)
{
	errorType = type;
}

ErrorType Error::getErrorType() const
{
	return errorType;
}


Range Error::getRange() const
{
	return allowedRange;
}

std::string Error::getFilename() const
{
	return filename;
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