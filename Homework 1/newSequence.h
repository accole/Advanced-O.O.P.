//newSequence.h

#ifndef NEWSEQUENCE_H
#define NEWSEQUENCE_H

//#include <String>
//using ItemType = std::string;
using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 200;

class Sequence
{
public:
	Sequence(int max = DEFAULT_MAX_ITEMS);
	~Sequence();
	Sequence(const Sequence& other);
	Sequence& operator=(const Sequence& nhs);
	bool empty() const;
	int size() const;
	bool insert(int pos, const ItemType& value);
	int insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);
private:
	//class invariants:
	//0 <= m_size (size of m_arr[]) <= DEFAULT_MAX_ITEMS
	// m_max = max size 
	int m_size;
	int m_max;
	ItemType * m_newseq;
};


#endif //NEWSEQUENCE_H
