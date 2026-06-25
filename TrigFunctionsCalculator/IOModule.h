#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include "ErrorHandling.h"

template<typename ...Ts>
std::ostream& operator<<(std::ostream& os, std::tuple<Ts...> const& t)
{
	os << "Tuple";
	return os;
}

/// <summary>
/// Responsible for outputting results in console or files 
/// </summary>
class ResultPrinter
{
private:
	bool isConsole;                                        ///<summary>Whether results are being outputted to console</summary>
	std::ofstream logFile_;                                 ///<summary>File for logging errors</summary>
	std::ofstream outputFile_;                              ///<summary>File for outputting correctly computed results</summary>
	std::unordered_map<ErrorType, std::string> errorTexts = 
	{
		{inFileOpenFail, "Невозможно открыть входной файл. Возможно, он не существует или у программы нет необходимых прав доступа. "},

		{outFileCreateFail, "Невозможно создать выходной файл. Возможно, у программы нет необходимых прав доступа. "},
		
		{outFileCreateFail, "Файл логов не может быть создан. Возможно, у программы нет необходимых прав доступа. "},
		
		{WrongArgumentCountConsole, "Неправильное количество аргументов. Возможные варианты вызова:\n"
		"trig.exe path/to/file_in path/to/file_out\n"
		"trig.exe func x eps"},

		{WrongArgumentCountFile, "Неправильное количество аргументов. Каждая строка файла должна иметь формат:\n"
		"func x eps"},

		{WrongFuncIdentifier, "Неизвестное обозначение функции. Доступные функции: sin, cos, tan, cot, sec, csc, arcsin, arccos, arctan, arccot, arcsec, arccsc"},

		{WrongArgFormat, "Неправильный формат значения аргумента.Значение аргумента должно быть числом в десятичной записи с числом знаков после запятой не более 15. Десятичный разделитель – точка."},

		{WrongArgValue, "Значение аргумента вне допустимого диапазона. Допустимый диапазон значений аргумента: "},

		{WrongPrecisionFormat, "Неправильный формат значения точности. Значение точности должно быть числом в десятичной записи с числом знаков после запятой не более 15. Десятичный разделитель – точка."},

		{WrongPrecisionValue, "Значение допустимой точности вне диапазона. Допустимый диапазон: [1e-10; 1.0]"},

		{CantAchievePrecision, "Программа не смогла добиться запрашиваемой точности"}
	};

	std::string generateErrorMessage(Error error) const;

public:
	ResultPrinter();
	void setStreams(std::ofstream outputFile, std::ofstream logFile);
	
	template <typename T>
	bool printResult(Result<T>& result) const;
};

template<typename T>
bool ResultPrinter::printResult(Result<T>& result) const
{
	std::locale::global(std::locale(""));
	std::cout.imbue(std::locale());

	if (result.isSuccess())
	{
		if (isConsole)
			std::cout << result.getValue() << std::endl;
		else
			outputFile_ << result.getValue() << std::endl;
	}
	else
	{
		outputFile_ << "-" << std::endl;

		for (auto iter = result.getErrors().cbegin(); iter != result.getErrors().cend(); iter++)
		{
			std::string errorText = generateErrorMessage(*iter);

			if (isConsole)
				std::cout << errorText << std::endl;
			else
				logFile_ << "[line: " << result.getLine() << "] " << errorText << std::endl;
		}
	}

	return result.isSuccess();
}