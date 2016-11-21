#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

#include <string>
using namespace std;

#include "HashEntry.h"
#include "TaskEntry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskTests // Testing Project namespace
{
	TEST_CLASS(HashEntryTests) // Groups the method tests together
	{
	public:

		TEST_METHOD(PointerToNext)
		{
			int key = 10;
			task::HashEntry<int, string> entry = task::HashEntry<int, string>(key, "what in the worlds");
			
			int actual = entry.getKey();
			Assert::AreEqual(key, actual);
		}

		TEST_METHOD(EntryKeysAreEqual)
		{
			using namespace task;
			TaskEntry task_entry = TaskEntry("mryagni", "Add console colors utility functions.");
			HashEntry<string, TaskEntry> hash_entry = HashEntry<string, TaskEntry>(task_entry.getId(), task_entry);

			Assert::AreEqual(task_entry.getId(), hash_entry.getKey());
		}
	};
}