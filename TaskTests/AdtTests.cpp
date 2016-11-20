// Visual Studio Boilerplate
#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

#include <string>
using namespace std;

#include "ADT\Stack.h"
#include "ADT\Queue.h"

// Namespace of Assert::
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskTests // Testing Project namespace
{
	TEST_CLASS(AdtTests) // Groups the method tests together
	{
	public:

		// TODO: Write test case for Stack usage on Task Entries
		TEST_METHOD(Stack_TaskObjects)
		{
			Assert::Fail(L"Test case has not been written yet.");
		}

		// TODO: Write test case for Queue usage on Task Entries
		TEST_METHOD(Queue_TaskObjects)
		{
			Assert::Fail(L"Test case has not been written yet.");
		}

		TEST_METHOD(Stack_Int)
		{
			adt::Stack<int> stack_int;

			const int iterations = 5;

			Assert::AreEqual(0, stack_int.getLength());
			for (int i = 0; i < iterations; i++) {
				stack_int.push(i);
			}
			Assert::AreEqual(iterations, stack_int.getLength());

			for (int i = iterations - 1; i >= 0; i--) {
				Assert::AreEqual(i, stack_int.pop());
			}
			Assert::AreEqual(0, stack_int.getLength());

			try {
				stack_int.pop();
			}
			catch (const char* error) {
				string actual = (string)error;
				string expected = "pop() called on an empty stack.";
				Assert::AreEqual(expected, actual);
			}
			catch (...) {
				Assert::Fail(L"Could not catch the thrown error");
			}
		}

		TEST_METHOD(Stack_String)
		{
			adt::Stack<string> stack_string;
			const int iterations = 3;
			string payload = "12";

			Assert::AreEqual(0, stack_string.getLength());
			for (char i = 0; i < iterations; i++) {
				payload += payload;
				stack_string.push(payload);
			}
			Assert::AreEqual(iterations, stack_string.getLength());

			payload = "";
			for (int i = 0; i < iterations; i++) {
				payload += stack_string.pop();
			}

			string expected = "1212121212121212121212121212";
			Assert::AreEqual(expected, payload);
		}

		TEST_METHOD(Queue_Int)
		{
			adt::Queue<int> queue_int;

			const int iterations = 5;

			Assert::AreEqual(0, queue_int.getLength());
			for (int i = 0; i < iterations; i++) {
				queue_int.enqueue(i);
			}
			Assert::AreEqual(iterations, queue_int.getLength());

			for (int i = 0; i < iterations; i++) {
				Assert::AreEqual(i, queue_int.dequeue());
			}
			Assert::AreEqual(0, queue_int.getLength());

			try {
				queue_int.dequeue();
			}
			catch (const char* error) {
				string actual = (string)error;
				string expected = "pop() called on an empty stack.";
				Assert::AreEqual(expected, actual);
			}
			catch (...) {
				Assert::Fail(L"Could not catch the thrown error");
			}
		}
	};
}