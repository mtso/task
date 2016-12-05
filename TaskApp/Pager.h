// Pager.h
// TaskApp
// CIS 22C F2016: Mr. Yagni

#ifndef TASKAPP_PAGER_H
#define TASKAPP_PAGER_H

#include <iostream>
#include <sstream>
#include <string>
#include <conio.h>

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

namespace app_util {

	/**
	 * Creates a paginated line-by-line viewer
	 * for text strings that span many lines.
	 *
	 * @param content Array of strings to print line-by-line
	 * @param line_count Number of items in the content array
	 * @param scroll_length Number of lines to print per page
	 */
	void page(const string* content, const int& line_count, const int& scroll_length);

#ifdef _WIN32
	void page(istream& buffer, ostream& output);
#endif
}

#endif