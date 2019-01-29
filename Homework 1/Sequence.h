//Sequence.h

#ifndef SEQUENCE_H
#define SEQUENCE_H

//#include <String>
//using ItemType = std::string;
using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 200;

class Sequence
{
public:
	Sequence();    
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
	int m_size;
	ItemType m_arr[DEFAULT_MAX_ITEMS];
};

#endif //SEQUENCE_H