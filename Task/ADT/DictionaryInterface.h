


#ifndef ADT_DICTIONARYINTERFACE_H
#define ADT_DICTIONARYINTERFACE_H

namespace adt {
	template <typename KeyType, typename ValueType>
	class DictionaryInterface
	{
	public:
		virtual bool isEmpty() const = 0;
		virtual int count() const = 0;
		virtual bool insert(const KeyType& new_key, const ValueType& new_value) = 0;
	};
}

#endif