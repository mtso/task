// List.h
// Lab 2: Stack ADT
// CIS 22C F2016: Adrian Marroquin, Matthew Tso

#ifndef ADT_LIST_H
#define ADT_LIST_H

#include "Node.h"
#include <iostream>

using namespace std;

namespace adt {

	/**
	 * Linked List implementation of Bag ADT
	 *
	 */
	template <typename DataType>
	class List
	{
	protected:
		// Pointer to the first node of the list.
		Node<DataType>* head;

		// Pointer to the last node of the list.
		Node<DataType>* tail;

		// Keeps track of the number of list items.
		int length;

		/**
		 * Returns the pointer to an item
		 */
		Node<DataType>* getPointerTo(const DataType& item) const;

	public:
		List();				// Default constructor
		virtual ~List();	// Virtual destructor

		/**
		 * Returns the list length.
		 */
		virtual int getLength() const;

		/**
		 * Returns whether the list is empty or not.
		 * @returns True if the list is empty, false if not.
		 */
		virtual bool isEmpty() const;

		/**
		 * Returns true if the list contains the data item
		 */
		virtual bool contains(const DataType& item) const;

		/**
		 * Adds an item into the beginning of the list.
		 * @param newItem The new <DataType> item to add.
		 * @returns True if successful, false if unsuccessful.
		 */
		bool addFirst(const DataType& newItem);

		/**
		* Adds an item into the end of the list.
		* @param newItem The new <DataType> item to add.
		* @returns True if successful, false if unsuccessful.
		*/
		bool addLast(const DataType& newItem);

		/**
		 * Removes an item from the list
		 */
		bool remove(const DataType& toRemove);

		/**
		 * Removes the first item from the list
		 */
		bool removeFirst();

		/**
		* Removes the first item from the list
		*/
		bool removeLast();

		/**
		 * Removes all the items from the list
		 */
		void clear();

		/*
		 * Print out contents of list
		 */
		void printList() const;

		/**
		 * Print contents of list into an output stream.
		 * Used for testing.
		 */
		void printListTo(ostream& out) const;
	};

	/**
	 * List Class Implementation
	 */
	template <typename DataType>
	List<DataType>::List()
		: head(nullptr)
		, tail(nullptr)
		, length(0)
	{
	}

	template <typename DataType>
	List<DataType>::~List()
	{
		clear();
	}

	template <typename DataType>
	int List<DataType>::getLength() const
	{
		return length;
	}

	template <typename DataType>
	bool List<DataType>::isEmpty() const
	{
		return length == 0;
	}

	template <typename DataType>
	bool List<DataType>::contains(const DataType& item) const
	{
		return getPointerTo(item) != nullptr;
	}

	template <typename DataType>
	Node<DataType>* List<DataType>::getPointerTo(const DataType& item) const
	{
		Node<DataType>* search = head;
		while (search != nullptr)
		{
			if (item == search->getData())
			{
				return search;
			}
			else
			{
				search = search->getNext();
			}
		}
		return search;
	}

	template <typename DataType>
	bool List<DataType>::addFirst(const DataType& newItem)
	{
		// TODO: What happens if no new node could be allocated memory?
		if (length == 0)
		{
			head = new Node<DataType>(newItem);
			length++;
			return true;
		}
		else
		{
			Node<DataType>* newNode = new Node<DataType>(newItem, head);
			head = newNode;
			length++;
			return true;
		}
	}

	template <typename DataType>
	bool List<DataType>::addLast(const DataType& newItem)
	{
		Node<DataType>* newNode = new Node<DataType>(newItem);
		if (length == 0)
		{
			tail = newNode;
			head = newNode;
			length++;
			return true;
		}
		else
		{
			tail->setNext(newNode);
			tail = newNode;
			length++;
			return true;
		}
	}

	template <typename DataType>
	bool List<DataType>::remove(const DataType& toRemove)
	{
		Node<DataType>* itemPointer = getPointerTo(toRemove);
		bool shouldRemoveItem = !isEmpty() && itemPointer != nullptr;

		if (shouldRemoveItem)
		{
			itemPointer->setData(head->getData());

			Node<DataType>* toRemovePointer = head;
			head = head->getNext();

			toRemovePointer->setNext(nullptr);
			delete toRemovePointer;
			toRemovePointer = nullptr;

			length--;
		}

		return shouldRemoveItem;
	}

	template <typename DataType>
	bool List<DataType>::removeFirst()
	{
		Node<DataType>* toRemovePointer = head;
		if (head == tail)
		{
			head = nullptr;
			tail = nullptr;
			toRemovePointer->setNext(nullptr);
			delete toRemovePointer;
			toRemovePointer = nullptr;
			length--;
			return true;
		}
		else
		{
			head = head->getNext();
			toRemovePointer->setNext(nullptr);
			delete toRemovePointer;
			toRemovePointer = nullptr;
			length--;
			return true;
		}
		return false;
	}


	template <typename DataType>
	void List<DataType>::clear()
	{
		while (!isEmpty())
		{
			removeFirst();
		}
	}

	template <typename DataType>
	void List<DataType>::printList() const
	{
		printListTo(cout);
	}

	template <typename DataType>
	void List<DataType>::printListTo(ostream& out) const
	{
		if (!isEmpty()) {
			out << head->getData() << endl;
			Node<DataType>* nextNode = head->getNext();
			while (nextNode != nullptr)
			{
				out << nextNode->getData() << endl;
				nextNode = nextNode->getNext();
			}
		}
		else {
			out << "Empty List" << endl;
		}
	}
}

#endif