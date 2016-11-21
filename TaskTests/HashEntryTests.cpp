#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

#include <string>
using namespace std;

#include "HashEntry.h"

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
	};
}