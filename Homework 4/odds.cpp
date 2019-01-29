//odds.cpp
//
//Adam Cole
//004912373
//Homework 4 Problem 3a

// Remove the odd integers from v.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original vector.
void removeOdds(vector<int>& v)
{
	vector<int>::iterator var = v.begin();
	while (var != v.end()) {
		if ((*var) % 2 == 1) {
			//odd
			var = v.erase(var);
		}
		else {
			//only increase the iterator if you delete an item
			var++;
		}
	}
}