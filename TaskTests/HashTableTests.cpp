#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

#include <string>

#include "HashTable.h"
#include "TaskEntry.h"

// Namespace of Assert::
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskTests // Testing Project namespace
{

	TEST_CLASS(HashTableTests) // Groups the tests together
	{
	public:
		// TODO: Write test cases for Hash Table class
		
		TEST_METHOD(DefaultConstructor) {
			task::HashTable<string, task::TaskEntry> entry_table;
			Assert::IsTrue(entry_table.isEmpty());
		}
	};
}