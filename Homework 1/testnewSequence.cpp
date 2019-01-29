//testSequence.cpp

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Sequence s1;
	s1.insert(0, "paratha");
	s1.insert(0, "focaccia");
	Sequence s2;
	s2.insert(0, "roti");
	s1.swap(s2);
	assert(s1.size() == 1 && s1.find("roti") == 0 && s2.size() == 2 &&
	s2.find("focaccia") == 0 && s2.find("paratha") == 1);
	cout << "All tests passed!" << endl;
}