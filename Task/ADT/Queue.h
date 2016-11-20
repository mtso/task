// Queue.h
// Lab 2b: Queue ADT
// CIS 22C F2016: Adrian Marroquin, Matthew Tso

#ifndef ADT_QUEUE_H
#define ADT_QUEUE_H

#include "List.h"

#define T_DATA template <typename DataType>

namespace adt 
{
	T_DATA
	class Queue : protected adt::List<DataType>
	{
	public:
		~Queue();

		/**
		 * Expose isEmpty
		 */
		bool isEmpty();

		/**
		 * Expose getLength
		 */
		int getLength();

		/**
		 * Adds an item to the top of the list.
		 */
		bool enqueue(const DataType& item);

		/**
		 * Removes an item from the end of the list
		 * (the item that the tail is pointing to)
		 */
		DataType dequeue();
	};

	/**
	 * Queue class implementation
	 */


	T_DATA
		Queue<DataType>::~Queue()
	{
		}

	T_DATA
		bool Queue<DataType>::isEmpty()
	{
			return List<DataType>::isEmpty();
		}

	T_DATA
		int Queue<DataType>::getLength()
	{
			return List<DataType>::getLength();
		}

	T_DATA
		bool Queue<DataType>::enqueue(const DataType& item)
	{
			return addLast(item);
		}

	T_DATA
		DataType Queue<DataType>::dequeue()
	{
			DataType returnItem = head->getData();
			List<DataType>::removeFirst();
			return returnItem;
		}
}

#endif