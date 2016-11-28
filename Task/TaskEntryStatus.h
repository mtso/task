
#ifndef TASK_TASKENTRYSTATUS_H
#define TASK_TASKENTRYSTATUS_H

#include <string>

enum TaskEntryStatus
{
	BACKLOG,
	IN_PROGRESS,
	COMPLETE
};

static std::string backlog("backlog");
static std::string in_progress("in_progress");
static std::string complete("complete");
static std::string unkown("unkown");

inline TaskEntryStatus getStatus(const std::string& str)
{
    if (in_progress == str)
    {
        return IN_PROGRESS;
    }
    else if (complete == str)
    {
        return COMPLETE;
    }
    else
    {
        return BACKLOG;
    }
}

inline std::string &getStatusString(TaskEntryStatus status)
{
    switch (status)
    {
        case BACKLOG:
            return backlog;
        case IN_PROGRESS:
            return in_progress;
        case COMPLETE:
            return complete;
        default:
            return unkown;
    }
}

#endif