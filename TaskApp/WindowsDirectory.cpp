
#include "WindowsDirectory.h"

namespace taskapp {

	string filenamesIn(const TCHAR* search_directory)
	{
		WIN32_FIND_DATA find_data;
		LARGE_INTEGER file_size;

		TCHAR search_pattern[MAX_PATH];
		size_t length_of_arg;
		HANDLE find_handle = INVALID_HANDLE_VALUE;
		DWORD dwordError = 0;

		StringCchLength(search_directory, MAX_PATH, &length_of_arg);

		if (length_of_arg > MAX_PATH - 3) {
			throw "Directory path is too long.";
		}

		StringCchCopy(search_pattern, MAX_PATH, search_directory);
		StringCchCat(search_pattern, MAX_PATH, TEXT("\\*"));
		
		find_handle = FindFirstFile(search_pattern, &find_data);

		cout << search_pattern << endl;

		if (find_handle == INVALID_HANDLE_VALUE) {
			throw "FindFirstFile returned an invalid handle value";
		}

		do {
			if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
			{
				_tprintf(TEXT(" %s  <DIR>\n"), find_data.cFileName);
			}
			else {
				file_size.LowPart = find_data.nFileSizeLow;
				file_size.HighPart = find_data.nFileSizeHigh;
				_tprintf(TEXT("%s  %ld bytes\n"), find_data.cFileName, file_size.QuadPart);
			}
		} while (FindNextFile(find_handle, &find_data) != 0);

		dwordError = GetLastError();
		if (dwordError != ERROR_NO_MORE_FILES)
		{
			throw "FindNextFile error";
		}

		FindClose(find_handle);
		return "done";
	}
}