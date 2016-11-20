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

			cout << "== " << page << " of " << line_count << " ==";
			input = _getch();
			// This needs to be longer than the previous line (13+ char) that says: == 4 of 15 ==
			cout << "\r                                         \r";

			scroll = (input == KEY_ENTER) ? 1 : scroll_length;

		} while (toupper(input) != 'Q');
	}
}
