// Visual Studio Boilerplate
#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

// Include the header file of your class to be able to access its public functions
// #include "[ObjectName].h" where [ObjectMain] is the name of the header file of your class.
#include "Example.h" 

// Namespace of Assert::
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskTests // Testing Project namespace
{
	TEST_CLASS(ExampleTests) // Groups the method tests together
	{
	public:
		
		TEST_METHOD(ExampleMethodTest)
		{
			// Construct an instance of Example object.
			task::Example example;
			
			int expected = 3;
			int actual = example.add(2, 2);

			// returns true if expected and actual are equivalent
			Assert::AreEqual(expected, actual);
		}

		// Once test methods are set up,
		// run the tests through the menubar:
		// Test > Run > All Tests
		//
		// This opens the test explorer
		// Checkmark means that all Assert:: 
		// testing statements have passed

	};
}