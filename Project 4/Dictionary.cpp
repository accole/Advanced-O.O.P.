// Dictionary.cpp


// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include <algorithm>	// for sorting
#include <functional>	// for hash function
using namespace std;

//Number of Buckets - prime number and max number
const int NUM_BUCKETS = 49999;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

  // This class does the real work of the implementation.

class DictionaryImpl
{
  public:
	DictionaryImpl() { 
		  //create NUM_BUCKETS buckets and initialize them to empty and null
		  for (int i = 0; i < NUM_BUCKETS; i++) { 
			  m_words[i] = new BUCKET; 
			  m_words[i]->next = nullptr; 
			  m_words[i]->word = "";
			  m_words[i]->sorted = "";
		  } 
	 }
    ~DictionaryImpl() {
		//delete every bucket in each linked list
		for (int i = 0; i < NUM_BUCKETS; i++) {
			//loops through all the created hash buckets
			BUCKET* temp = m_words[i];
			//loop through the linked list in each Bucket in m_words
			while (temp->next != nullptr) {
				BUCKET* del = temp;
				temp = temp->next;
				delete del;
			}
		}
	}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
  private:
	  struct BUCKET { 
		  string word;		//inputted word
		  string sorted;	//inputted word sorted
		  BUCKET* next;		//points to the next bucket in a linked list
	  };
	  unsigned int hashFunc(const std::string &input) const;
	  BUCKET* m_words[NUM_BUCKETS];
};

unsigned int DictionaryImpl::hashFunc(const std::string &input) const {
	//code given to us in lecture 15 slides
	std::hash<std::string> str_hash;	//creates a string hasher
	unsigned int hashed = str_hash(input);	//hashes string
	unsigned int bucketNum = hashed % NUM_BUCKETS;
	return bucketNum;
}

void DictionaryImpl::insert(string word)
{
	//insert based on the sorted string
    removeNonLetters(word);
	if (!word.empty()) {
		//insert the word
		//sort the inputed word into alphabetical order
		std::string sortd = word;
		sort(sortd.begin(), sortd.end());
		//plug word into the hash function
		int bucket = hashFunc(sortd);
		//find the correct bucket
		BUCKET* temp = m_words[bucket];
		if (temp == nullptr) {
			//first insertion into that bucket
			temp = new BUCKET;
			temp->next = nullptr;
			temp->word = word;
			temp->sorted = sortd;
		}
		else {
			//already BUCKETS in the linked list
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			//temp now points to the last BUCKET in the linked list
			//add a new BUCKET after
			temp->next = new BUCKET;
			//point the next to nullptr
			temp->next->next = nullptr;
			//set the word = word
			temp->next->word = word;
			//set the sorted version = sorted
			temp->next->sorted = sortd;
		}
	}
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
	//instead of looking up each permutation and searching for it in the buckets
	//	look up each sorted word and return the real word

    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

	//sort the string letters
	string sortedword = letters;
	sort(sortedword.begin(), sortedword.end());
	//plug sorted word into the hash function
	int bucket = hashFunc(sortedword);

	//find the correct bucket and search the linked list
	BUCKET* temp = m_words[bucket];
	while (temp != nullptr) {
		//most elements of the linked list at the bucket are anagrams
		if (temp->sorted == sortedword) {
			callback(temp->word);
		}
		temp = temp->next;
	}
	//no such element exists
}
    
void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
} 

  // Each successive call to this function generates the next permutation of the
  // characters in the parameter.  For example,
  //    string s = "eel";
  //    generateNextPermutation(s);  // now s == "ele"
  //    generateNextPermutation(s);  // now s == "lee"
  //    generateNextPermutation(s);  // now s == "eel"
  // You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;

    for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p+1; q <= last  &&  *q > *(p-1); q++)
            ;
        swap(*(p-1), *(q-1));
    }
    for ( ; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions ********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
