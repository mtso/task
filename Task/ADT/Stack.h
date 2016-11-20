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

	/**
	 * Stack Class Implementation
	 */

	template <typename DataType>
	Stack<DataType>::~Stack()
	{
		// Do we need to explicitly call?
	}

	template <typename DataType>
	bool Stack<DataType>::isEmpty() const
	{
		// Return superclass's isEmpty function.
		return List<DataType>::isEmpty();
	}

	template <typename DataType>
	int Stack<DataType>::getLength() const
	{
		// Return superclass's getLength function.
		return List<DataType>::getLength();
	}

	template <typename DataType>
	void Stack<DataType>::clear()
	{
		List<DataType>::clear();
	}

	template <typename DataType>
	bool Stack<DataType>::push(const DataType& item)
	{
		return addFirst(item);
	}

	template <typename DataType>
	DataType Stack<DataType>::pop()
	{
		DataType value = head->getData();
		List<DataType>::removeFirst();
		return value;
	}

	template <typename DataType>
	DataType Stack<DataType>::peek()
	{
		return head->getData();
	}
}

#endif
