#include "maze.cpp"
#include <time.h>
#include <fstream>
#include "stdafx.h"

int main() {

	rlutil::setColor(15);//Sets color to white

	std::ofstream myMaze("Maze.txt");
	StreambufDoubler doubler(std::cout.rdbuf(), myMaze.rdbuf());
	std::cout.rdbuf(&doubler);

	srand(clock());

	int sizeX, sizeY;
	cout << "Dimensions of the maze (width x height): \n" 
		<< "Quick note: For higher values for 'width' the maze will not appear as it should on the cmd" 
		<< "(ex.: 80 x 20).\n";
	
	cout << "Enter the dimensions of the maze (width & height):\t";

	cin >> sizeX >> sizeY;
	
	cout << "\n\n";

	cout << "A maze with dimensions: " <<
		"width = " << sizeX << " and height = " << sizeY << endl;

	Maze maze(sizeX, sizeY);
	maze.generateMaze();
	maze.printMaze(false);

	cout << "\n\n";
	cout << "THE MAZE WAS SAVED IN A .TXT FILE.\nEven if the maze is 80 x 20 you should not have problem" 
		<<" with zooming out on Notepad.\n\n";
	
	myMaze.close();


	int entranceX, entranceY, exitX, exitY;
	cout << endl << "Enter the entrance coordinates (X: 0-" << sizeX - 1
		<< " & Y: 0-" << sizeY - 1 << "): ";
	cin >> entranceX >> entranceY;
	maze.setEntrance(entranceX, entranceY);

	cout << "Enter the exit coordinates (X: 0-" << sizeX - 1
		<< " & Y: 0-" << sizeY - 1 << "): ";
	cin >> exitX >> exitY;
	maze.setExit(exitX, exitY);

	cout << "\n\n";

	myMaze.open("Maze.txt", std::ios_base::app); // append instead of overwrite

	myMaze << "Starting point: (" << entranceX << ", " << entranceY << ")\n";
	myMaze << "Exit point: (" << exitX << ", " << exitY << ")\n\n\n";

	myMaze.close();

	myMaze << "Starting point: (" << entranceX << ", " << entranceY << ")\n";
	myMaze << "Exit point: (" << exitX << ", " << exitY << ")\n\n\n";

	cout << "Do you want the program to solve it for you? ('Y', 'y', 'N' or 'n')\n";

	char input;
	cin >> input;

	if (input == 'Y' || input == 'y') {

		rlutil::setColor(8);//Sets color to dark grey

		std::ofstream solutionFile("Solution.txt");
		StreambufDoubler doublerS(std::cout.rdbuf(), solutionFile.rdbuf());
		std::cout.rdbuf(&doublerS);

		maze.solveMaze();
		maze.printMaze(true);

		solutionFile.close();

		rlutil::setColor(15);//Sets color back to normal

		solutionFile.close();

		cout << "\n\n";
		cout << "THE SOLUTION WAS SAVED IN A .TXT FILE.\n\n";
	}

	return 0;
}
