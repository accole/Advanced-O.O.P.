//mazestack.cpp
//
//Homework 2 problem 1

//#include <stack>
#include <iostream>
using namespace std;

//Coord class
class Coord {
public:
	Coord(int rr = 0, int cc = 0) : m_r(rr), m_c(cc) {}	//constructor
	int r() const { return m_r; }	//return row
	int c() const { return m_c; }	//return col
private:
	int m_r;		//row
	int m_c;		//column
};

//Stack Class
const int SIZE = 100;
using ItemType = Coord;

class Stack {
public:
	Stack() : m_top(0) {}
	void push(ItemType value) {
		if (m_top >= SIZE) { return; }
		m_stack[m_top] = value; m_top++;
	}
	void pop() { if (m_top == 0) { return; } m_top--; }
	ItemType top() { return m_stack[m_top - 1]; }
	bool empty() { return (m_top == 0); }
	int size() { return m_top; }
private:
	int m_top;				//"size" of the elements in Stack
	ItemType m_stack[SIZE];	//fixed array to store the stack of values
};

//methods
bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

//int main
int main() {
	char maze[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
	{ 'X','.','.','.','.','.','.','.','.','X' },
	{ 'X','X','X','X','X','.','X','.','X','X' },
	{ 'X','.','.','.','X','.','X','.','.','X' },
	{ 'X','.','X','.','.','.','X','.','.','X' },
	{ 'X','.','X','X','X','.','X','X','X','X' },
	{ 'X','X','X','.','.','.','.','X','.','X' },
	{ 'X','.','X','X','.','X','X','X','.','X' },
	{ 'X','.','.','.','.','X','.','.','.','X' },
	{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 6, 5, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}

//south = increasing r
//north = decreasing r
//east= increasing c
//west = decreasing c

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	//return true if a path through the maze exists
	//false otherwise
	//-------------------------
	//create a stack of coordinates
	Stack s;
	//push the starting coordinate onto the stack and update maze
	s.push(Coord(sr, sc));
	maze[sr][sc] = 'D';			//'D' = discovered
	//while the stack is not empty
	while (!s.empty()) {
		//Pop the top coordinate off the stack.This gives you the current
		//(r,c) location that your algorithm is exploring.
		Coord temp = s.top();
		//for question 2 of HW 2
		cout << "(" << temp.r() << "," << temp.c() << ")" << endl;
		s.pop();
		//If the current(r,c) coordinate is equal to the ending coordinate,
		//then we've solved the maze so return true! 
		if (temp.r() == er && temp.c() == ec) { return true; }
		//Check each place you can move from the current cell as follows :
		//North, West, South, East
		//------------
		//north
		if (maze[temp.r() - 1][temp.c()] == '.') {
			//push the coordinate onto the stack to be searched
			s.push(Coord(temp.r() - 1, temp.c()));
			//mark the element in the array as discovered
			maze[temp.r() - 1][temp.c()] = 'D';
		}
		//west
		if (maze[temp.r()][temp.c() - 1] == '.') {
			s.push(Coord(temp.r(), temp.c() - 1));
			maze[temp.r()][temp.c() - 1] = 'D';
		}
		//south
		if (maze[temp.r() + 1][temp.c()] == '.') {
			s.push(Coord(temp.r() + 1, temp.c()));
			maze[temp.r() + 1][temp.c()] = 'D';
		}
		//east
		if (maze[temp.r()][temp.c() + 1] == '.') {
			s.push(Coord(temp.r(), temp.c() + 1));
			maze[temp.r()][temp.c() + 1] = 'D';
		}
	}
	//if function runs through while loop, no solution
	return false;
}

//PSEUDOCODE:

// Push the starting coordinate(sr, sc) onto the coordinate stack and
//	update maze[sr][sc] to indicate that the algorithm has encountered
//	it(i.e., set maze[sr][sc] to have a value other than '.').
// While the stack is not empty,
// { Pop the top coordinate off the stack.This gives you the current
//		(r,c) location that your algorithm is exploring.
//	 If the current(r,c) coordinate is equal to the ending coordinate,
//		then we've solved the maze so return true! 
//	 Check each place you can move from the current cell as follows :
//		If you can move NORTH and haven't encountered that cell yet,
//			then push the coordinate(r - 1,c) onto the stack and update
//			maze[r - 1][c] to indicate the algorithm has encountered it.
//		If you can move WEST and haven't encountered that cell yet,
//			then push the coordinate(r,c - 1) onto the stack and update
//			maze[r][c - 1] to indicate the algorithm has encountered it.
//		If you can move SOUTH and haven't encountered that cell yet,
//			then push the coordinate(r + 1,c) onto the stack and update
//			maze[r + 1][c] to indicate the algorithm has encountered it.
//		If you can move EAST and haven't encountered that cell yet,
//			then push the coordinate(r,c + 1) onto the stack and update
//			maze[r][c + 1] to indicate the algorithm has encountered it.
// }
// There was no solution, so return false
