// Visual Studio Boilerplate
#include "stdafx.h"      // Pre-compiled header (optimizes unit testing header file)
#include "CppUnitTest.h" // Unit testing API

#include <string>

#include "Utilities\Sha1.h"
#include "Utilities\Djb2.h"

// Namespace of Assert::
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskTests // Testing Project namespace
{
	TEST_CLASS(HashTests) // Groups the tests together
	{
	public:

		TEST_METHOD(Sha1_ATest)
		{
			std::string input = "A Test";
			std::string expected = "8f0c0855915633e4a7de19468b3874c8901df043";
			std::string actual = task::sha_1(input);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Sha1_QuickFox)
		{
			std::string input = "The quick brown fox jumped over a lazy dog.";
			std::string expected = "e26d11465308c2c78f0914c69f2001cb3c454c9f";
			std::string actual = task::sha_1(input);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Sha1_LongParagraph)
		{
			std::string input = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque dignissim tellus non lacus aliquet pulvinar. Donec at orci turpis. Etiam consequat, sapien ut ornare tristique, erat mauris consectetur turpis, nec ullamcorper lacus nibh eu nulla. Aliquam nunc nisl, condimentum sit amet faucibus eu, maximus eu sem. In eu risus elit. Duis vitae lacinia neque. Cras ut volutpat quam. Fusce posuere augue nec arcu sagittis rutrum. Aliquam ac convallis est. Interdum et malesuada fames ac ante ipsum primis in faucibus. Phasellus volutpat, lorem eget tincidunt tincidunt, sapien dolor elementum mauris, ut tincidunt leo est a sapien. Aenean metus arcu, dignissim a viverra ut, fringilla at felis. Suspendisse ut rhoncus ipsum, eget blandit velit.";
			std::string expected = "2a78301bc7fba267541a198282b9876231771d9b";
			std::string actual = task::sha_1(input);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Sha1_Blank)
		{
			std::string input = "";
			std::string expected = "da39a3ee5e6b4b0d3255bfef95601890afd80709";
			std::string actual = task::sha_1(input);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Sha1_MockTestEntry)
		{
			std::string input = "3688099389	3688358589	\"Decide on hash function to use.\"	assignee=mtso";
			std::string expected = "38c467b1b5d4b78944d07928efcfb233ee8b6d62";
			std::string actual = task::sha_1(input);
			Assert::AreEqual(expected, actual);
		}

		// Test that the produced hash is the same each time for an unchanged input.
		TEST_METHOD(Sha1_Equality)
		{
			string input = "Test input";

			string hash_current;
			string hash_previous = task::sha_1(input);

			for (int run_count = 0; run_count < 100; run_count++) {
				hash_current = task::sha_1(input);
				Assert::AreEqual(hash_previous, hash_current);
				hash_previous = hash_current;
			}
		}

		// Test that the produced hash is the same each time for an unchanged input.
		TEST_METHOD(Djb2_Equality)
		{
			unsigned char* input = (unsigned char*)"Test input";

			unsigned long hash_current;
			unsigned long hash_previous = task::djb_2(input);

			for (int run_count = 0; run_count < 100; run_count++) {
				hash_current = task::djb_2(input);
				Assert::AreEqual(hash_previous, hash_current);
				hash_previous = hash_current;
			}
		}
	};
}
