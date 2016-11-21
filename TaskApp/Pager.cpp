// Pager.cpp
// TaskApp
// CIS 22C F2016: Matthew Tso

#include "Pager.h"

#define KEY_ENTER 13
#define KEY_SPACE 32

namespace app_util {

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
}
