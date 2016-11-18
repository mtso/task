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

		TEST_METHOD(RunDiagnostic)
		{
			task::Diagnostic diagnostic;

			try {
				diagnostic.run();
			}
			catch (const char* error) {
				Assert::AreEqual("Diagnostic::run() has not been implemented yet", error);
			}
			catch (...) {
				Assert::Fail(L"Could not catch the thrown error");
			}
		}

//		TEST_METHOD(RunDiagnosticWithOutput)
//		{
//			ostringstream output;
//			task::Diagnostic diagnostic;
//
//			try {
//				diagnostic.runAndPrintTo(output);
//				string actual = output.str();
//				string expected = "Diagnostic::run(ostream&) has not been implemented yet";
//				Assert::AreEqual(expected, actual);
//			}
//			catch (const char* error) {
//				string error_str = error;
//				wstring error_wstr = wstring(error_str.begin(), error_str.end());
//				Assert::Fail(error_wstr.c_str());
//			}
//			catch (...) {
//				Assert::Fail(L"Could not catch the thrown error");
//			}
//		}

	};
}
