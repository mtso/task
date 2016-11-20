#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

#include <string>
using namespace std;

#include "TaskEntry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskTests // Testing Project namespace
{
	TEST_CLASS(TaskEntryTests) // Groups the method tests together
	{
	public:

		TEST_METHOD(CheckConstructorHash)
		{
			using namespace std::chrono; 
			string input_description = "Get the hash table done.";
			string input_user = "mryagni";

			steady_clock::duration current_time = steady_clock::now().time_since_epoch();
			const milliseconds unchanged_time = duration_cast<milliseconds>(current_time);

			task::TaskEntry entry_1 = task::TaskEntry(input_user, input_description, unchanged_time.count());

			// Force >1 ms of time to pass
			ostringstream buffer;
			for (unsigned long i = 0; i < 500; i++) {
				buffer << i + i;
				task::sha_1(buffer.str());
				buffer.clear();
			}

			task::TaskEntry entry_2 = task::TaskEntry(input_user, input_description, unchanged_time.count());

			Assert::AreEqual(entry_1.getId(), entry_2.getId());
		}
	};
}