//Sequence.cpp

#include "Sequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence() {
	//Constructor
	// Create an empty sequence (i.e., one with no items)
	m_size = 0;
}

bool Sequence::empty() const {
	// Return true if the sequence is empty, otherwise false.
	return m_size == 0;
}

int Sequence::size() const {
	// Return the number of items in the sequence.
	return m_size;
}

bool Sequence::insert(int pos, const ItemType& value) {
	// Insert value into the sequence so that it becomes the item at
	// position pos.  The original item at position pos and those that
	// follow it end up at positions one higher than they were at before.
	// Return true if 0 <= pos <= size() and the value could be
	// inserted.  (It might not be, if the sequence has a fixed capacity,
	// e.g., because it's implemented using a fixed-size array.)  Otherwise,
	// leave the sequence unchanged and return false.  Notice that
	// if pos is equal to size(), the value is inserted at the end.
	if (pos < 0 || pos > m_size){
		//return false if fails condition
		return false;
	}
	if (m_size != DEFAULT_MAX_ITEMS) {
		//shift all the elements in the array up one
		int j = m_size;
		m_size++;
		for (int i = j; i >= pos; i--) {
			m_arr[i + 1] = m_arr[i];
		}
		//assign the value to element at pos
		m_arr[pos] = value;
		//return true
		return true;
	}
	return false;
}

int Sequence::insert(const ItemType& value) {
	// Let p be the smallest integer such that value <= the item at
	// position p in the sequence; if no such item exists (i.e.,
	// value > all items in the sequence), let p be size().  Insert
	// value into the sequence so that it becomes the item at position
	// p.  The original item at position p and those that follow it end
	// up at positions one higher than before.  Return p if the value
	// was actually inserted.  Return -1 if the value was not inserted
	// (perhaps because the sequence has a fixed capacity and is full).
	//-------------------------------------------------------------
	int p = m_size;
	//determine p
	for (int x = 0; x < m_size; x++) {
		if (value <= m_arr[x]) {
			p = x;
		}
	}
	//test for capacity
	if (m_size == DEFAULT_MAX_ITEMS) {
		p = -1;
	}
	//insert the value at p
	this->insert(p, value);
	return p;
}

bool Sequence::erase(int pos) {
	// If 0 <= pos < size(), remove the item at position pos from
	// the sequence (so that all items that followed that item end up at
	// positions one lower than they were at before), and return true.
	// Otherwise, leave the sequence unchanged and return false.
	if (pos < 0 || pos >= m_size) {
		return false;
	}
	//shift the elements, losing the value at pos
	for (int i = pos; i < m_size - 1; i++) {
		m_arr[pos] = m_arr[pos + 1];
	}
	//decrement the size and return true
	m_size--;
	return true;
}


int Sequence::remove(const ItemType& value) {
	// Erase all items from the sequence that == value.  Return the
	// number of items removed (which will be 0 if no item == value).
	int erased = 0;
	int j = m_size;
	for (int k = 0; k < j; k++) {
		if (value == m_arr[k]) {
			this->erase(k);
			k--;
			j--;
			erased++;
		}
	}
	return erased;
}


bool Sequence::get(int pos, ItemType& value) const {
	// If 0 <= pos < size(), copy into value the item at position pos
	// in the sequence and return true.  Otherwise, leave value unchanged
	// and return false.
	if (pos < 0 || pos >= m_size) {
		return false;
	}
	value = m_arr[pos];
	return true;
}

bool Sequence::set(int pos, const ItemType& value) {
	// If 0 <= pos < size(), replace the item at position pos in the
	// sequence with value and return true.  Otherwise, leave the sequence
	// unchanged and return false.
	if (pos < 0 || pos >= m_size) {
		return false;
	}
	m_arr[pos] = value;
	return true;
}

int Sequence::find(const ItemType& value) const {
	// Let p be the smallest integer such that value == the item at
	// position p in the sequence; if no such item exists, let p be -1.
	// Return p.
	int p = -1;
	//determine p
	for (int x = 0; x < m_size; x++) {
		if (value == m_arr[x]) {
			p = x;
		}
	}
	return p;
}

void Sequence::swap(Sequence& other) {
	// Exchange the contents of this sequence with the other one.
	//--------------------------------------------
	//find the bigger size
	int biggest;
	if (m_size > other.m_size) {
		biggest = m_size;
	}
	else {
		biggest = other.m_size;
	}
	//swap the elements
	ItemType var;
	for (int i = 0; i < biggest; i++) {
		var = m_arr[i];
		m_arr[i] = other.m_arr[i];
		other.m_arr[i] = var;
	}
	//swap the sizes
	int temp = other.m_size;
	other.m_size = m_size;
	m_size = temp;
}