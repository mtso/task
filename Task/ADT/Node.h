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

	/**
	 * Node Template class Implementation
	 */
	template <typename DataType>
	Node<DataType>::Node() : next(nullptr)
	{
	}

	template <typename DataType>
	Node<DataType>::Node(const DataType& initialData)
		: data(initialData)
		, next(nullptr)
	{
	}

	template <typename DataType>
	Node<DataType>::Node(const DataType& initialData, Node<DataType>* nextNode)
		: data(initialData)
		, next(nextNode)
	{
	}

	template <typename DataType>
	Node<DataType>* Node<DataType>::getNext() const
	{
		return next;
	}

	template <typename DataType>
	void Node<DataType>::setNext(Node<DataType>* newNext)
	{
		next = newNext;
	}

	template <typename DataType>
	DataType Node<DataType>::getData() const
	{
		return data;
	}

	template <typename DataType>
	void Node<DataType>::setData(const DataType& newData)
	{
		data = newData;
	}

}

#endif