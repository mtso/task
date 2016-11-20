// Node.cpp
// Lab 2: Stack ADT
// CIS 22C F2016: Adrian Marroquin, Matthew Tso

//#ifndef ADT_NODE_CPP
//#define ADT_NODE_CPP

//#include "Node.h"

namespace adt 
{
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

//#endif