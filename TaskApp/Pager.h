// Pager.h
// TaskApp
// CIS 22C F2016: Matthew Tso

#ifndef TASKAPP_PAGER_H
#define TASKAPP_PAGER_H

#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

namespace app_util {

	void page(const string* content, const int& line_count, const int& scroll_length);
}

#endif