// HashList.cpp
// Task
// CIS 22C F2016: Matthew Tso

#ifndef TASK_HASHLISTIMPLEMENTATION_H
#define TASK_HASHLISTIMPLEMENTATION_H

#include "HashList.h"

namespace task 
{
	T_KV
	HashList<KV>::HashList()
		: head(nullptr)
		, list_length(0)
		, access_count(0)
	{
	}

	T_KV
	HashList<KV>::~HashList()
	{
		clear();
	}

	T_KV
	unsigned int HashList<KV>::length() const
	{
		return list_length;
	}

	T_KV
	bool HashList<KV>::isEmpty() const
	{
		return head == nullptr;
	}

	T_KV
	void HashList<KV>::clear()
	{
		while (!isEmpty()) {
			removeFirst();
		}
	}

	T_KV
	HashEntry<KV>* HashList<KV>::pointerTo(const KeyType& target_key)
	{
		HashEntry<KV>* search = head;
		HashEntry<KV>* previous = nullptr;

		while (search != nullptr) 
		{
			access_count++;
			if (search->getKey() == target_key) 
			{
				// If not the first node,
				// set as first node.
				if (previous != nullptr) 
				{
					previous->setNext(search->getNext());
					search->setNext(head);
					head = search;
				}

				return search;
			}
			previous = search;
			search = search->getNext();
		}
		return nullptr;
	}

	T_KV
	bool HashList<KV>::contains(const KeyType& target_key)
	{
		return (pointerTo(target_key) == nullptr) ? false : true;
	}

	T_KV
	ValueType HashList<KV>::getValue(const KeyType& target_key)
	{
		HashEntry<KV>* search = pointerTo(target_key);
		if (search != nullptr) {
			return search->getValue();
		}
		else {
			throw NotFoundException();
		}
	}

	T_KV
	ValueType& HashList<KV>::getRawValue(const KeyType& target_key)
	{
		HashEntry<KV>* search = pointerTo(target_key);
		if (search != nullptr) {
			return search->getRawValue();
		}
		else {
			throw NotFoundException();
		}
	}

	T_KV
	void HashList<KV>::addFirst(const KeyType& new_key, const ValueType& new_value)
	{
		HashEntry<KV>* new_entry = new HashEntry<KV>(new_key, new_value, head);
		head = new_entry;
		list_length++;
	}

	T_KV
	bool HashList<KV>::removeFirst()
	{
		if (isEmpty()) { return false; }

		// Un-link first entry
		HashEntry<KV>* to_remove = head;
		head = head->getNext();

		// Delete un-linked entry
		delete to_remove;
		to_remove = nullptr;

		list_length--;
		return true;
	}

	T_KV
	bool HashList<KV>::remove(const KeyType& delete_key)
	{
		HashEntry<KV>* to_remove = head;
		HashEntry<KV>* previous = nullptr;

		while (to_remove != nullptr)
		{
			if (to_remove->getKey() != delete_key) {
				previous = to_remove;
				to_remove = to_remove->getNext();
				continue;
			}

			// delete first entry
			if (previous == nullptr) {
				removeFirst();
				return true;
			}

			// delete an entry
			previous->setNext(to_remove->getNext());
			delete to_remove;
			list_length--;
			return true;
		}
		return false;
	}

	T_KV
	void HashList<KV>::traverse(void visit(ValueType& entry)) const
	{
		if (isEmpty()) {
			return;
		}

		HashEntry<KV>* current = head;
		while (current != nullptr) {
			ValueType value = current->getValue();
			visit(value);
			current = current->getNext();
		}
	}

	T_KV
	KeyType HashList<KV>::peekKey()
	{
		return head->getKey();
	}

	T_KV
	ValueType HashList<KV>::peekValue()
	{
		return head->getValue();
	}

	T_KV
	int HashList<KV>::getAccessCountFor(const KeyType& target_key)
	{
		access_count = 0;
		if (contains(target_key)) {
			return access_count;
		}
		else {
			throw NotFoundException();
		}
	}
}

#endif