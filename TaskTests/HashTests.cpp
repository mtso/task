// Visual Studio Boilerplate
#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

#include "Utilities/Sha1.h"

// Namespace of Assert::
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskTests // Testing Project namespace
{
	TEST_CLASS(HashTests) // Groups the method tests together
	{
	public:
		
		TEST_METHOD(Sha1_ATest)
		{
			string input = "A Test";
      string expected = "8f0c0855915633e4a7de19468b3874c8901df043";
      string actual = task::sha_1(input);
			Assert::AreEqual(expected, actual);
		}

    TEST_METHOD(Sha1_QuickFox)
		{
			string input = "The quick brown fox jumped over a lazy dog.";
      string expected = "e26d11465308c2c78f0914c69f2001cb3c454c9f";
      string actual = task::sha_1(input);
			Assert::AreEqual(expected, actual);
		}
	};
}
