//eval.cpp
//
//Problem 5
//HW 2
//
//Adam Cole
//004912373

//includes
#include <string>
#include <stack>
#include <cassert>
#include <stdio.h>
#include <iostream>
using namespace std;

//function declarations
bool valid(string infix);
void conversion(string infix, string& postfix);
bool evaluation(string postfix);
bool apply(char v1, char v2, char operate);
bool greaterPrecedence(char a, char s);

int evaluate(string infix, string& postfix, bool& result) {
	//test if expression is syntactically valid
	if (valid(infix)) {
		//infix to postfix conversion first
		conversion(infix, postfix);
		//evaluate the postfix expression
		result = evaluation(postfix);
		//return 0
		return 0;
	}
	//if not, return 1 and dont change postfix or result
	return 1;
}
//fucntions utilized by evaluate
bool valid(string infix) {
	//returns true if the infix expression is syntactically valid
	//false if otherwise
	//-------------------------
	//examples of being invalid include:
		//"T|"			//true or false must follow an operator
		//"F F"			//spaces are allowed only to seperate valid things
		//"TF"			//true and false can't be subsequent characters
		//"()"			//there must be an argument
		//"T(F|T)"		//must be operators in between operands
		//"T(&T)"		//for | and &, there must be operators on both sides
		//"(T&(F|F)"	//for every '(' must be a ')'
//*		//""			//string can't be empty
	//--------------------------
	if (infix == "")	//empty string
		return false;
	//evaluate each character in the infix string
	//counter for parenthesis (open and closed)
	int open = 0;
	int closed = 0;
	//initial character
	int i = 0;
	char b = infix.at(i);
	//check the first character
	switch (b) {
	case '|':
	case '&':
	case ')':
		return false;
		break;
	case '(':
		open++;
		break;
	case ' ':
		i++;
		break;
	}
	//loop through the rest of the infix string
	for (int j = i + 1; j < infix.size(); j++) {
		//starting from the second character
		char a = infix.at(j);	//after
		b = infix.at(i);		//before
		if (b == ' ')
			b = infix.at(i - 1);
		switch (a) {
		//true or false
		case 'T':
		case 'F':
			//the previous character can't be another 'T' or 'F'
			if (b == 'T' || b == 'F')
				return false;
			break;
		//parenthesis
		case '(':
			//open
			open++;
			if (b == 'T' || b == 'F')
				return false;
			break;
		case ')':
			closed++;
			if (closed > open)
				return false;
			if (b == '(')
				return false;
			break;
		//space
		case ' ':
			//skip ' '
			break;
		//if nothing else, operator
		case '!':
			//only false if theres not an operator before it
			if (b == ')')
				return false;
			else if (b == 'T' || b == 'F')
				return false;
		default:
			if (b == '|' || b == '&' || b == '(')
				return false;
			break;
		}
		//check the last character
		if (j == infix.size() - 1) {
			//last character
			if (a != 'T' && a != 'F' && a != ')' && a != ' ')
				return false;
		}
		//increment the "before" character
		i++;
	}
	if (open > closed)
		return false;
	//if passes through the for loop, return true
	return true;
}
void conversion(string infix, string& postfix) {
	//converts an infix boolean expression to a postfix one
	//-------------------------------
	//empty the postfix
	postfix = "";
	//create a stack of characters
	stack<char> s;
	size_t counter = 0;
	while (counter < infix.size()) {
		//character at each index in the string
		char a = infix.at(counter);
		if (a == 'T' || a == 'F') {
			postfix += a;
		}
		else if (a == '(') {
			s.push(a);
		}
		else if (a == ')') {
			//pop operators off the stack until '('
			while (s.top() != '(') {
				postfix += s.top();
				s.pop();
			}
			//remove the '('
			s.pop();
		}
		else if (a == ' ') {
			//space
			//--------
			//do nothing and move onto the next character
		}
		else {
			//character is an operator
			if (s.empty()) {
				//push the operator onto the stack
				//ex. !
				s.push(a);
			}
			else {
				//not empty
				//-----------------------
				//pop all operators with greater or equal precedence
				//off the stack and append
				while ((s.top() != '(') && (greaterPrecedence(a, s.top()))){
					postfix += s.top();
					s.pop();
				}
				//push new operator onto the stack
				s.push(a);
			}
		}
		//move to the next character
		counter++;
	}
	//if operators are left in the stack, append them
	while (!s.empty()) {
		postfix += s.top();
		s.pop();
	}
}
bool evaluation(string postfix) {
	//evaluates a valid boolean postfix expression and returns the result
	//-----------------
	//create a stack of characters
	stack<char> s;
	int counter = 0;
	//while the counter goes through all the tokens in the stack
	while (counter < postfix.size()) {
		char a = postfix.at(counter);
		//if its true or false, push it onto the stack
		if (a == 'T' || a == 'F')
			s.push(a);
		else {
			if (a == '!') {
				if (s.top() == 'T') {
					//only pop the top character off of the stack
					s.pop();
					//apply the not to the char v1
					s.push('F');
				}
				else {
					//only pop the top character off of the stack
					s.pop();
					//apply the not to the char v1
					s.push('T');
				}
			}
			else {
				//if its an operator, pull out the top two values and
				//perform the operation on the two top values
				char v2 = s.top();
				s.pop();
				char v1 = s.top();
				s.pop();
				//apply the operator to v1 and v2
				//v1 first, v2 second
				//push result onto the stack
				if (apply(v1, v2, a))
					s.push('T');
				else
					s.push('F');
			}
		}
		//increment the character
		counter++;
	}
	//after all tokens have been processed, return the top value on the stack
	if (s.top() == 'T') {
		return true;
	}
	else {
		return false;
	}
}
//fucntions utilized by conversion, evaluation, and valid
bool apply(char v1, char v2, char operate) {
	//return the result of v1 (bool operator) v2
	//---------------------------
	//convert the characters into booleans
	bool vone;
	bool vtwo;
	if (v1 == 'T')
		vone = true;
	else
		vone = false;
	if (v2 == 'T')
		vtwo = true;
	else
		vtwo = false;
	//preform the operation
	switch (operate) {
	case '|':
		return vone | vtwo;
		break;
	case '&':
		return vone & vtwo;
		break;
	}
	return false;
}
bool greaterPrecedence(char a, char s) {
	//returns true if char s has greater or equal precedence than char a
	//false otherwise
	//----------------------
	// ! > & > | 
	//! = ! (equal precedence) associates left to right
	switch (a) {
	case '!':
		//everything will either be of less than or equal precedence
		return false;
		break;
	case '&':
		if (s == '|' || s == '&')
			return false;
		else 
			return true;
		break;
	case '|':
		if (s == '|')
			return false;
		else
			return true;
		break;
	case '(':
		return false;
		break;
	}
	return false;
}
//testing purposes
//int main() {
//	string pf;
//	bool answer;
//	assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|"  &&  answer);
//	assert(evaluate("T|", pf, answer) == 1);
//	assert(evaluate("F F", pf, answer) == 1);
//	assert(evaluate("TF", pf, answer) == 1);
//	assert(evaluate("()", pf, answer) == 1);
//	assert(evaluate("T(F|T)", pf, answer) == 1);
//	assert(evaluate("T(&T)", pf, answer) == 1);
//	assert(evaluate("(T&(F|F)", pf, answer) == 1);
//	assert(evaluate("", pf, answer) == 1);
//	assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
//		&& pf == "FF!TF&&|" && !answer);
//	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
//	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
//	cout << "Passed all tests" << endl;
//}