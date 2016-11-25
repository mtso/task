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
			string test_value = "hello world";
			int test_key = 3;

			task::HashList<int, string> list;
			Assert::IsTrue(list.isEmpty());

			list.addFirst(3, test_value);
			Assert::AreEqual(1, list.length());

			string value3 = list.getValue(3);
			Assert::AreEqual(test_value, value3);

			list.remove(test_key);
			Assert::IsTrue(list.isEmpty());

			list.addFirst(test_key, test_value);
			list.addFirst(test_key, test_value);
			list.addFirst(test_key, test_value);
			Assert::IsFalse(list.isEmpty());
			Assert::AreEqual(3, list.length());

			list.clear();
			Assert::IsTrue(list.isEmpty());
		}
	};
}