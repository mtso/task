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
			task::TaskEntry* demo_entry = new task::TaskEntry("mryagni", "demo entry for diagnostic");
			task::HashTable<string, task::TaskEntry> table;
			c_tree<uint64_t, task::TaskEntry> tree;
			table.insert(demo_entry->getId(), *demo_entry);
			tree.insert(demo_entry->getTimeCreatedMs(), demo_entry);

			diagnostic.setTable(&table);
			diagnostic.setTree(&tree);

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

			delete demo_entry;
		}

		TEST_METHOD(RunDiagnosticWithOutput)
		{
			ostringstream output;
			task::Diagnostic diagnostic;
			task::TaskEntry* demo_entry = new task::TaskEntry("mryagni", "demo entry for diagnostic");
			task::HashTable<string, task::TaskEntry> table;
			c_tree<uint64_t, task::TaskEntry> tree;
			table.insert(demo_entry->getId(), *demo_entry);
			tree.insert(demo_entry->getTimeCreatedMs(), demo_entry);

			diagnostic.setTable(&table);
			diagnostic.setTree(&tree);

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
