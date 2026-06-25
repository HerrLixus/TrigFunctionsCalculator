#include "pch.h"
#include "CppUnitTest.h"
#include <Utils.h>
#include <vector>
#include <variant>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<>
			inline std::wstring ToString<Result<double>>(const Result<double>& t) {
				return L"Result<double>";
			}

			template<>
			inline std::wstring ToString<Result<std::tuple<Functions, double, double>>>(const Result<std::tuple<Functions, double, double>>& t) {
				return L"Result<std::tuple<Functions, double, double>>";
			}
		}
	}
}


namespace TrigCalculatorTests
{
	TEST_CLASS(TrigCalculatorTests)
	{
	public:

		void testEvaluation(std::vector<std::tuple<Functions, double, double, bool, std::variant<double, Result<double>>>> inputs)
		{
			for (int i = 0; i < inputs.size(); i++)
			{
				Functions function;
				double x;
				double precision;
				bool isSuccess;
				std::variant<double, Result<double>> expected;
				std::tie(function, x, precision, isSuccess, expected) = inputs[i];

				Result<double> output = Utils::evaluate(function, x, precision);
				
				Assert::AreEqual(output.isSuccess(), isSuccess);
				if (output.isSuccess())
				Assert::IsTrue(
						abs(output.getValue() - std::get<double>(expected)) < precision ||
						output.getValue() == std::get<double>(expected), L"Insufficient precision");
				else
					Assert::AreEqual(output, std::get<Result<double>>(expected), L"Wrong set of errors");
			}
		}

		TEST_METHOD(SinTests)
		{
			std::vector<std::tuple<Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{SIN,		-32.0,			0.001,			true,		-0.5514},
				{SIN,		-32.0,			0.0000000001,	true,		-0.55142668124},
				{SIN,		-3.1416,		0.001,			true,		 0.0000},
				{SIN,		-3.1416,		0.0000000001,	true,		 0.00000734641},
				{SIN,		-2.3562,		0.001,			true,		-0.7071},
				{SIN,		-2.3562,		0.0000000001,	true,		-0.70710288515},
				{SIN,		-1.5708,		0.001,			true,		-1.0000},
				{SIN,		-1.5708,		0.0000000001,	true,		-0.99999999999},
				{SIN,		-0.7854,		0.001,			true,		-0.7071},
				{SIN,		-0.7854,		0.0000000001,	true,		-0.70710807986},
				{SIN,		 0.0,			0.001,			true,		 0.0000},
				{SIN,		 0.0,			0.0000000001,	true,		 0.00000000000},
				{SIN,		 32.0,			0.001,			true,		 0.5514},
				{SIN,		 32.0,			0.0000000001,	true,		 0.55142668124},
				{SIN,		 3.1416,		0.001,			true,		-0.0000},
				{SIN,		 3.1416,		0.0000000001,	true,		-0.00000734641},
				{SIN,		 2.3562,		0.001,			true,		 0.7071},
				{SIN,		 2.3562,		0.0000000001,	true,		 0.70710288515},
				{SIN,		 1.5708,		0.001,			true,		 1.0000},
				{SIN,		 1.5708,		0.0000000001,	true,		 0.99999999999},
				{SIN,		 0.7854,		0.001,			true,		 0.7071},
				{SIN,		 0.7854,		0.0000000001,	true,		 0.70710807986}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(CosTests)
		{
			std::vector<std::tuple<Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{COS,	-32,			0.001,			true,	 0.8342},
				{COS,	-32,			0.0000000001,	true,	 0.83422336051},
				{COS,	-3.1416,		0.001,			true,	-1.0000},
				{COS,	-3.1416,		0.0000000001,	true,	-0.99999999997},
				{COS,	-2.3562,		0.001,			true,	-0.7071},
				{COS,	-2.3562,		0.0000000001,	true,	-0.70711067720},
				{COS,	-1.5708,		0.001,			true,	-0.0000},
				{COS,	-1.5708,		0.0000000001,	true,	-0.00000367321},
				{COS,	-0.7854,		0.001,			true,	 0.7071},
				{COS,	-0.7854,		0.0000000001,	true,	 0.70710548251},
				{COS,	 0.0,			0.001,			true,	 1.0000},
				{COS,	 0.0,			0.0000000001,	true,	 1.00000000000},
				{COS,	 32.0,			0.001,			true,	 0.8342},
				{COS,	 32.0,			0.0000000001,	true,	 0.83422336051},
				{COS,	 3.1416,		0.001,			true,	-1.0000},
				{COS,	 3.1416,		0.0000000001,	true,	-0.99999999997},
				{COS,	 2.3562,		0.001,			true,	-0.7071},
				{COS,	 2.3562,		0.0000000001,	true,	-0.70711067720},
				{COS,	 1.5708,		0.001,			true,	-0.0000},
				{COS,	 1.5708,		0.0000000001,	true,	-0.00000367321},
				{COS,	 0.7854,		0.001,			true,	 0.7071},
				{COS,	 0.7854,		0.0000000001,	true,	 0.70710548251}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(TanTests)
		{
			std::vector<std::tuple<Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{ TAN,	-32.0,		0.001,			true,	-0.6610 },
				{ TAN,	-32.0,		0.0000000001,	true,	-0.66100604148 },
				{ TAN,	-3.1416,	0.001,			true,	-0.0000 },
				{ TAN,	-3.1416,	0.0000000001,	true,	-0.00000734641 },
				{ TAN,	-2.3562,	0.001,			true,	 1.0000 },
				{ TAN,	-2.3562,	0.0000000001,	true,	 0.99998898045 },
				{ TAN,	-1.5708,	0.001,			true,	 INFINITY },
				{ TAN,	-1.5708,	0.0000000001,	true,	 INFINITY },
				{ TAN,	-0.7854,	0.001,			true,	-1.0000 },
				{ TAN,	-0.7854,	0.0000000001,	true,	-1.00000367321 },
				{ TAN,	 0.0,		0.001,			true,	 0.0000 },
				{ TAN,	 0.0,		0.0000000001,	true,	 0.00000000000 },
				{ TAN,	 32.0,		0.001,			true,	 0.6610 },
				{ TAN,	 32.0,		0.0000000001,	true,	 0.66100604148 },
				{ TAN,	 3.1416,	0.001,			true,	 0.0000 },
				{ TAN,	 3.1416,	0.0000000001,	true,	 0.00000734641 },
				{ TAN,	 2.3562,	0.001,			true,	-1.0000 },
				{ TAN,	 2.3562,	0.0000000001,	true,	-0.99998898045 },
				{ TAN,	 1.5708,	0.001,			true,	-INFINITY },
				{ TAN,	 1.5708,	0.0000000001,	true,	-INFINITY },
				{ TAN,	 0.7854,	0.001,			true,	 1.0000 },
				{ TAN,	 0.7854,	0.0000000001,	true,	 1.00000367321 }
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(CotTests)
		{
			Result<double> outOfRangeError = Result<double>();
			outOfRangeError.addError(Error(WrongArgValue));

			std::vector<std::tuple<Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{COT,	-32.0,		0.001,			true,	-1.5128},
				{COT,	-32.0,		0.0000000001,	true,	-1.51284547681},
				{COT,	-3.1416,	0.001,			true,	-INFINITY},
				{COT,	-3.1416,	0.0000000001,	true,	-INFINITY},
				{COT,	-2.3562,	0.001,			true,	 1.0000},
				{COT,	-2.3562,	0.0000000001,	true,	 1.00001101968},
				{COT,	-1.5708,	0.001,			true,	 0.0000},
				{COT,	-1.5708,	0.0000000001,	true,	 0.00000367321},
				{COT,	-0.7854,	0.001,			true,	-1.0000},
				{COT,	-0.7854,	0.0000000001,	true,	-0.99999632680},
				{COT,	 0.0,		0.001,			false,	 outOfRangeError},
				{COT,	 32.0,		0.001,			true,	 1.5128},
				{COT,	 32.0,		0.0000000001,	true,	 1.51284547681},
				{COT,	 3.1416,	0.001,			true,	+INFINITY},
				{COT,	 3.1416,	0.0000000001,	true,	+INFINITY},
				{COT,	 2.3562,	0.001,			true,	-1.0000},
				{COT,	 2.3562,	0.0000000001,	true,	-1.00001101968},
				{COT,	 1.5708,	0.001,			true,	-0.0000},
				{COT,	 1.5708,	0.0000000001,	true,	-0.00000367321},
				{COT,	 0.7854,	0.001,			true,	 1.0000},
				{COT,	 0.7854,	0.0000000001,	true,	 0.99999632680}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(SecTests)
		{
			std::vector<std::tuple<Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{SEC,	-32.0,		0.001,			true,	 1.1987},
				{SEC,	-32.0,		0.0000000001,	true,	 1.19871972824},
				{SEC,	-3.1416,	0.001,			true,	-1.0000},
				{SEC,	-3.1416,	0.0000000001,	true,	-1.00000000003},
				{SEC,	-2.3562,	0.001,			true,	-1.4142},
				{SEC,	-2.3562,	0.0000000001,	true,	-1.41420577039},
				{SEC,	-1.5708,	0.001,			true,	-INFINITY},
				{SEC,	-1.5708,	0.0000000001,	true,	-INFINITY},
				{SEC,	-0.7854,	0.001,			true,	 1.4142},
				{SEC,	-0.7854,	0.0000000001,	true,	 1.41421615973},
				{SEC,	 0.0,		0.001,			true,	 1.0000},
				{SEC,	 32.0,		0.001,			true,	 1.1987},
				{SEC,	 32.0,		0.0000000001,	true,	 1.19871972824},
				{SEC,	 3.1416,	0.001,			true,	-1.0000},
				{SEC,	 3.1416,	0.0000000001,	true,	-1.00000000003},
				{SEC,	 2.3562,	0.001,			true,	-1.4142},
				{SEC,	 2.3562,	0.0000000001,	true,	-1.41420577039},
				{SEC,	 1.5708,	0.001,			true,	-INFINITY},
				{SEC,	 1.5708,	0.0000000001,	true,	-INFINITY},
				{SEC,	 0.7854,	0.001,			true,	 1.4142},
				{SEC,	 0.7854,	0.0000000001,	true,	 1.41421615973}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(CscTests)
		{
			Result<double> outOfRangeError = Result<double>();
			outOfRangeError.addError(Error(WrongArgValue));

			std::vector<std::tuple<Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{CSC,	-32.0,		0.001,			true,		-1.8135},
				{CSC,	-32.0,		0.0000000001,	true,		-1.81347771883},
				{CSC,	-3.1416,	0.001,			true,		+INFINITY},
				{CSC,	-3.1416,	0.0000000001,	true,		+INFINITY},
				{CSC,	-2.3562,	0.001,			true,		-1.4142},
				{CSC,	-2.3562,	0.0000000001,	true,		-1.41422135448},
				{CSC,	-1.5708,	0.001,			true,		-1.0000},
				{CSC,	-1.5708,	0.0000000001,	true,		-1.00000000001},
				{CSC,	-0.7854,	0.001,			true,		-1.4142},
				{CSC,	-0.7854,	0.0000000001,	true,		-1.41421096503},
				{CSC,	 0.0,		0.001,			false,		 outOfRangeError},
				{CSC,	 32.0,		0.001,			true,		 1.8135},
				{CSC,	 32.0,		0.0000000001,	true,		 1.81347771883},
				{CSC,	 3.1416,	0.001,			true,		-INFINITY},
				{CSC,	 3.1416,	0.0000000001,	true,		-INFINITY},
				{CSC,	 2.3562,	0.001,			true,		 1.4142},
				{CSC,	 2.3562,	0.0000000001,	true,		 1.41422135448},
				{CSC,	 1.5708,	0.001,			true,		 1.0000},
				{CSC,	 1.5708,	0.0000000001,	true,		 1.00000000001},
				{CSC,	 0.7854,	0.001,			true,		 1.4142},
				{CSC,	 0.7854,	0.0000000001,	true,		 1.41421096503}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(ArcsinTests)
		{
			std::vector<std::tuple<Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{ARCSIN,		-1.0,		0.001,			true,	-1.5708},
				{ARCSIN,		-1.0,		0.0000000001,	true,	-1.57079632679},
				{ARCSIN,		-0.866,		0.001,			true,	-1.0471},
				{ARCSIN,		-0.866,		0.0000000001,	true,	-1.04714674586},
				{ARCSIN,		-0.7071,	0.001,			true,	-0.7854},
				{ARCSIN,		-0.7071,	0.0000000001,	true,	-0.78538857340},
				{ARCSIN,		-0.5,		0.001,			true,	-0.5236},
				{ARCSIN,		-0.5,		0.0000000001,	true,	-0.52359877560},
				{ARCSIN,		 0.0,		0.001,			true,	 0.0000},
				{ARCSIN,		 0.0,		0.0000000001,	true,	 0.00000000000},
				{ARCSIN,		 1.0,		0.001,			true,	 1.5708},
				{ARCSIN,		 1.0,		0.0000000001,	true,	 1.57079632679},
				{ARCSIN,		 0.866,		0.001,			true,	 1.0471},
				{ARCSIN,		 0.866,		0.0000000001,	true,	 1.04714674586},
				{ARCSIN,		 0.7071,	0.001,			true,	 0.7854},
				{ARCSIN,		 0.7071,	0.0000000001,	true,	 0.78538857340},
				{ARCSIN,		 0.5,		0.001,			true,	 0.5236},
				{ARCSIN,		 0.5,		0.0000000001,	true,	 0.52359877560},
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(ArccosTests)
		{
			std::vector<std::tuple<Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{ARCCOS,		-1.0,		0.001,			true,	3.1416},
				{ARCCOS,		-1,			0.0000000001,	true,	3.14159265359},
				{ARCCOS,		-0.866,		0.001,			true,	2.6179},
				{ARCCOS,		-0.866,		0.0000000001,	true,	2.61794307266},
				{ARCCOS,		-0.7071,	0.001,			true,	2.3562},
				{ARCCOS,		-0.7071,	0.0000000001,	true,	2.35618490019},
				{ARCCOS,		-0.5,		0.001,			true,	2.0944},
				{ARCCOS,		-0.5,		0.0000000001,	true,	2.09439510239},
				{ARCCOS,		 0.0,		0.001,			true,	1.5708},
				{ARCCOS,		 0.0,		0.0000000001,	true,	1.57079632679},
				{ARCCOS,		 1.0,		0.001,			true,	0.0000},
				{ARCCOS,		 1.0,		0.0000000001,	true,	0.00000000000},
				{ARCCOS,		 0.866,		0.001,			true,	0.5236},
				{ARCCOS,		 0.866,		0.0000000001,	true,	0.52364958093},
				{ARCCOS,		 0.7071,	0.001,			true,	0.7854},
				{ARCCOS,		 0.7071,	0.0000000001,	true,	0.78540775340},
				{ARCCOS,		 0.5,		0.001,			true,	1.0472},
				{ARCCOS,		 0.5,		0.0000000001,	true,	1.04719755120}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(ArctanTests)
		{
			Result<double> cantComputeError = Result<double>();
			cantComputeError.addError(Error(CantAchievePrecision));

			std::vector<std::tuple<Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{ARCTAN,		-1.7321,	0.001,			true,		-1.0472},
				{ARCTAN,		-1.7321,	0.0000000001,	true,		-1.04720984904},
				{ARCTAN,		-1.0,		0.001,			true,		-0.7854},
				{ARCTAN,		-1.0,		0.0000000001,	false,		 cantComputeError},
				{ARCTAN,		-0.5774,	0.001,			true,		-0.5236},
				{ARCTAN,		-0.5774,	0.0000000001,	true,		-0.52363607290},
				{ARCTAN,		 0.0,		0.001,			true,		 0.0000},
				{ARCTAN,		 0.0,		0.0000000001,	true,		 0.00000000000},
				{ARCTAN,		 1.7321,	0.001,			true,		 1.0472},
				{ARCTAN,		 1.7321,	0.0000000001,	true,		 1.04720984904},
				{ARCTAN,		 1.0,		0.001,			true,		 0.7854},
				{ARCTAN,		 1.0,		0.0000000001,	false,		 cantComputeError},
				{ARCTAN,		 0.5774,	0.001,			true,		 0.5236},
				{ARCTAN,		 0.5774,	0.0000000001,	true,		 0.52363607290},
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(ArccotTests)
		{
			Result<double> cantComputeError = Result<double>();
			cantComputeError.addError(Error(CantAchievePrecision));

			std::vector<std::tuple<Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{ARCCOT,		-1.7321,	0.001,			true,		2.6180},
				{ARCCOT,		-1.7321,	0.0000000001,	true,		2.61800617584},
				{ARCCOT,		-1.0,		0.001,			true,		2.3562},
				{ARCCOT,		-1.0,		0.0000000001,	false,		cantComputeError},
				{ARCCOT,		-0.5774,	0.001,			true,		2.0944},
				{ARCCOT,		-0.5774,	0.0000000001,	true,		2.09443239970},
				{ARCCOT,		 0.0,		0.001,			true,		1.5708},
				{ARCCOT,		 0.0,		0.0000000001,	true,		1.57079632679},
				{ARCCOT,		 1.7321,	0.001,			true,		0.5236},
				{ARCCOT,		 1.7321,	0.0000000001,	true,		0.52358647775},
				{ARCCOT,		 1.0,		0.001,			true,		0.7854},
				{ARCCOT,		 1.0,		0.0000000001,	false,		cantComputeError},
				{ARCCOT,		 0.5774,	0.001,			true,		1.0472},
				{ARCCOT,		 0.5774,	0.0000000001,	true,		1.04716025389},
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(ArcsecTests)
		{
			Result<double> outOfRangeError = Result<double>();
			outOfRangeError.addError(Error(WrongArgValue));

			std::vector<std::tuple<Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{ARCSEC,		-1.0,		0.001,			true,		3.1416},
				{ARCSEC,		-1.0,		0.0000000001,	true,		3.14159265359},
				{ARCSEC,		-1.1547,	0.001,			true,		2.6180},
				{ARCSEC,		-1.1547,	0.0000000001,	true,		2.61799468556},
				{ARCSEC,		-1.4142,	0.001,			true,		2.3562},
				{ARCSEC,		-1.4142,	0.0000000001,	true,		2.35620408038},
				{ARCSEC,		-2.0,		0.001,			true,		2.0944},
				{ARCSEC,		-2.0,		0.0000000001,	true,		2.09439510239},
				{ARCSEC,		 0.0,		0.001,			false,		outOfRangeError},
				{ARCSEC,		 0.0,		0.0000000001,	false,		outOfRangeError},
				{ARCSEC,		 1.0,		0.001,			true,		0.0000},
				{ARCSEC,		 1.0,		0.0000000001,	true,		0.00000000000},
				{ARCSEC,		 1.1547,	0.001,			true,		0.5236},
				{ARCSEC,		 1.1547,	0.0000000001,	true,		0.52359796803},
				{ARCSEC,		 1.4142,	0.001,			true,		0.7854},
				{ARCSEC,		 1.4142,	0.0000000001,	true,		0.78538857321},
				{ARCSEC,		 2.0,		0.001,			true,		1.0472},
				{ARCSEC,		 2.0,		0.0000000001,	true,		1.04719755120}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(ArccscTests)
		{
			Result<double> outOfRangeError = Result<double>();
			outOfRangeError.addError(Error(WrongArgValue));

			std::vector<std::tuple<Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{ARCCSC,		-1.0,		0.001,			true,		-1.5708},
				{ARCCSC,		-1.0,		0.0000000001,	true,		-1.57079632679},
				{ARCCSC,		-1.1547,	0.001,			true,		-1.0472},
				{ARCCSC,		-1.1547,	0.0000000001,	true,		-1.04719835877},
				{ARCCSC,		-1.4142,	0.001,			true,		-0.7854},
				{ARCCSC,		-1.4142,	0.0000000001,	true,		-0.78540775358},
				{ARCCSC,		-2.0,		0.001,			true,		-0.5236},
				{ARCCSC,		-2.0,		0.0000000001,	true,		-0.52359877560},
				{ARCCSC,		 0.0,		0.001,			false,		outOfRangeError},
				{ARCCSC,		 0.0,		0.0000000001,	false,		outOfRangeError},
				{ARCCSC,		 1.0,		0.001,			true,		1.5708},
				{ARCCSC,		 1.0,		0.0000000001,	true,		1.57079632679},
				{ARCCSC,		 1.1547,	0.001,			true,		1.0472},
				{ARCCSC,		 1.1547,	0.0000000001,	true,		1.04719835877},
				{ARCCSC,		 1.4142,	0.001,			true,		0.7854},
				{ARCCSC,		 1.4142,	0.0000000001,	true,		0.78540775358},
				{ARCCSC,		 2.0,		0.001,			true,		0.5236},
				{ARCCSC,		 2.0,		0.0000000001,	true,		0.52359877560},
			};

			testEvaluation(inputs);
		}
	};

	TEST_CLASS(ValidateInputFormatTests)
	{
		TEST_METHOD(validateInputFormatTests)
		{
			Result<std::tuple<Functions, double, double>> res1 = Result<std::tuple<Functions, double, double>>();
			res1.setValue(std::tuple(COS, 0.7071, 0.001));


			Result<std::tuple<Functions, double, double>> res2 = Result<std::tuple<Functions, double, double>>();
			res2.addError(Error(WrongPrecisionFormat));

			Result<std::tuple<Functions, double, double>> res3 = Result<std::tuple<Functions, double, double>>();
			res3.addError(Error(WrongArgFormat));

			Result<std::tuple<Functions, double, double>> res4 = Result<std::tuple<Functions, double, double>>();
			res4.addError(Error(WrongArgFormat));
			res4.addError(Error(WrongPrecisionFormat));

			Result<std::tuple<Functions, double, double>> res5 = Result<std::tuple<Functions, double, double>>();
			res5.addError(Error(WrongFuncIdentifier));

			Result<std::tuple<Functions, double, double>> res6 = Result<std::tuple<Functions, double, double>>();
			res6.addError(Error(WrongFuncIdentifier));
			res6.addError(Error(WrongPrecisionFormat));

			Result<std::tuple<Functions, double, double>> res7 = Result<std::tuple<Functions, double, double>>();
			res7.addError(Error(WrongFuncIdentifier));
			res7.addError(Error(WrongArgFormat));

			Result<std::tuple<Functions, double, double>> res8 = Result<std::tuple<Functions, double, double>>();
			res8.addError(Error(WrongFuncIdentifier));
			res8.addError(Error(WrongArgFormat));
			res8.addError(Error(WrongPrecisionFormat));

			Assert::AreEqual(res1, Utils::validateInputFormat("cos", "0.7071", "0.001"), L"Correct function, Correct argument, Correct precision failed");
			Assert::AreEqual(res2, Utils::validateInputFormat("cos", "0.7071", "1e-3"), L"Correct function, Correct argument, Wrong precision failed");
			Assert::AreEqual(res3, Utils::validateInputFormat("cos", "1e-2", "0.001"), L"Correct function, Wrong argument, Correct precision failed");
			Assert::AreEqual(res4, Utils::validateInputFormat("cos", "1e-2", "1e-3"), L"Correct function, Wrong argument, Wrong precision failed");
			Assert::AreEqual(res5, Utils::validateInputFormat("exp", "0.7071", "0.001"), L"Wrong function, Correct argument, Correct precision failed");
			Assert::AreEqual(res6, Utils::validateInputFormat("exp", "0.7071", "1e-3"), L"Wrong function, Correct argument, Wrong precision failed");
			Assert::AreEqual(res7, Utils::validateInputFormat("exp", "1e-2", "0.001"), L"Wrong function, Wrong argument, Correct precision failed");
			Assert::AreEqual(res8, Utils::validateInputFormat("exp", "1e-2", "1e-3"), L"Wrong function, Wrong argument, Wrong precision failed");

		}
	};

	TEST_CLASS(ValidateDoubleTests)
	{
		TEST_METHOD(validateDoubleTests)
		{
			std::vector<std::tuple<std::string, bool, const wchar_t*>> inputs = 
			{
				{"",					false, L"Пустая строка"},
				{"12345",				true,  L"Одни цифры"},
				{".14",					true,  L"Точка в начале"},
				{"14.",					true,  L"Точка в конце"},
				{"1.4",					true,  L"Точка в середине"},
				{"1.4.3",				false, L"Две точки"},
				{"abcdef",				false, L"Только буквы"},
				{"123abc",				false, L"Буквы и цифры"},
				{"1.5E5",				false, L"Экспоненциальная запись"},
				{"1.12345678910111213", false, L"Слишком длинная запись"},
				{"1,4",					false, L"Десятичная запятая"},

			};

			for (int i = 0; i < inputs.size(); i++)
			{
				const wchar_t* message;
				std::string input;
				bool expected;
				std::tie(input, expected, message) = inputs[i];

				Assert::AreEqual(expected, Utils::validateDouble(input), message);
			}
		}

	};
}
