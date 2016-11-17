// Diagnostic.cpp
// Task
// CIS 22C F2016: Matthew Tso

#include "Diagnostic.h"

namespace task {

	void Diagnostic::run()
	{
		throw "Diagnostic::run() has not been implemented yet";
	}

	ostream& Diagnostic::runWith(ostream& output_stream)
	{
		output_stream << "Diagnostic::run(ostream&) has not been implemented yet";
		return output_stream;
	}
}