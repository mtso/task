// Visual Studio Boilerplate
#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

#include "Utilities/Diagnostic.h" 

// Namespace of Assert::
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskTests // Testing Project namespace
{
	TEST_CLASS(DiagnosticTests) // Groups the method tests together
	{
	public:

		const int test_run_count = 10000;

		TEST_METHOD(RunDiagnostic)
		{
			task::Diagnostic diagnostic;

			try {
				diagnostic.run(test_run_count);
			}
			catch (const char* error) {
				string error_str = error;
				wstring error_wstr = wstring(error_str.begin(), error_str.end());
				Assert::Fail(error_wstr.c_str());
			}
			catch (...) {
				Assert::Fail(L"Could not catch the thrown error");
			}
		}

		TEST_METHOD(RunDiagnosticWithOutput)
		{
			ostringstream output;
			task::Diagnostic diagnostic;

			try {
                // If this succeeds, test just falls-through try-catch block.
                // Cannot compare ostringstream to pre-defined string because
                // we don't really know how long this will take before-hand.
				diagnostic.runAndPrintTo(test_run_count, output);
			}
			catch (const char* error) {
				string error_str = error;
				wstring error_wstr = wstring(error_str.begin(), error_str.end());
				Assert::Fail(error_wstr.c_str());
			}
			catch (...) {
				Assert::Fail(L"Could not catch the thrown error");
			}
		}

	};
}
