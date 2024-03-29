#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "rlutil.h"
#include "maze.h"

const char WALL = '#';
const char SPACE = ' ';
const char SOLUTION = '.';


Stack::Stack()
{
	top = nullptr;
}


Stack::~Stack()
{
	while (!isEmpty()) {
		pop();
	}
}


void Stack::push(Cell* cell)
{
	LinkedCell* newTop = new LinkedCell;
	newTop->next = top;
	newTop->data = cell;
	top = newTop;
}


void Stack::pop()
{
	if (isEmpty()) return;

	LinkedCell* currentTop = top;
	top = top->next;

	delete currentTop;
	currentTop = nullptr;
}


bool Stack::isEmpty() const
{
	return top == nullptr ? true : false;
}


Cell* Stack::getTop() const
{
	if (top == nullptr) {
		return nullptr;
	}
	return top->data;
}


int Stack::getLength() const
{
	if (top == nullptr) return 0;

	int length = 0;
	LinkedCell* current = top;

	while (current != nullptr) {
		current = current->next;
		length++;
	}

	return length;
}


Cell* Stack::getRandom() const
{
	int length = getLength();
	int index = rand() % length;
	LinkedCell* current = top;

	while (index != 0) {
		current = current->next;
		index--;
	}

	return current->data;
}


Maze::Maze(int width, int height)
{
	mazeWidth = width;
	mazeHeight = height;

	maze = new Cell[mazeHeight * mazeWidth];

	entranceX = 0;
	entranceY = 0;
	exitX = width - 1;
	exitY = height - 1;

	for (int i = 0; i < mazeHeight; i++) {
		for (int j = 0; j < mazeWidth; j++) {
			maze[i * mazeWidth + j].x = j;
			maze[i * mazeWidth + j].y = i;
			maze[i * mazeWidth + j].index = i * mazeWidth + j;
		}
	}

	stack = new Stack;
	path = new Stack;

	// Start of maze at (0, 0)
	stack->push(&maze[0]);
	nbOfCellsVisited = 1;
	maze[0].visited = true;
}


Maze::~Maze()
{
	delete stack;
	stack = nullptr;

	delete path;
	path = nullptr;

	delete[] maze;
	
	maze = nullptr;
}


void Maze::setEntrance(int x, int y) {
	entranceX = x;
	entranceY = y;
}


void Maze::setExit(int x, int y) {
	exitX = x;
	exitY = y;
}


bool Maze::generateMaze()
{
	// Base case (i.e. when all cells have been visited)
	if (nbOfCellsVisited == mazeHeight * mazeWidth)
		return true;

	Stack neighbors;

	// Check for WEST neighbor
	if (stack->getTop()->x > 0)
	{
		int index = stack->getTop()->index - 1;
		if (maze[index].visited == false)
			neighbors.push(&maze[index]);
	}

	// Check for EAST neighbor
	if (stack->getTop()->x < mazeWidth - 1)
	{
		int index = stack->getTop()->index + 1;
		if (maze[index].visited == false)
			neighbors.push(&maze[index]);
	}

	// Check for NORTH neighbor
	if (stack->getTop()->y > 0)
	{
		int index = stack->getTop()->index - mazeWidth;
		if (maze[index].visited == false)
			neighbors.push(&maze[index]);
	}

	// Check for SOUTH neighbor
	if (stack->getTop()->y < mazeHeight - 1)
	{
		int index = stack->getTop()->index + mazeWidth;
		if (maze[index].visited == false)
			neighbors.push(&maze[index]);
	}

	// There is a neighbor which we haven't visited yet, so explore it
	if (!neighbors.isEmpty())
	{
		Cell* selectedNeighbor = neighbors.getRandom();
		selectedNeighbor->visited = true;

		// Relation: neighbor is EAST of current top
		if (stack->getTop()->x < selectedNeighbor->x)
		{
			stack->getTop()->east = true;
			selectedNeighbor->west = true;
		}

		// Relation: neighbor is WEST of current top
		if (stack->getTop()->x > selectedNeighbor->x)
		{
			stack->getTop()->west = true;
			selectedNeighbor->east = true;
		}

		// Relation: neighbor is SOUTH of current top
		if (stack->getTop()->y > selectedNeighbor->y)
		{
			stack->getTop()->north = true;
			selectedNeighbor->south = true;
		}

		// Relation: neighbor is SOUTH of current top
		if (stack->getTop()->y < selectedNeighbor->y)
		{
			stack->getTop()->south = true;
			selectedNeighbor->north = true;
		}

		// Adding the cell at the top of maze stack
		stack->push(selectedNeighbor);
		nbOfCellsVisited++;
	}

	// Stuck with no neighbors to visit so go backwards
	else
	{
		stack->pop();

		if (stack->isEmpty()) return false;
	}

	return generateMaze();
}
   

bool Maze::solveMaze()
{	
	// Initialization
	if (path->getTop() == nullptr) {
		int index = entranceY * mazeWidth + entranceX;
		maze[index].explored = true;
		maze[index].isOnPath = true;
		path->push(&maze[index]);
	}

	// Base Case
	if (path->getTop()->x == exitX && path->getTop()->y == exitY)
		return true;

	// Finding whether there is a free neighbor to explore
	Stack neighbors;
	if (path->getTop()->east) {
		int index = path->getTop()->index + 1;
		if (!maze[index].explored)
			neighbors.push(&maze[index]);
	}
	if (path->getTop()->west) {
		int index = path->getTop()->index - 1;
		if (!maze[index].explored)
			neighbors.push(&maze[index]);
	}

	if (path->getTop()->north) {
		int index = path->getTop()->index - mazeWidth;
		if (!maze[index].explored)
			neighbors.push(&maze[index]);
	}

	if (path->getTop()->south) {
		int index = path->getTop()->index + mazeWidth;
		if (!maze[index].explored)
			neighbors.push(&maze[index]);
	}

	// Selecting a neighbor to explore
	if (!neighbors.isEmpty())
	{
		Cell* selectedNeighbor = neighbors.getRandom();
		selectedNeighbor->isOnPath = true;
		selectedNeighbor->explored = true;
		path->push(selectedNeighbor);
	}
	// Dead end so go backwards
	else
	{
		path->getTop()->isOnPath = false;
		path->pop();

		if (path->isEmpty()) return false;
	}

	return solveMaze();
}
 

void printRow(int nb)
{
	for (int i = 0; i < nb; i++)
		cout << WALL;
	cout << endl;
}


void printNumbers(int max) {
	cout << " ";
	for (int i = 0; i < max; i++) {
		if (i < 9)
			cout << i << "   ";
		else
			cout << i << "  ";
	}
	cout << endl;
}


void Maze::printMaze(bool displayPath) const
{	
	printNumbers(mazeWidth);
	printRow(4 * mazeWidth);
	for (int i = 0; i < mazeHeight; i++) {
		cout << WALL;

		for (int j = 0; j < mazeWidth; j++) {
			if (maze[i * mazeWidth + j].east) {
				if (maze[i * mazeWidth + j].isOnPath && displayPath) {
					if (maze[i * mazeWidth + j + 1].isOnPath)
						cout << SOLUTION << SOLUTION << SOLUTION << SOLUTION;
					else
						cout << SOLUTION << SOLUTION << SPACE << SPACE;
				}
				else
					cout << SPACE << SPACE << SPACE << SPACE;
			}
			else {
				if (j == mazeWidth - 1) {
					if (maze[i * mazeWidth + j].isOnPath && displayPath)
						cout << SOLUTION << SOLUTION << WALL;
					else
						cout << SPACE << SPACE << WALL;
				}
				else {
					if (maze[i * mazeWidth + j].isOnPath && displayPath)
						cout << SOLUTION << SOLUTION << WALL << WALL;
					else
						cout << SPACE << SPACE << WALL << WALL;
				}

			}

		}
		cout << " " << i << endl;
		cout << WALL;

		for (int j = 0; j < mazeWidth; j++) {
			if (maze[i * mazeWidth + j].south) {
				if (j == mazeWidth - 1) {
					if (maze[i * mazeWidth + j].isOnPath && displayPath) {
						if (maze[i * mazeWidth + j + mazeWidth].isOnPath)
							cout << SOLUTION << SOLUTION << WALL;
						else
							cout << SPACE << SPACE << WALL;
					}
					else
						cout << SPACE << SPACE << WALL;
				}
				else {
					if (maze[i * mazeWidth + j].isOnPath && displayPath) {
						if (maze[i * mazeWidth + j + mazeWidth].isOnPath)
							cout << SOLUTION << SOLUTION << WALL << WALL;
						else
							cout << SPACE << SPACE << WALL << WALL;
					}
					else
						cout << SPACE << SPACE << WALL << WALL;
				}
			}
			else {
				if (j == mazeWidth - 1)
					cout << WALL << WALL << WALL;
				else
					cout << WALL << WALL << WALL << WALL;
			}
		}
		cout << endl;

	}
}




