// TaskConfiguration.h
// TaskApp
// CIS 22C F2016: Matthew Tso
//
// Defines constants used in the console app

#ifndef TASKAPP_APPCONSTANTS_H
#define TASKAPP_APPCONSTANTS_H

// Standard shell is roughly 80 col wide (79 char)
//
// Ruler                  |===============================================================================|
// Ruler 7-1-7            |=======-=======-=======-=======-=======-=======-=======-=======-=======-=======|

namespace taskconfig {

    const char* VERSION = "0.0.1";
    
    const char* CREDITS = "task was designed and built by Adrian Marroquin, Matthew Tso, Xin He, and Jinzhu Shen at De Anza College for CIS 22C with Professor Manish Goel in the quarter of Fall 2016.";
    
    // Command input options
    const char COMMAND_TEST_CH      = 'T';
    const char* COMMAND_TEST_STR    = "task";
    
    const char COMMAND_CREDITS_CH   = 'C';
    const char* COMMAND_CREDITS_STR = "credits";
    
    const char COMMAND_QUIT_CH      = 'Q';
    const char* COMMAND_QUIT_STR    = "quit";


	// Task entry
	const string STATUS_STR_BACKLOG = "Backlog";
	const string STATUS_STR_INPROGRESS = "In-progress";
	const string STATUS_STR_COMPLETE = "Complete";
}

#endif /* TaskConfiguration_h */
