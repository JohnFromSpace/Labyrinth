#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "assert.h"
using namespace std;

struct Cell
{
	int x;
	int y;
	int index;
	bool visited; // For maze generation
	bool explored; // For maze solving
	bool isOnPath;

	bool north;
	bool south;
	bool east;
	bool west;

	Cell()
	{
		x = 0;
		y = 0;
		index = 0;
		visited = false;
		explored = false;
		isOnPath = false;
		north = false;
		south = false;
		east = false;
		west = false;
	}
};


struct LinkedCell
{
	Cell* data;
	LinkedCell* next;

	LinkedCell() {
		data = nullptr;
		next = nullptr;
	};
};


class Stack
{
private:
	LinkedCell* top;

public:
	Stack();
	~Stack();

	void push(Cell* cell);
	void pop();

	bool isEmpty() const;
	int getLength() const;

	Cell* getTop() const;
	Cell* getRandom() const;
};


class Maze
{
private:
	int mazeWidth;
	int mazeHeight;

	int entranceX;
	int entranceY;
	int exitX;
	int exitY;

	Cell* maze;
	Stack* stack;
	Stack* path;
	int nbOfCellsVisited;

public:
	Maze(int width, int height);
	~Maze();

	bool generateMaze();
	bool solveMaze();
	void setEntrance(int x, int y);
	void setExit(int x, int y);

	void printMaze(bool displayPath) const;



};

//Implemented class derivative of the streambuf class
class StreambufDoubler : public std::streambuf {
public:
	StreambufDoubler(std::streambuf* buf1, std::streambuf* buf2) :
		_buf1(buf1), _buf2(buf2), _buffer(128)
	{
		assert(_buf1 && _buf2);

		setg(0, 0, 0);
		setp(_buffer.data(), _buffer.data(), _buffer.data() + _buffer.size());
	}

	~StreambufDoubler() {
		sync();
	}

	void imbue(const std::locale& loc) {
		_buf1->pubimbue(loc);
		_buf2->pubimbue(loc);
	}

	std::streampos seekpos(std::streampos sp, std::ios_base::openmode which) {
		return seekoff(sp, std::ios_base::cur, which);
	}

	std::streampos seekoff(std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which) {
		if (which | std::ios_base::in)
			throw(std::runtime_error("Can't use this class to read data"));

		_buf1->pubseekoff(off, way, which);
		return _buf2->pubseekoff(off, way, which);
	}

	int overflow(int c) {
		int retValue = sync() ? EOF : 0;
		sputc(c);
		return retValue;
	}

	int sync() {
		_buf1->sputn(pbase(), pptr() - pbase());
		_buf2->sputn(pbase(), pptr() - pbase());
		setp(_buffer.data(), _buffer.data(), _buffer.data() + _buffer.size());
		return _buf1->pubsync() | _buf2->pubsync();
	}

private:
	std::streambuf* _buf1;
	std::streambuf* _buf2;

	std::vector<char>   _buffer;
};
