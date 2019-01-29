//mazesqueue.cpp
//
//Homework 2 problem 3


#include <queue>
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

//Queue Class
using ItemType = Coord;

class Queue {
public:
	Queue() { m_head = nullptr; m_tail = m_head; m_elements = 0; }
	void enqueue(ItemType a) {
		//insert the item at the end of the queue
		Node* temp = new Node;
		temp->value = a;
		//check if empty list
		if (m_head == nullptr) {
			m_head = temp;
			temp->next = nullptr;
			m_tail = temp;
			return;
		}
		Node* trav = m_head;
		while (trav->next != nullptr) {
			trav = trav->next;
		}
		trav->next = temp;
		temp->next = nullptr;
		m_tail = temp;
		m_elements++;
	}
	ItemType dequeue() {
		//removes and returns the top item from the front of the queue
		Node* temp = m_head;
		m_head = m_head->next;
		ItemType val = temp->value;
		delete temp;
		m_elements--;
		return val;
	}
	bool isEmpty() {return (m_elements == 0);}
	int size() {return m_elements;}
	ItemType getFront() {return m_head->value;}
private:
	struct Node {
		ItemType value;
		Node* next;
	};
	Node* m_head;
	Node* m_tail;
	int m_elements;
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
	//returns true if there's a path through the maze, false otherwise
	//-------------
	//create a Queue
	/*Queue q;*/
	queue<Coord> q;
	//insert starting point onto the queue and mark discovered
	/*q.enqueue(Coord(sr, sc));*/
	q.push(Coord(sr, sc));
	maze[sr][sc] = 'D';
	//while queue isn't empty
	while (/*!q.isEmpty()*/ !q.empty()) {
		//remove the top from the queue
		Coord temp = /*q.getFront();*/ q.front();
		//for question 4 of HW 2
		cout << "(" << temp.r() << "," << temp.c() << ")" << endl;
		/*q.dequeue();*/
		q.pop();
		//if the point equals the end coordinate, return true!
		if (temp.r() == er && temp.c() == ec) {return true;}
		//Check each place you can move from the current cell as follows:
		//Check North, West, South, East
		//----------------------
		//north
		if (maze[temp.r() - 1][temp.c()] == '.') {
			//mark spot as discovered
			maze[temp.r() - 1][temp.c()] = 'D';
			//add the coordinate to the queue
			/*q.enqueue(Coord(temp.r() - 1, temp.c()));*/
			q.push(Coord(temp.r() - 1, temp.c()));
		}
		//west
		if (maze[temp.r()][temp.c() - 1] == '.') {
			maze[temp.r()][temp.c() - 1] = 'D';
			/*q.enqueue(Coord(temp.r(), temp.c() - 1));*/
			q.push(Coord(temp.r(), temp.c() - 1));
		}
		//south
		if (maze[temp.r() + 1][temp.c()] == '.') {
			maze[temp.r() + 1][temp.c()] = 'D';
			/*q.enqueue(Coord(temp.r() + 1, temp.c()));*/
			q.push(Coord(temp.r() + 1, temp.c()));
		}
		//east
		if (maze[temp.r()][temp.c() + 1] == '.') {
			maze[temp.r()][temp.c() + 1] = 'D';
			/*q.enqueue(Coord(temp.r(), temp.c() + 1));*/
			q.push(Coord(temp.r(), temp.c() + 1));
		}
	}
	//if the queue is empty, no solution
	return false;
}

//PSEUDOCODE:

//Insert starting point onto the queue
//mark the starting point as "discovered"
//if the queue is empty, there is NO SOLUTION and we're done
//remove the top from the queue
//if we're at the endpoint, DONE! Otherwise...
//If slot to the WEST is open & undiscovered
//	mark(r, c-1) as discovered
//	INSERT (r, c-1) on the Queue
//If slot to the EAST is open & undiscovered
//	""	(r, c+1)
//If slot to the NORTH is open and undiscovered
//	""	(r-1, c)
//If slot to the SOUTH is open and undiscovered
//	""	(r+1, c)
//GoTo "if the queue is empty, there is NO SOLUTION and we're done"
