// WindowsDirectory.h
// TaskApp
// CIS 22C F2016: Matthew Tso, Adrian Marroquin
//
// From msdn docs: https://msdn.microsoft.com/en-us/library/windows/desktop/aa365200(v=vs.85).aspx
// Searches a given directory path and logs the filepaths of its contents.

#include "WindowsDirectory.h"
#include "ADT\Stack.h"

namespace taskapp {


	vector<string> filenamesIn(const TCHAR* search_directory)
	{
		vector<string> filenames;

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
		//LARGE_INTEGER file_size;

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
			// Ignore directories
			if (! (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				wstring raw_string = find_data.cFileName;
				string filename(raw_string.begin(), raw_string.end());
				
				filenames.push_back(filename);
			}
		} while (FindNextFile(find_handle, &find_data) != 0);

		dwordError = GetLastError();
		if (dwordError != ERROR_NO_MORE_FILES)
		{
			// Something went wrong with FindNextFile
			throw "FindNextFile error";
		}

		FindClose(find_handle);
		return filenames;
	}

	bool getCurrentUser(string& username)
	{
		// Windows directory variables
		WCHAR user_root_wchar[MAX_PATH];
		DWORD length = MAX_PATH;
		HANDLE handle = INVALID_HANDLE_VALUE;
		string user_root;

		// Get the user's root directory
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_READ, &handle)) { return false; }
		if (!GetUserProfileDirectory(handle, user_root_wchar, &length)) { return false; }
		wstring user_root_w = (wstring)user_root_wchar;
		user_root = string(user_root_w.begin(), user_root_w.end());
		
		// file reading variables
		ifstream git_config;
		string line;
		size_t position;
		bool isUserSection = false;

		// Open and read .gitconfig file
		git_config.open(user_root + "\\.gitconfig");
		while (getline(git_config, line)) 
		{
			// if it isn't the [user] section,
			// check if it's a heading that matches [user]
			// else continue
			if (!isUserSection) 
			{
				position = line.find("[user]");
				if (position == 0) {
					isUserSection = true;
				}
				continue;
			}
			else 
			{
				// If we are in the [user] section,
				// and come across a '[', it is the end of the [user] section
				// else 
				position = line.find('[');
				if (position == 0) {
					isUserSection = false;
					continue;
				}

				// If we come across the name field,
				// grab the username that comes after "\tname = "
				position = line.find("\tname");
				if (position == 0) {
					username = line.substr(8, line.length() - 8);
					git_config.close();
					return true;
				}
			}
		}
		git_config.close();

		return false;
	}
}
