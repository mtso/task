// DictionaryInterface.h
// Task/ADT
// CIS 22C F2016: Matthew Tso

#ifndef ADT_DICTIONARYINTERFACE_H
#define ADT_DICTIONARYINTERFACE_H

namespace adt {
	template <typename KeyType, typename ValueType>
	class DictionaryInterface
	{
	public:
		virtual ~DictionaryInterface() {}

		virtual bool isEmpty() const = 0;
		virtual int count() const = 0;
		virtual bool insert(const KeyType& new_key, const ValueType& new_value) = 0;
		virtual bool remove(const KeyType& search_key) = 0;
		virtual void clear() = 0;
		virtual ValueType getValue(const KeyType& search_key) const = 0;
		virtual bool contains(const KeyType& search_key) const = 0;
		virtual void traverse(void visit(ValueType&)) const = 0;
	};
}

#endif