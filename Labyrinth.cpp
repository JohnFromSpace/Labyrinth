##include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <stack>
#include <fstream>
#include "stdafx.h" 

using namespace std;

#define SIZE 1501 // 79 * 19 

// CELL STRUCTURE
struct Cell{
    bool visited;
    bool top_wall;
    bool bot_wall;
    bool left_wall;
    bool right_wall;
    char display;
};

// FUNCTION DECLARATIONS
void Initialize(Cell Level[][SIZE]);
void ClearScreen();
void Redraw(Cell Level[][SIZE]);
void GenerateMaze(Cell Level[][SIZE], int& posX, int& posY, int& goalX, int& goalY);
void SaveMaze(Cell Level[][SIZE]);

//Main Function
int main() {
    Cell Level[SIZE][SIZE];
    int posX = 0;
    int posY = 0;
    int goalX = 0;
    int goalY = 0;
    bool game_over = false;

    while (!game_over) {
        system("cls");
        Initialize(Level);
        Redraw(Level);
        GenerateMaze(Level, posX, posY, goalX, goalY);
        SaveMaze(Level);

        char input;
        cout << "Create a new Maze? (Y)/(N): ";
        cin >> input;

        if ((input != 'n') && (input != 'N') && (input != 'y') && (input != 'Y'))
            cout << "Invalid option" << endl;
        else if ((input == 'n') || (input == 'N')) {
            game_over = true;
            cout << "Good bye!" << endl;
        }
    }

    _getch();
    return 0;
}
