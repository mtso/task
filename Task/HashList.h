
#ifndef TASK_HASHLIST_H
#define TASK_HASHLIST_H

#include "HashEntry.h"

namespace task
{

	T_KV
	class HashList
	{
	private:
		HashEntry<KV>* head;

		int list_length;

	public:
		class NotFoundException
		{
		private:
			string description = "Value not found";
		public:
			string getDescription() const { return description; }
		};

		HashList();

		virtual ~HashList();

		virtual int length() const;

		virtual bool isEmpty() const;

		virtual bool contains(const KeyType& target_key) const;

		virtual ValueType getValue(const KeyType& target_key) const;

		virtual void addFirst(const KeyType& new_key, const ValueType& new_value);

		virtual bool remove(const KeyType& delete_key);

		virtual bool removeFirst();

		void clear();
	};

	/**
	IMPLEMENTATION
	 */

	T_KV
	HashList<KV>::HashList()
		: head(nullptr)
		, list_length(0)
	{
	}

	T_KV
	HashList<KV>::~HashList()
	{
		clear();
	}

	T_KV
	int HashList<KV>::length() const
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
	bool HashList<KV>::contains(const KeyType& target_key) const
	{
		HashEntry<KV>* search = head;

		while (search != nullptr) {
			if (search->getKey() == target_key) {
				return true;
			}
			search = search->getNext();
		}
		return false;
	}

	T_KV
	ValueType HashList<KV>::getValue(const KeyType& target_key) const
	{
		HashEntry<KV>* search = head;

		while (search != nullptr) {
			if (search->getKey() == target_key) {
				return search->getValue();
			}
			search = search->getNext();
		}
		throw NotFoundException();
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
		if (isEmpty()) {
			return false;
		}

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
	bool HashList<KV>::remove(const KeyType& delete_key) // why can't this parameter be const?
	{
		HashEntry<KV>* to_remove = head;
		HashEntry<KV>* previous = nullptr;
		
		while (to_remove != nullptr) 
		{
			if (to_remove->getKey() == delete_key) {
				// delete entry

				if (previous == nullptr) {
					removeFirst();
					return true;
				}

				previous->setNext(to_remove->getNext());
				delete to_remove;
				list_length--;
				return true;
			}
			
			previous = to_remove;
			to_remove = to_remove->getNext();
		}
		return false;
	}

}

#endif