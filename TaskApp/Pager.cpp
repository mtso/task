// Pager.cpp
// TaskApp
// CIS 22C F2016: Mr. Yagni

#include "Pager.h"

#define KEY_ENTER  13
#define KEY_SPACE  32
#define KEY_Q     113

namespace app_util 
{
	void page(const string* content, const int& line_count, const int& scroll_length)
	{
		int page = 0;
		int input = 0;
		int scroll = scroll_length;
		int iter = 0;

		do {
			for (iter = 0; iter < scroll && page + iter < line_count; iter++) {
				cout << content[iter + page];
				cout << endl;
			}

			if (page + iter >= line_count) {
				break;
			}
			page += scroll;

			cout << "== " << page << " of " << line_count << " ==  <space/enter>";
			input = _getch();

			// This does a carriage return back to the line's beginning
			// needs to be longer than the previous line (13+ char) that says: == 4 of 15 ==
			cout << "\r                                            \r";

			switch (input) {
			case KEY_ENTER:
				scroll = 1;
				break;

			case KEY_SPACE:
				scroll = scroll_length;
				break;

			default:
				scroll = 0;
				break;
			}

		} while (toupper(input) != 'Q');
	}

#ifdef _WIN32

	// Windows API-specific console height
	// REF: http://stackoverflow.com/a/12642749/2684355
	// Get the number of rows in the console window.
	short getRowsInWindow()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		return info.srWindow.Bottom - info.srWindow.Top + 1;
	}

	void page(istream& buffer, ostream& output)
	{
		int page_height = (int)getRowsInWindow() - 1; // console height less one for input line.
		int current_count = 0, lines_to_output = page_height;
		bool shouldContinue = true, needs_input = false;
		string line;

		// Main output loop
		while (getline(buffer, line) && shouldContinue) 
		{
			output << line << endl;
			current_count++;
			if (current_count < lines_to_output) { continue; }

			// Wait for input
			output << ":";
			needs_input = true;
			while (needs_input) 
			{	
				switch (_getch())
				{
				case KEY_ENTER:
					lines_to_output = 1;
					current_count = 0;
					needs_input = false;
					break;
				case KEY_SPACE:
					lines_to_output = page_height;
					current_count = 0;
					needs_input = false;
					break;
				case KEY_Q:
					shouldContinue = false;
					needs_input = false;
					break;
				default:
					break;
				}
			}
			output << "\r       \r"; // rollback the input-prompt line
		}

		while (getline(buffer, line)) { /* Clear remaining lines in buffer */ }
	}

#endif
}
