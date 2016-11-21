// DemoDataGenerator.h
// TaskApp
// CIS 22C F2016:

#include "TaskEntry.h"

namespace taskapp {

	/**
	 * TODO: 
	 * If no .task folder exists, this will be called to 
	 * create a new demo .task folder with fake tasklogs.
	 */
	void generateDemoDirectory(
		const string& demo_user, 
		const uint64_t& demo_start_time, 
		const uint64_t& demo_end_time, 
		const int& entry_count);
}