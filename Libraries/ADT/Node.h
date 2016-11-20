// Node.h
// Lab 2: Stack ADT
// CIS 22C F2016: Adrian Marroquin, Matthew Tso

#ifndef ADT_NODE_H
#define ADT_NODE_H

namespace adt 
{
	/**
	 * Node Class
	 * The node object contains two attributes: the data item and a pointer to the next node.
	 * The class provides accessors and modifiers for both attributes.
	 */
	template <typename DataType>
	class Node
	{
	private:
		// The piece of data that this object holds
		DataType data;

		// Pointer to the next node in the list
		Node<DataType>* next;

	public:
		/**
		 * Default constructor
		 * Initialized with a garbage value for data
		 * and `nullptr` for next
		 */
		Node();

		/**
		 * Construct with data
		 * @param initialData
		 */
		Node(const DataType& initialData);

		/**
		 * Construct with data and next node
		 * @param initialData
		 * @param nextNode the next node in the list
		 */
		Node(const DataType& initialData, Node<DataType>* nextNode);

		/**
		 * Returns a pointer to the next node.
		 * @returns The pointer to next.
		 */
		Node<DataType>* getNext() const;

		/**
		 * Sets the next pointer to a new node.
		 * @param newNext The pointer to the next node in the list.
		 */
		void setNext(Node<DataType>* newNext);

		/**
		 * Returns the data that this node holds.
		 * @returns The data item.
		 */
		DataType getData() const;

		/**
		 * Sets a new piece of data for this node to hold.
		 * @param newData
		 */
		void setData(const DataType& newData);
	};
}

#include "Node.cpp"
#endif