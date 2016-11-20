// List.cpp
// Lab 2: Stack ADT
// CIS 22C F2016: Adrian Marroquin, Matthew Tso

//#ifndef ADT_LIST_CPP
//#define ADT_LIST_CPP

//#include "List.h"

namespace adt {

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
//#endif