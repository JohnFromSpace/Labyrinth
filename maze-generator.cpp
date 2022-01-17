#include "maze.cpp"
#include <time.h>
#include <fstream>

int main() {

	srand(clock());

	int sizeX, sizeY;
	cout << "Enter the dimensions of the maze (width & height): ";
	cin >> sizeX >> sizeY;
	cout << endl;

	Maze maze(sizeX, sizeY);
	maze.generateMaze();
	maze.printMaze(false);

	int entranceX, entranceY, exitX, exitY;
	cout << endl << "Enter the entrance coordinates (X: 0-" << sizeX - 1
		<< " & Y: 0-" << sizeY - 1 << "): ";
	cin >> entranceX >> entranceY;
	maze.setEntrance(entranceX, entranceY);

	cout << "Enter the exit coordinates (X: 0-" << sizeX - 1
		<< " & Y: 0-" << sizeY - 1 << "): ";
	cin >> exitX >> exitY;
	maze.setExit(exitX, exitY);

	cout << endl;

	maze.solveMaze();
	maze.printMaze(true);

	return 0;
}
/*
// SAVE MAZE
void SaveMaze(int sizeX, int sizeY, Maze maze) {
	ofstream output;
	char file[20];
	char input;

	cout << endl << "Save Maze? (Y)/(N): ";
	cin >> input;

	if ((input == 'y') || (input == 'Y')) {
		cout << endl << "Save as: ";
		cin >> file;

		output.open(file);

		for (int i = 0; i < sizeX; i++) {
			output << endl;
			for (int j = 0; j < sizeY; j++) {
				output << level[i][j].display << " ";
			}
		}

		cout << "Maze has been saved to" << "\"" << file << "\"" << endl;
		output.close();
	}

}
*/