// Pager.h
// TaskApp
// CIS 22C F2016: Adrian Marroquin

#ifndef TASKAPP_WINDOWSDIRECTORY_H
#define TASKAPP_WINDOWSDIRECTORY_H

#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <strsafe.h>
#include <vector>
#include <string>
#include "ADT\Stack.h"
using namespace std;
#pragma comment(lib, "User32.lib")

// TRY: 
// REF: http://stackoverflow.com/questions/6006319/converting-tchar-to-string-in-c
// REF: http://stackoverflow.com/questions/6291458/how-to-convert-a-tchar-array-to-stdstring
// typedef std::basic_string<TCHAR> tstring;

namespace taskapp {

	/**
	 * Stub of a function that that is supposed to return
	 * the filepaths of a given directory.
	 */
	vector<string> filenamesIn(const TCHAR* search_directory);
}

#endif