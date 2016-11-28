#ifndef TASK_INTERFACE_H
#define TASK_INTERFACE_H

#include <string>
#include "TaskEntry.h"

void TaskRunner(task::TaskEntry task, std::string command);

#endif