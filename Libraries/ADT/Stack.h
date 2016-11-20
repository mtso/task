// Stack.h
// Lab 2: Stack ADT
// CIS 22C F2016: Adrian Marroquin, Matthew Tso

#ifndef ADT_STACK_H
#define ADT_STACK_H

#include "List.h"

namespace adt {
/*
 * Stack Class
 * The Stack object provides Push and Pop functions.
 * The Class provides the boolean function isEmpty.
 */
	template <typename DataType>
	class Stack : protected List<DataType>
	{
	public:
		~Stack(); // Destructor

		/**
			* Exposes lists's isEmpty
			*/
		bool isEmpty() const;

		/**
			* Returns the number of items in the stack.
			*/
		int getLength() const;

		/**
			* Expose clear
			*/
		void clear();

		/**
			* Push adds an item to the top of the stack.
			*/
		bool push(const DataType& item);

		/**
			* Pop removes the first item from the stack.
			*/
		DataType pop();

		/*
			* Peek returns the value of the first item from the stack.
			*/
		DataType peek();
	};
}

//#include "Stack.cpp"
#endif