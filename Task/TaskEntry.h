// TaskEntry.h
// Task
// CIS 22C F2016:

#include <stdint.h>
#include <sstream>
//#include <string>
#include <chrono>
using namespace std;

#include "TaskEntryStatus.h"
#include "Utilities\Sha1.h"

namespace task
{

	class TaskEntry
	{
	private:
		// 40 hex character id
		string unique_id;
		uint64_t time_created;
		uint64_t time_due;
		string description;
		TaskEntryStatus status;

		/**
		 * Mutual initializer, all constructors should call this!
		 */
		void init(
			const string& input_description,
			const uint64_t& input_time_created,
			const TaskEntryStatus& input_status = BACKLOG,
			const uint64_t& input_time_due = 0);

	public:
		/**
		 * Construct a new TaskEntry with just a string.
		 */
		TaskEntry(const string& input_description);

		/**
		 * Construct a new TaskEntry with a string and
		 * a manual time value. This can be used for testing.
		 */
		TaskEntry(const string& input_description, const uint64_t& input_time_created);

		/**
		 * Returns the description as a string
		 */
		string getDescription() const;

		/**
		 * Returns the creation time in milliseconds
		 */
		uint64_t getTimeCreatedMs() const;
		
		/**
		 * Returns the creation time as a natural language string
		 */
		string getTimeCreatedStr() const;

		string getId() const;

		TaskEntryStatus getStatus() const;

		/**
		 * Used in collections to identify entries
		 */
		bool operator==(const TaskEntry& right) const;
	};
}