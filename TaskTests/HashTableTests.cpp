#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

#include <string>

#include "HashTable.h"
#include "TaskEntry.h"
#include "HashList.h"

// Namespace of Assert::
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskTests // Testing Project namespace
{

	TEST_CLASS(HashTableTests) // Groups the tests together
	{
	public:
		// TODO: Write test cases for Hash Table class
		
		TEST_METHOD(DefaultConstructor) {
			task::HashTable<string, task::TaskEntry> table;
			Assert::IsTrue(table.isEmpty());
		}

		TEST_METHOD(HashList) {
			task::HashList<int, string> list;
			Assert::IsTrue(list.isEmpty());
		}
	};
}