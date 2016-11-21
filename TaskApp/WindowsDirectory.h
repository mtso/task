
#ifndef TASKAPP_WINDOWSDIRECTORY_H
#define TASKAPP_WINDOWSDIRECTORY_H

#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <strsafe.h>
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
	string filenamesIn(const TCHAR* search_directory);
}

#endif