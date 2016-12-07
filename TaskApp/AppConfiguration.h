// AppConfiguration.h
// TaskApp
// CIS 22C F2016: Matthew Tso
//
// Defines constants used in the console app

#ifndef TASKAPP_APPCONFIGURATION_H
#define TASKAPP_APPCONFIGURATION_H

// Standard shell is roughly 80 col wide (79 char)
//
// Ruler                  |===============================================================================|
// Ruler 7-1-7            |=======-=======-=======-=======-=======-=======-=======-=======-=======-=======|

namespace taskapp {

    //const char* VERSION = "0.1.0";
    
    const char* CREDITS = "task was designed and built by Adrian Marroquin, Matthew Tso, Xin He, and Jinzhu Shen at De Anza College for CIS 22C with Professor Manish Goel in the quarter of Fall 2016.";
    
    // Command input options
    //const char COMMAND_TEST_CH      = 'T';
    //const char* COMMAND_TEST_STR    = "task";
    //
    //const char COMMAND_CREDITS_CH   = 'C';
    //const char* COMMAND_CREDITS_STR = "credits";
    //
    //const char COMMAND_QUIT_CH      = 'Q';
    //const char* COMMAND_QUIT_STR    = "quit";


	// Task entry
	const char* STATUS_STR_BACKLOG = "backlog";
	const char* STATUS_STR_INPROGRESS = "in-progress";
	const char* STATUS_STR_COMPLETE = "complete";

	const char* HELP_TEXT = "Task was built by Adrian Marroquin, Matthew Tso, Jinzhu Shen, and Xin He.\n\n"
		"list [option]\n"
		"\tLists the task items in the order of creation. Options are: all, team.\n\n"
		"new [description]\n"
		"\tCreates a new entry and sets the status to backlog.\n\n"
		"update [id] [option] [argument]\n"
		"\tUpdates an entry's field.\n\n"
		"delete [id]\n"
		"\tDeletes an entry.\n\n"
		"history\n"
		"\tShows the command history of the current session.\n\n"
		"undo\n"
		"\tUndos the last command recorded.\n\n"
		"search [terms]\n"
		"\tSearches the description of the entries.\n\n"
		"test\n"
		"\tTests the addition, deletion, and accesses of the HashTable and BinarySearchTree.\n\n"
		"help\n"
		"\tDisplays information about each command.\n\n"
		"quit\n"
		"\tTerminates task's console process.\n";
}

#endif /* TaskConfiguration_h */
