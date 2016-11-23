/**
* @brief Unit test class for c_tree.
* @file c_tree_test.cpp
* @author CIS22C XINHE
*/

#include <iostream>
#include <sstream>
#include <vector>
#include "c_tree.h"
#include "c_tree_impl.h"
#include "c_tree_test.h"
#include <string>
using namespace std;
#define TEST_CASE(cond) \
	if (!(cond)) { \
		cout<<"ERROR: "<<__FILE__<<","<<__LINE__<<": " \
			<<#cond<<" is false"<<endl; \
	}

void c_tree_test::test(void)
{
	test_misc();
	test_insert();
	test_remove();
}

void c_tree_test::test_misc(void)
{
	c_tree<int, int> tree;
	TEST_CASE(tree.is_empty() && !tree.is_not_empty());

	tree.insert(1);
	TEST_CASE(!tree.is_empty() && *tree.first_data() == 1);

	tree.insert(3);
	tree.insert(2);

	bool checked = true;
	int* data = tree.first_data();
	if (*data != 1) {
		checked = false;
	}
	data = tree.next_data();
	if (*data != 2) {
		checked = false;
	}
	data = tree.next_data();
	if (*data != 3) {
		checked = false;
	}
	TEST_CASE(!tree.is_empty() && checked);

	tree.clear();
	int i;
	for (i = 0; i < 7; ++i) {
		tree.insert(i);
	}

	checked = true;
	data = tree.first_data();
	if (*data != 0) {
		checked = false;
	}
	for (i = 1; i < 7; ++i) {
		data = tree.next_data();
		if (*data != i) {
			checked = false;
		}
	}
	TEST_CASE(checked);

	tree.clear();
	for (i = 6; i >= 0; --i) {
		tree.insert(i);
	}

	checked = true;
	data = tree.first_data();
	if (*data != 0) {
		checked = false;
	}
	for (i = 1; i < 7; ++i) {
		data = tree.next_data();
		if (*data != i) {
			checked = false;
		}
	}
	TEST_CASE( checked);

	tree.clear();
	for (i = 0; i < 1024; ++i) {
		tree.insert(i);
	}

	checked = true;
	data = tree.first_data();
	if (*data != 0) {
		checked = false;
	}
	for (i = 1; i < 1024; ++i) {
		data = tree.next_data();
		if (*data != i) {
			checked = false;
		}
	}
	TEST_CASE( checked);

	tree.clear();
	for (i = 1023; i >= 0; --i) {
		tree.insert(i);
	}
	checked = true;
	data = tree.first_data();
	if (*data != 0) {
		checked = false;
	}
	for (i = 1; i < 1024; ++i) {
		data = tree.next_data();
		if (*data != i) {
			checked = false;
		}
	}
	TEST_CASE(checked);

	tree.clear();
	for (i = 0; i < 1024; ++i) {
		tree.insert(i);
	}
	tree.remove(500);
	checked = true;
	data = tree.first_data();
	if (*data != 0) {
		checked = false;
	}
	for (i = 1; i < 1024; ++i) {
		if (i != 500) {
			data = tree.next_data();
			if (*data != i) {
				checked = false;
			}
		}
	}
	TEST_CASE(checked);

	tree.clear();
	TEST_CASE( tree.is_empty());

	tree.clear();
	for (i = 0; i < 1024; ++i) {
		tree.insert(i);
	}
	int* found_ret;
	bool found = tree.find(568, &found_ret);
	int* not_found_ret;
	bool not_found = tree.find(1047, &not_found_ret);
	TEST_CASE( found && *found_ret == 568 && !not_found &&
		not_found_ret == NULL);

	tree.clear();
	TEST_CASE( tree.is_empty() && !tree.is_not_empty());

	tree.insert(1);
	TEST_CASE( !tree.is_empty() && tree.is_not_empty());

	tree.clear();
	for (i = 0; i < 1024; ++i) {
		tree.insert(i);
	}
	checked = true;
	data = tree.first_data();
	if (*data != 0) {
		checked = false;
	}
	for (i = 1; i < 1024; ++i) {
		data = tree.next_data();
		if (*data != i) {
			checked = false;
		}
	}
	data = tree.next_data();
	if (data != NULL) {
		checked = false;
	}
	TEST_CASE( checked);

	tree.clear();
	for (i = 0; i < 1024; ++i) {
		tree.insert(i);
	}
	checked = true;
	data = tree.last_data();
	if (*data != 1023) {
		checked = false;
	}
	for (i = 1022; i >= 0; --i) {
		data = tree.prev_data();
		if (*data != i) {
			checked = false;
		}
	}
	data = tree.prev_data();
	if (data != NULL) {
		checked = false;
	}
	TEST_CASE(checked);

	tree.clear();
	TEST_CASE( tree.size() == 0);

	tree.insert(1);
	TEST_CASE( tree.size() == 1);

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	TEST_CASE( tree.size() == 3);

	tree.remove(0);
	TEST_CASE( tree.size() == 3);

	tree.remove(1);
	TEST_CASE( tree.size() == 2);
}

#define TEST_INSERT(expect, ...) \
	{ \
		int val = 0; \
		tree.clear(); \
		int items[] = {__VA_ARGS__}; \
		for (size_t i = 0; i < sizeof(items)/sizeof(items[0]); ++i) { \
			tree.insert(items[i], &val); \
						} \
		s = tree.to_string(); \
		TEST_CASE(s == expect); \
	}

void c_tree_test::test_insert(void)
{
	c_tree<int, int> tree;

	// Basic test.
	string s = tree.to_string();
	TEST_CASE( s == "");

	int* ret;
	int val = 3;
	tree.insert(1, &val, &ret);
	TEST_CASE(*ret == 1);

	TEST_CASE( tree.to_string() ==
		"(1,3)\r\n"
		"+---(null,null)\r\n"
		"L---(null,null)");

	TEST_INSERT(
		"(1,0)\r\n"
		"+---(null,null)\r\n"
		"L---(null,null)",
		1);

	TEST_INSERT(
		"(1,0)\r\n"
		"+---(null,null)\r\n"
		"L---(2,0)\r\n"
		"    +---(null,null)\r\n"
		"    L---(null,null)",
		1, 2);

	TEST_INSERT(
		"(1,0)\r\n"
		"+---(null,null)\r\n"
		"L---(2,0)\r\n"
		"    +---(null,null)\r\n"
		"    L---(3,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(null,null)",
		1, 2, 3);

	TEST_INSERT(
		"(1,0)\r\n"
		"+---(null,null)\r\n"
		"L---(2,0)\r\n"
		"    +---(null,null)\r\n"
		"    L---(3,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(4,0)\r\n"
		"            +---(null,null)\r\n"
		"            L---(null,null)",
		1, 2, 3, 4);

	TEST_INSERT(
		"(1,0)\r\n"
		"+---(null,null)\r\n"
		"L---(2,0)\r\n"
		"    +---(null,null)\r\n"
		"    L---(3,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(4,0)\r\n"
		"            +---(null,null)\r\n"
		"            L---(5,0)\r\n"
		"                +---(null,null)\r\n"
		"                L---(null,null)",
		1, 2, 3, 4, 5);

	TEST_INSERT(
		"(1,0)\r\n"
		"+---(null,null)\r\n"
		"L---(2,0)\r\n"
		"    +---(null,null)\r\n"
		"    L---(3,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(4,0)\r\n"
		"            +---(null,null)\r\n"
		"            L---(5,0)\r\n"
		"                +---(null,null)\r\n"
		"                L---(6,0)\r\n"
		"                    +---(null,null)\r\n"
		"                    L---(null,null)",
		1, 2, 3, 4, 5, 6);

	TEST_INSERT(
		"(1,0)\r\n"
		"+---(null,null)\r\n"
		"L---(2,0)\r\n"
		"    +---(null,null)\r\n"
		"    L---(3,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(4,0)\r\n"
		"            +---(null,null)\r\n"
		"            L---(5,0)\r\n"
		"                +---(null,null)\r\n"
		"                L---(6,0)\r\n"
		"                    +---(null,null)\r\n"
		"                    L---(7,0)\r\n"
		"                        +---(null,null)\r\n"
		"                        L---(null,null)",
		1, 2, 3, 4, 5, 6, 7);

	TEST_INSERT(
		"(1,0)\r\n"
		"+---(null,null)\r\n"
		"L---(2,0)\r\n"
		"    +---(null,null)\r\n"
		"    L---(3,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(null,null)",
		1, 2, 3, 1, 2, 3);
}

#define TEST_REMOVE(expect, rmv, ...) \
	{ \
		int _val = 0; \
		tree.clear(); \
		int items[] = {__VA_ARGS__}; \
		for (size_t i = 0; i < sizeof(items)/sizeof(items[0]); ++i) { \
			tree.insert(items[i], &_val); \
		} \
		tree.remove(rmv); \
		TEST_CASE(tree.to_string() == expect); \
	}

void c_tree_test::test_remove(void)
{

	c_tree<int, int> tree;

	// Basic test.
	string s = tree.to_string();
	TEST_CASE( s == "");

	// Remove a node that's node in the tree.
	tree.remove(0);
	s = tree.to_string();
	TEST_CASE( s == "");

	// Remove the last node.
	int val = 0;
	tree.clear();
	tree.insert(0, &val);
	tree.remove(0);
	TEST_CASE(s == "");

	tree.clear();
	tree.insert(4, &val);
	tree.insert(2, &val);
	tree.insert(6, &val);
	tree.insert(1, &val);
	tree.insert(3, &val);
	tree.insert(5, &val);
	tree.insert(7, &val);

	// Prepare
	TEST_CASE( tree.to_string() ==
		"(4,0)\r\n"
		"+---(2,0)\r\n"
		"|   +---(1,0)\r\n"
		"|   |   +---(null,null)\r\n"
		"|   |   L---(null,null)\r\n"
		"|   L---(3,0)\r\n"
		"|       +---(null,null)\r\n"
		"|       L---(null,null)\r\n"
		"L---(6,0)\r\n"
		"    +---(5,0)\r\n"
		"    |   +---(null,null)\r\n"
		"    |   L---(null,null)\r\n"
		"    L---(7,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(null,null)");

	// Basic test.
	TEST_REMOVE(
		"(4,0)\r\n"
		"+---(2,0)\r\n"
		"|   +---(1,0)\r\n"
		"|   |   +---(null,null)\r\n"
		"|   |   L---(null,null)\r\n"
		"|   L---(3,0)\r\n"
		"|       +---(null,null)\r\n"
		"|       L---(null,null)\r\n"
		"L---(6,0)\r\n"
		"    +---(5,0)\r\n"
		"    |   +---(null,null)\r\n"
		"    |   L---(null,null)\r\n"
		"    L---(7,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(null,null)",
		0,
		4,2,6,1,3,5,7);

	TEST_REMOVE(
		"",
		1,
		1);

	TEST_REMOVE(
		"(4,0)\r\n"
		"+---(2,0)\r\n"
		"|   +---(null,null)\r\n"
		"|   L---(3,0)\r\n"
		"|       +---(null,null)\r\n"
		"|       L---(null,null)\r\n"
		"L---(6,0)\r\n"
		"    +---(5,0)\r\n"
		"    |   +---(null,null)\r\n"
		"    |   L---(null,null)\r\n"
		"    L---(7,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(null,null)",
		1,
		4, 2, 6, 1, 3, 5, 7);

	TEST_REMOVE(
		"(4,0)\r\n"
		"+---(1,0)\r\n"
		"|   +---(null,null)\r\n"
		"|   L---(3,0)\r\n"
		"|       +---(null,null)\r\n"
		"|       L---(null,null)\r\n"
		"L---(6,0)\r\n"
		"    +---(5,0)\r\n"
		"    |   +---(null,null)\r\n"
		"    |   L---(null,null)\r\n"
		"    L---(7,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(null,null)",
		2,
		4, 2, 6, 1, 3, 5, 7);

	TEST_REMOVE(
		"(4,0)\r\n"
		"+---(2,0)\r\n"
		"|   +---(1,0)\r\n"
		"|   |   +---(null,null)\r\n"
		"|   |   L---(null,null)\r\n"
		"|   L---(null,null)\r\n"
		"L---(6,0)\r\n"
		"    +---(5,0)\r\n"
		"    |   +---(null,null)\r\n"
		"    |   L---(null,null)\r\n"
		"    L---(7,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(null,null)",
		3,
		4, 2, 6, 1, 3, 5, 7);

	TEST_REMOVE(
		"(3,0)\r\n"
		"+---(2,0)\r\n"
		"|   +---(1,0)\r\n"
		"|   |   +---(null,null)\r\n"
		"|   |   L---(null,null)\r\n"
		"|   L---(null,null)\r\n"
		"L---(6,0)\r\n"
		"    +---(5,0)\r\n"
		"    |   +---(null,null)\r\n"
		"    |   L---(null,null)\r\n"
		"    L---(7,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(null,null)",
		4,
		4, 2, 6, 1, 3, 5, 7);

	TEST_REMOVE(
		"(4,0)\r\n"
		"+---(2,0)\r\n"
		"|   +---(1,0)\r\n"
		"|   |   +---(null,null)\r\n"
		"|   |   L---(null,null)\r\n"
		"|   L---(3,0)\r\n"
		"|       +---(null,null)\r\n"
		"|       L---(null,null)\r\n"
		"L---(6,0)\r\n"
		"    +---(null,null)\r\n"
		"    L---(7,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(null,null)",
		5,
		4, 2, 6, 1, 3, 5, 7);

	TEST_REMOVE(
		"(4,0)\r\n"
		"+---(2,0)\r\n"
		"|   +---(1,0)\r\n"
		"|   |   +---(null,null)\r\n"
		"|   |   L---(null,null)\r\n"
		"|   L---(3,0)\r\n"
		"|       +---(null,null)\r\n"
		"|       L---(null,null)\r\n"
		"L---(5,0)\r\n"
		"    +---(null,null)\r\n"
		"    L---(7,0)\r\n"
		"        +---(null,null)\r\n"
		"        L---(null,null)",
		6,
		4, 2, 6, 1, 3, 5, 7);

	TEST_REMOVE(
		"(4,0)\r\n"
		"+---(2,0)\r\n"
		"|   +---(1,0)\r\n"
		"|   |   +---(null,null)\r\n"
		"|   |   L---(null,null)\r\n"
		"|   L---(3,0)\r\n"
		"|       +---(null,null)\r\n"
		"|       L---(null,null)\r\n"
		"L---(6,0)\r\n"
		"    +---(5,0)\r\n"
		"    |   +---(null,null)\r\n"
		"    |   L---(null,null)\r\n"
		"    L---(null,null)",
		7,
		4, 2, 6, 1, 3, 5, 7);
}
