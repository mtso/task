// WindowsDirectory.h
// TaskApp
// CIS 22C F2016: Matthew Tso, Adrian Marroquin

// Win32 Directory handling
// TRY: 
// REF: http://stackoverflow.com/questions/6006319/converting-tchar-to-string-in-c
// REF: http://stackoverflow.com/questions/6291458/how-to-convert-a-tchar-array-to-stdstring
// REF: http://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string

#ifndef TASKAPP_WINDOWSDIRECTORY_H
#define TASKAPP_WINDOWSDIRECTORY_H

#include <Windows.h>
#include <UserEnv.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <strsafe.h>
#include <vector>
#include <string>
#include "ADT\Stack.h"
using namespace std;
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "UserEnv.lib")

namespace taskapp {

	/**
	 * Stub of a function that that is supposed to return
	 * the filepaths of a given directory.
	 */
	vector<string> filenamesIn(const TCHAR* search_directory);

	/**
	 * Get the user's name from .gitconfig
	 */
	bool getCurrentUser(string& username);
}

#endif
