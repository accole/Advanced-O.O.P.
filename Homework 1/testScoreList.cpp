//testSequence.cpp

#include "Sequence.h"
#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	ScoreList seq;
	assert(seq.add(45));
	assert(seq.remove(45));
	assert(seq.add(800) == false);
	assert(seq.add(49));
	assert(seq.size() == 1);
	seq.add(57);
	seq.add(39);
	assert(seq.maximum() == 57);
	assert(seq.minimum() == 39);
	cout << "Passed all tests" << endl;
}