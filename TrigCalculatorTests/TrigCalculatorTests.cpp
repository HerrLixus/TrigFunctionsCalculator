#include "pch.h"
#include "CppUnitTest.h"
#include <TrigFunctionsCalculator.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TrigCalculatorTests
{
	TEST_CLASS(TrigCalculatorTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, testMethod(1));
		}
	};
}
