#include "pch.h"
#include "CppUnitTest.h"
#include <Utils.h>
#include <vector>
#include <variant>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<>
			inline std::wstring ToString<Result<double>>(const Result<double>& t) {
				return L"Result<double>";
			}
		}
	}
}


namespace TrigCalculatorTests
{
	TEST_CLASS(TrigCalculatorTests)
	{
	public:

		void testEvaluation(std::vector<std::tuple<Utils::Functions, double, double, bool, std::variant<double, Result<double>>>> inputs)
		{
			for (int i = 0; i < inputs.size(); i++)
			{
				Utils::Functions function;
				double x;
				double precision;
				bool isSuccess;
				std::variant<double, Result<double>> expected;
				std::tie(function, x, precision, isSuccess, expected) = inputs[i];

				Result<double> output = Utils::evaluate(function, x, precision);

				Assert::AreEqual(output.isSuccess(), isSuccess);
				if (output.isSuccess())
					Assert::IsTrue(abs(output.getValue() - std::get<double>(expected)) < precision, L"Insufficient precision");
				else
					Assert::AreEqual(output, std::get<Result<double>>(expected), L"Wrong set of errors");
			}
		}

		TEST_METHOD(SinTests)
		{
			std::vector<std::tuple<Utils::Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{Utils::Sin,		-32.0,			0.001,			true,		-0.5514},
				{Utils::Sin,		-32.0,			0.0000000001,	true,		-0.55142668124},
				{Utils::Sin,		-3.1416,		0.001,			true,		 0.0000},
				{Utils::Sin,		-3.1416,		0.0000000001,	true,		 0.00000734641},
				{Utils::Sin,		-2.3562,		0.001,			true,		-0.7071},
				{Utils::Sin,		-2.3562,		0.0000000001,	true,		-0.70710288515},
				{Utils::Sin,		-1.5708,		0.001,			true,		-1.0000},
				{Utils::Sin,		-1.5708,		0.0000000001,	true,		-0.99999999999},
				{Utils::Sin,		-0.7854,		0.001,			true,		-0.7071},
				{Utils::Sin,		-0.7854,		0.0000000001,	true,		-0.70710807986},
				{Utils::Sin,		 0.0,			0.001,			true,		 0.0000},
				{Utils::Sin,		 0.0,			0.0000000001,	true,		 0.00000000000},
				{Utils::Sin,		 32.0,			0.001,			true,		 0.5514},
				{Utils::Sin,		 32.0,			0.0000000001,	true,		 0.55142668124},
				{Utils::Sin,		 3.1416,		0.001,			true,		-0.0000},
				{Utils::Sin,		 3.1416,		0.0000000001,	true,		-0.00000734641},
				{Utils::Sin,		 2.3562,		0.001,			true,		 0.7071},
				{Utils::Sin,		 2.3562,		0.0000000001,	true,		 0.70710288515},
				{Utils::Sin,		 1.5708,		0.001,			true,		 1.0000},
				{Utils::Sin,		 1.5708,		0.0000000001,	true,		 0.99999999999},
				{Utils::Sin,		 0.7854,		0.001,			true,		 0.7071},
				{Utils::Sin,		 0.7854,		0.0000000001,	true,		 0.70710807986}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(CosTests)
		{
			std::vector<std::tuple<Utils::Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{Utils::Cos,	-32,			0.001,			true,	 0.8342},
				{Utils::Cos,	-32,			0.0000000001,	true,	 0.83422336051},
				{Utils::Cos,	-3.1416,		0.001,			true,	-1.0000},
				{Utils::Cos,	-3.1416,		0.0000000001,	true,	-0.99999999997},
				{Utils::Cos,	-2.3562,		0.001,			true,	-0.7071},
				{Utils::Cos,	-2.3562,		0.0000000001,	true,	-0.70711067720},
				{Utils::Cos,	-1.5708,		0.001,			true,	-0.0000},
				{Utils::Cos,	-1.5708,		0.0000000001,	true,	-0.00000367321},
				{Utils::Cos,	-0.7854,		0.001,			true,	 0.7071},
				{Utils::Cos,	-0.7854,		0.0000000001,	true,	 0.70710548251},
				{Utils::Cos,	 0.0,			0.001,			true,	 1.0000},
				{Utils::Cos,	 0.0,			0.0000000001,	true,	 1.00000000000},
				{Utils::Cos,	 32.0,			0.001,			true,	 0.8342},
				{Utils::Cos,	 32.0,			0.0000000001,	true,	 0.83422336051},
				{Utils::Cos,	 3.1416,		0.001,			true,	-1.0000},
				{Utils::Cos,	 3.1416,		0.0000000001,	true,	-0.99999999997},
				{Utils::Cos,	 2.3562,		0.001,			true,	-0.7071},
				{Utils::Cos,	 2.3562,		0.0000000001,	true,	-0.70711067720},
				{Utils::Cos,	 1.5708,		0.001,			true,	-0.0000},
				{Utils::Cos,	 1.5708,		0.0000000001,	true,	-0.00000367321},
				{Utils::Cos,	 0.7854,		0.001,			true,	 0.7071},
				{Utils::Cos,	 0.7854,		0.0000000001,	true,	 0.70710548251}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(TanTests)
		{
			std::vector<std::tuple<Utils::Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{ Utils::Tan,	-32.0,		0.001,			true,	-0.6610 },
				{ Utils::Tan,	-32.0,		0.0000000001,	true,	-0.66100604148 },
				{ Utils::Tan,	-3.1416,	0.001,			true,	-0.0000 },
				{ Utils::Tan,	-3.1416,	0.0000000001,	true,	-0.00000734641 },
				{ Utils::Tan,	-2.3562,	0.001,			true,	 1.0000 },
				{ Utils::Tan,	-2.3562,	0.0000000001,	true,	 0.99998898045 },
				{ Utils::Tan,	-1.5708,	0.001,			true,	 INFINITY },
				{ Utils::Tan,	-1.5708,	0.0000000001,	true,	 INFINITY },
				{ Utils::Tan,	-0.7854,	0.001,			true,	-1.0000 },
				{ Utils::Tan,	-0.7854,	0.0000000001,	true,	-1.00000367321 },
				{ Utils::Tan,	 0.0,		0.001,			true,	 0.0000 },
				{ Utils::Tan,	 0.0,		0.0000000001,	true,	 0.00000000000 },
				{ Utils::Tan,	 32.0,		0.001,			true,	 0.6610 },
				{ Utils::Tan,	 32.0,		0.0000000001,	true,	 0.66100604148 },
				{ Utils::Tan,	 3.1416,	0.001,			true,	 0.0000 },
				{ Utils::Tan,	 3.1416,	0.0000000001,	true,	 0.00000734641 },
				{ Utils::Tan,	 2.3562,	0.001,			true,	-1.0000 },
				{ Utils::Tan,	 2.3562,	0.0000000001,	true,	-0.99998898045 },
				{ Utils::Tan,	 1.5708,	0.001,			true,	-INFINITY },
				{ Utils::Tan,	 1.5708,	0.0000000001,	true,	-INFINITY },
				{ Utils::Tan,	 0.7854,	0.001,			true,	 1.0000 },
				{ Utils::Tan,	 0.7854,	0.0000000001,	true,	 1.00000367321 }
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(CotTests)
		{
			Result<double> outOfRangeError = Result<double>();
			outOfRangeError.addError(Error(WrongArgValue, -1));

			std::vector<std::tuple<Utils::Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{Utils::Cot,	-32.0,		0.001,			true,	-1.5128},
				{Utils::Cot,	-32.0,		0.0000000001,	true,	-1.51284547681},
				{Utils::Cot,	-3.1416,	0.001,			true,	-INFINITY},
				{Utils::Cot,	-3.1416,	0.0000000001,	true,	-INFINITY},
				{Utils::Cot,	-2.3562,	0.001,			true,	 1.0000},
				{Utils::Cot,	-2.3562,	0.0000000001,	true,	 1.00001101968},
				{Utils::Cot,	-1.5708,	0.001,			true,	 0.0000},
				{Utils::Cot,	-1.5708,	0.0000000001,	true,	 0.00000367321},
				{Utils::Cot,	-0.7854,	0.001,			true,	-1.0000},
				{Utils::Cot,	-0.7854,	0.0000000001,	true,	-0.99999632680},
				{Utils::Cot,	 0.0,		0.001,			false,	 outOfRangeError},
				{Utils::Cot,	 32.0,		0.001,			true,	 1.5128},
				{Utils::Cot,	 32.0,		0.0000000001,	true,	 1.51284547681},
				{Utils::Cot,	 3.1416,	0.001,			true,	+INFINITY},
				{Utils::Cot,	 3.1416,	0.0000000001,	true,	+INFINITY},
				{Utils::Cot,	 2.3562,	0.001,			true,	-1.0000},
				{Utils::Cot,	 2.3562,	0.0000000001,	true,	-1.00001101968},
				{Utils::Cot,	 1.5708,	0.001,			true,	-0.0000},
				{Utils::Cot,	 1.5708,	0.0000000001,	true,	-0.00000367321},
				{Utils::Cot,	 0.7854,	0.001,			true,	 1.0000},
				{Utils::Cot,	 0.7854,	0.0000000001,	true,	 0.99999632680}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(SecTests)
		{
			std::vector<std::tuple<Utils::Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{Utils::Sec,	-32.0,		0.001,			true,	 1.1987},
				{Utils::Sec,	-32.0,		0.0000000001,	true,	 1.19871972824},
				{Utils::Sec,	-3.1416,	0.001,			true,	-1.0000},
				{Utils::Sec,	-3.1416,	0.0000000001,	true,	-1.00000000003},
				{Utils::Sec,	-2.3562,	0.001,			true,	-1.4142},
				{Utils::Sec,	-2.3562,	0.0000000001,	true,	-1.41420577039},
				{Utils::Sec,	-1.5708,	0.001,			true,	-INFINITY},
				{Utils::Sec,	-1.5708,	0.0000000001,	true,	-INFINITY},
				{Utils::Sec,	-0.7854,	0.001,			true,	 1.4142},
				{Utils::Sec,	-0.7854,	0.0000000001,	true,	 1.41421615973},
				{Utils::Sec,	 0.0,		0.001,			true,	 1.0000},
				{Utils::Sec,	 32.0,		0.001,			true,	 1.1987},
				{Utils::Sec,	 32.0,		0.0000000001,	true,	 1.19871972824},
				{Utils::Sec,	 3.1416,	0.001,			true,	-1.0000},
				{Utils::Sec,	 3.1416,	0.0000000001,	true,	-1.00000000003},
				{Utils::Sec,	 2.3562,	0.001,			true,	-1.4142},
				{Utils::Sec,	 2.3562,	0.0000000001,	true,	-1.41420577039},
				{Utils::Sec,	 1.5708,	0.001,			true,	-INFINITY},
				{Utils::Sec,	 1.5708,	0.0000000001,	true,	-INFINITY},
				{Utils::Sec,	 0.7854,	0.001,			true,	 1.4142},
				{Utils::Sec,	 0.7854,	0.0000000001,	true,	 1.41421615973}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(CscTests)
		{
			Result<double> outOfRangeError = Result<double>();
			outOfRangeError.addError(Error(WrongArgValue, -1));

			std::vector<std::tuple<Utils::Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{Utils::Csc,	-32.0,		0.001,			true,		-1.8135},
				{Utils::Csc,	-32.0,		0.0000000001,	true,		-1.81347771883},
				{Utils::Csc,	-3.1416,	0.001,			true,		+INFINITY},
				{Utils::Csc,	-3.1416,	0.0000000001,	true,		+INFINITY},
				{Utils::Csc,	-2.3562,	0.001,			true,		-1.4142},
				{Utils::Csc,	-2.3562,	0.0000000001,	true,		-1.41422135448},
				{Utils::Csc,	-1.5708,	0.001,			true,		-1.0000},
				{Utils::Csc,	-1.5708,	0.0000000001,	true,		-1.00000000001},
				{Utils::Csc,	-0.7854,	0.001,			true,		-1.4142},
				{Utils::Csc,	-0.7854,	0.0000000001,	true,		-1.41421096503},
				{Utils::Csc,	 0.0,		0.001,			false,		 outOfRangeError},
				{Utils::Csc,	 32.0,		0.001,			true,		 1.8135},
				{Utils::Csc,	 32.0,		0.0000000001,	true,		 1.81347771883},
				{Utils::Csc,	 3.1416,	0.001,			true,		-INFINITY},
				{Utils::Csc,	 3.1416,	0.0000000001,	true,		-INFINITY},
				{Utils::Csc,	 2.3562,	0.001,			true,		 1.4142},
				{Utils::Csc,	 2.3562,	0.0000000001,	true,		 1.41422135448},
				{Utils::Csc,	 1.5708,	0.001,			true,		 1.0000},
				{Utils::Csc,	 1.5708,	0.0000000001,	true,		 1.00000000001},
				{Utils::Csc,	 0.7854,	0.001,			true,		 1.4142},
				{Utils::Csc,	 0.7854,	0.0000000001,	true,		 1.41421096503}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(ArcsinTests)
		{
			std::vector<std::tuple<Utils::Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{Utils::Arcsin,		-1.0,		0.001,			true,	-1.5708},
				{Utils::Arcsin,		-1.0,		0.0000000001,	true,	-1.57079632679},
				{Utils::Arcsin,		-0.866,		0.001,			true,	-1.0471},
				{Utils::Arcsin,		-0.866,		0.0000000001,	true,	-1.04714674586},
				{Utils::Arcsin,		-0.7071,	0.001,			true,	-0.7854},
				{Utils::Arcsin,		-0.7071,	0.0000000001,	true,	-0.78538857340},
				{Utils::Arcsin,		-0.5,		0.001,			true,	-0.5236},
				{Utils::Arcsin,		-0.5,		0.0000000001,	true,	-0.52359877560},
				{Utils::Arcsin,		 0.0,		0.001,			true,	 0.0000},
				{Utils::Arcsin,		 0.0,		0.0000000001,	true,	 0.00000000000},
				{Utils::Arcsin,		 1.0,		0.001,			true,	 1.5708},
				{Utils::Arcsin,		 1.0,		0.0000000001,	true,	 1.57079632679},
				{Utils::Arcsin,		 0.866,		0.001,			true,	 1.0471},
				{Utils::Arcsin,		 0.866,		0.0000000001,	true,	 1.04714674586},
				{Utils::Arcsin,		 0.7071,	0.001,			true,	 0.7854},
				{Utils::Arcsin,		 0.7071,	0.0000000001,	true,	 0.78538857340},
				{Utils::Arcsin,		 0.5,		0.001,			true,	 0.5236},
				{Utils::Arcsin,		 0.5,		0.0000000001,	true,	 0.52359877560},
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(ArccosTests)
		{
			std::vector<std::tuple<Utils::Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{Utils::Arccos,		-1.0,		0.001,			true,	3.1416},
				{Utils::Arccos,		-1,			0.0000000001,	true,	3.14159265359},
				{Utils::Arccos,		-0.866,		0.001,			true,	2.6179},
				{Utils::Arccos,		-0.866,		0.0000000001,	true,	2.61794307266},
				{Utils::Arccos,		-0.7071,	0.001,			true,	2.3562},
				{Utils::Arccos,		-0.7071,	0.0000000001,	true,	2.35618490019},
				{Utils::Arccos,		-0.5,		0.001,			true,	2.0944},
				{Utils::Arccos,		-0.5,		0.0000000001,	true,	2.09439510239},
				{Utils::Arccos,		 0.0,		0.001,			true,	1.5708},
				{Utils::Arccos,		 0.0,		0.0000000001,	true,	1.57079632679},
				{Utils::Arccos,		 1.0,		0.001,			true,	0.0000},
				{Utils::Arccos,		 1.0,		0.0000000001,	true,	0.00000000000},
				{Utils::Arccos,		 0.866,		0.001,			true,	0.5236},
				{Utils::Arccos,		 0.866,		0.0000000001,	true,	0.52364958093},
				{Utils::Arccos,		 0.7071,	0.001,			true,	0.7854},
				{Utils::Arccos,		 0.7071,	0.0000000001,	true,	0.78540775340},
				{Utils::Arccos,		 0.5,		0.001,			true,	1.0472},
				{Utils::Arccos,		 0.5,		0.0000000001,	true,	1.04719755120}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(ArctanTests)
		{
			Result<double> cantComputeError = Result<double>();
			cantComputeError.addError(Error(CantAchievePrecision, -1));

			std::vector<std::tuple<Utils::Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{Utils::Arctan,		-1.7321,	0.001,			true,		-1.0472},
				{Utils::Arctan,		-1.7321,	0.0000000001,	true,		-1.04720984904},
				{Utils::Arctan,		-1.0,		0.001,			true,		-0.7854},
				{Utils::Arctan,		-1.0,		0.0000000001,	false,		 cantComputeError},
				{Utils::Arctan,		-0.5774,	0.001,			true,		-0.5236},
				{Utils::Arctan,		-0.5774,	0.0000000001,	true,		-0.52363607290},
				{Utils::Arctan,		 0.0,		0.001,			true,		 0.0000},
				{Utils::Arctan,		 0.0,		0.0000000001,	true,		 0.00000000000},
				{Utils::Arctan,		 1.7321,	0.001,			true,		 1.0472},
				{Utils::Arctan,		 1.7321,	0.0000000001,	true,		 1.04720984904},
				{Utils::Arctan,		 1.0,		0.001,			true,		 0.7854},
				{Utils::Arctan,		 1.0,		0.0000000001,	false,		 cantComputeError},
				{Utils::Arctan,		 0.5774,	0.001,			true,		 0.5236},
				{Utils::Arctan,		 0.5774,	0.0000000001,	true,		 0.52363607290},
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(ArccotTests)
		{
			Result<double> cantComputeError = Result<double>();
			cantComputeError.addError(Error(CantAchievePrecision, -1));

			std::vector<std::tuple<Utils::Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{Utils::Arccot,		-1.7321,	0.001,			true,		2.6180},
				{Utils::Arccot,		-1.7321,	0.0000000001,	true,		2.61800617584},
				{Utils::Arccot,		-1.0,		0.001,			true,		2.3562},
				{Utils::Arccot,		-1.0,		0.0000000001,	false,		cantComputeError},
				{Utils::Arccot,		-0.5774,	0.001,			true,		2.0944},
				{Utils::Arccot,		-0.5774,	0.0000000001,	true,		2.09443239970},
				{Utils::Arccot,		 0.0,		0.001,			true,		1.5708},
				{Utils::Arccot,		 0.0,		0.0000000001,	true,		1.57079632679},
				{Utils::Arccot,		 1.7321,	0.001,			true,		0.5236},
				{Utils::Arccot,		 1.7321,	0.0000000001,	true,		0.52358647775},
				{Utils::Arccot,		 1.0,		0.001,			true,		0.7854},
				{Utils::Arccot,		 1.0,		0.0000000001,	false,		cantComputeError},
				{Utils::Arccot,		 0.5774,	0.001,			true,		1.0472},
				{Utils::Arccot,		 0.5774,	0.0000000001,	true,		1.04716025389},
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(ArcsecTests)
		{
			Result<double> outOfRangeError = Result<double>();
			outOfRangeError.addError(Error(WrongArgValue, -1));

			std::vector<std::tuple<Utils::Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{Utils::Arcsec,		-1.0,		0.001,			true,		3.1416},
				{Utils::Arcsec,		-1.0,		0.0000000001,	true,		3.14159265359},
				{Utils::Arcsec,		-1.1547,	0.001,			true,		2.6180},
				{Utils::Arcsec,		-1.1547,	0.0000000001,	true,		2.61799468556},
				{Utils::Arcsec,		-1.4142,	0.001,			true,		2.3562},
				{Utils::Arcsec,		-1.4142,	0.0000000001,	true,		2.35620408038},
				{Utils::Arcsec,		-2.0,		0.001,			true,		2.0944},
				{Utils::Arcsec,		-2.0,		0.0000000001,	true,		2.09439510239},
				{Utils::Arcsec,		 0.0,		0.001,			false,		outOfRangeError},
				{Utils::Arcsec,		 0.0,		0.0000000001,	false,		outOfRangeError},
				{Utils::Arcsec,		 1.0,		0.001,			true,		0.0000},
				{Utils::Arcsec,		 1.0,		0.0000000001,	true,		0.00000000000},
				{Utils::Arcsec,		 1.1547,	0.001,			true,		0.5236},
				{Utils::Arcsec,		 1.1547,	0.0000000001,	true,		0.52359796803},
				{Utils::Arcsec,		 1.4142,	0.001,			true,		0.7854},
				{Utils::Arcsec,		 1.4142,	0.0000000001,	true,		0.78538857321},
				{Utils::Arcsec,		 2.0,		0.001,			true,		1.0472},
				{Utils::Arcsec,		 2.0,		0.0000000001,	true,		1.04719755120}
			};

			testEvaluation(inputs);
		}

		TEST_METHOD(ArccscTests)
		{
			Result<double> outOfRangeError = Result<double>();
			outOfRangeError.addError(Error(WrongArgValue, -1));

			std::vector<std::tuple<Utils::Functions, double, double, bool, std::variant<double, Result<double>>>> inputs =
			{
				{Utils::Arccsc,		-1.0,		0.001,			true,		-1.5708},
				{Utils::Arccsc,		-1.0,		0.0000000001,	true,		-1.57079632679},
				{Utils::Arccsc,		-1.1547,	0.001,			true,		-1.0472},
				{Utils::Arccsc,		-1.1547,	0.0000000001,	true,		-1.04719835877},
				{Utils::Arccsc,		-1.4142,	0.001,			true,		-0.7854},
				{Utils::Arccsc,		-1.4142,	0.0000000001,	true,		-0.78540775358},
				{Utils::Arccsc,		-2.0,		0.001,			true,		-0.5236},
				{Utils::Arccsc,		-2.0,		0.0000000001,	true,		-0.52359877560},
				{Utils::Arccsc,		 0.0,		0.001,			false,		outOfRangeError},
				{Utils::Arccsc,		 0.0,		0.0000000001,	false,		outOfRangeError},
				{Utils::Arccsc,		 1.0,		0.001,			true,		1.5708},
				{Utils::Arccsc,		 1.0,		0.0000000001,	true,		1.57079632679},
				{Utils::Arccsc,		 1.1547,	0.001,			true,		1.0472},
				{Utils::Arccsc,		 1.1547,	0.0000000001,	true,		1.04719835877},
				{Utils::Arccsc,		 1.4142,	0.001,			true,		0.7854},
				{Utils::Arccsc,		 1.4142,	0.0000000001,	true,		0.78540775358},
				{Utils::Arccsc,		 2.0,		0.001,			true,		0.5236},
				{Utils::Arccsc,		 2.0,		0.0000000001,	true,		0.52359877560},
			};

			testEvaluation(inputs);
		}
	};

	TEST_CLASS(ValidateInputFormatTests)
	{
		TEST_METHOD(validateInputFormatTests)
		{
			Result<std::tuple<Utils::Functions, double, double>> res1 = Result<std::tuple<Utils::Functions, double, double>>();
			res1.setValue(std::tuple(Utils::Cos, 0.7071, 0.001));


			Result<std::tuple<Utils::Functions, double, double>> res2 = Result<std::tuple<Utils::Functions, double, double>>();
			res2.addError(Error(WrongPrecisionFormat, -1));

			Result<std::tuple<Utils::Functions, double, double>> res3 = Result<std::tuple<Utils::Functions, double, double>>();
			res3.addError(Error(WrongArgFormat, -1));

			Result<std::tuple<Utils::Functions, double, double>> res4 = Result<std::tuple<Utils::Functions, double, double>>();
			res4.addError(Error(WrongArgFormat, -1));
			res4.addError(Error(WrongPrecisionFormat, -1));

			Result<std::tuple<Utils::Functions, double, double>> res5 = Result<std::tuple<Utils::Functions, double, double>>();
			res5.addError(Error(WrongFuncIdentifier, -1));

			Result<std::tuple<Utils::Functions, double, double>> res6 = Result<std::tuple<Utils::Functions, double, double>>();
			res6.addError(Error(WrongFuncIdentifier, -1));
			res6.addError(Error(WrongPrecisionFormat, -1));

			Result<std::tuple<Utils::Functions, double, double>> res7 = Result<std::tuple<Utils::Functions, double, double>>();
			res7.addError(Error(WrongFuncIdentifier, -1));
			res7.addError(Error(WrongArgFormat, -1));

			Result<std::tuple<Utils::Functions, double, double>> res8 = Result<std::tuple<Utils::Functions, double, double>>();
			res8.addError(Error(WrongFuncIdentifier, -1));
			res8.addError(Error(WrongArgFormat, -1));
			res8.addError(Error(WrongPrecisionFormat, -1));

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
}
