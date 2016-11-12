#include "stdafx.h"
#include "CppUnitTest.h"
// #include "[ObjectName].h" where [ObjectMain] is the name of the class file.

#include "Demo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskTests
{		
	TEST_CLASS(ExampleTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			// Assert::Fail(L"Test case has not been written yet.");
			task::Demo demo;
			Assert::AreEqual(4, demo.add(2, 2));
		}

	};
}