// WindowsDirectory.h
// TaskApp
// CIS 22C F2016: Matthew Tso
//
// From msdn docs: https://msdn.microsoft.com/en-us/library/windows/desktop/aa365200(v=vs.85).aspx
// Searches a given directory path and logs the filepaths of its contents.

#include "WindowsDirectory.h"

namespace taskapp {

	string filenamesIn(const TCHAR* search_directory)
	{
		// Get the length of the input parameter
		size_t length_of_arg;
		StringCchLength(search_directory, MAX_PATH, &length_of_arg);

		// Throw if parameter length + 3 (for the search pattern)
		// is greater than MAX_PATH (260)
		if (length_of_arg > MAX_PATH - 3) {
			throw "Directory path is too long.";
		}

		// Variables to contain data about each returned file handle
		WIN32_FIND_DATA find_data;
		LARGE_INTEGER file_size;

		// Used to store the input directory path + `\\*`
		// in order to search the entire folder.
		TCHAR search_pattern[MAX_PATH];
		
		// Contains the value returned from FindFirstFile()/FindeNextFile()
		HANDLE find_handle = INVALID_HANDLE_VALUE;

		// Used to catch ERROR_NO_MORE_FILES
		DWORD dwordError = 0;

		// Copy input parameter and append `\\*`
		StringCchCopy(search_pattern, MAX_PATH, search_directory);
		StringCchCat(search_pattern, MAX_PATH, TEXT("\\*"));
		
		// Find the first file handle that matches the search pattern
		find_handle = FindFirstFile(search_pattern, &find_data);

		if (find_handle == INVALID_HANDLE_VALUE) {
			throw "FindFirstFile returned an invalid handle value";
		}

		do {
			// Handle directories differently than files
			if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
			{
				_tprintf(TEXT("  %s   <DIR>\n"), find_data.cFileName);
			}
			else 
			{
				file_size.LowPart = find_data.nFileSizeLow;
				file_size.HighPart = find_data.nFileSizeHigh;
				_tprintf(TEXT("%s  %ld bytes\n"), find_data.cFileName, file_size.QuadPart);
			}
		} 
		while (FindNextFile(find_handle, &find_data) != 0);

		dwordError = GetLastError();
		if (dwordError != ERROR_NO_MORE_FILES)
		{
			// Something went wrong with FindNextFile
			throw "FindNextFile error";
		}

		FindClose(find_handle);
		return "done";
	}
}