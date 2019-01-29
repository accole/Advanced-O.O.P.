//ScoreList.cpp

#include "Sequence.h"
#include "ScoreList.h"
#include <limits>

ScoreList::ScoreList() {
	// Create an empty score list.
}

bool ScoreList::add(ItemType score) {
	// If the score is valid (a value from 0 to 100) and the score list
	// has room for it, add it to the score list and return true.
	// Otherwise, leave the score list unchanged and return false.
	if (score < 0 || score > 100) {
		return false;
	}
	if (m_sequence.size() != DEFAULT_MAX_ITEMS) {
		m_sequence.insert(score);
	}
	return true;
}

bool ScoreList::remove(ItemType score) {
	// Remove one instance of the specified score from the score list.
	// Return true if a score was removed; otherwise false.
	if (m_sequence.erase(m_sequence.find(score)) > 0) {
		return true;
	}
	return false;
}

int ScoreList::size() const {
	// Return the number of scores in the list.
	return m_sequence.size();
}

ItemType ScoreList::minimum() const {
	// Return the lowest score in the score list.  If the list is
	// empty, return NO_SCORE.
	if (m_sequence.empty()) {
		return NO_SCORE;
	}
	ItemType minimum;
	ItemType other;
	m_sequence.get(0, minimum);
	for (int i = 1; i < m_sequence.size(); i++) {
		m_sequence.get(i, other);
		if (other < minimum) {
			minimum = other;
		}
	}
	return minimum;
}
	

ItemType ScoreList::maximum() const {
	// Return the highest score in the score list.  If the list is
	// empty, return NO_SCORE.
	if (m_sequence.empty()) {
		return NO_SCORE;
	}
	ItemType maximum;
	ItemType other;
	m_sequence.get(0, maximum);
	for (int i = 1; i < m_sequence.size(); i++) {
		m_sequence.get(i, other);
		if (other > maximum) {
			maximum = other;
		}
	}
	return maximum;
}