// AppCommands.h
// TaskApp
// CIS 22C F2016: Matthew Tso

#ifndef TASKAPP_APPCOMMANDS_H
#define TASKAPP_APPCOMMANDS_H

namespace taskapp {

	enum AppCommand
	{
		CMD_LIST,
		CMD_CREATE,
		CMD_UPDATE,
		CMD_DELETE,
		CMD_HISTORY,
		CMD_UNDO,
		CMD_TEST,
		CMD_QUIT,
		CMD_HELP,
		CMD_SEARCH,
		CMD_UNRECOGNIZED
	};
}

#endif