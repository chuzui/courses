/**
 * File: xlup-puzzle.cpp
 * ---------------------
 * Provides the main module for the application that illustrates
 * how XL-Up puzzles can be solved.
 */

#include <iostream>
using namespace std;

#include "grid.h"
#include "stack.h"
#include "random.h"
#include "gevents.h"
#include "xlup-types.h"
#include "xlup-file-read.h"
#include "xlup-graphics.h"

const static string kPuzzleFileName = "xlup-puzzle.txt";
const static string kXLUpWord =
" I II III IV V VI VII VIII IX X"
" XI XII XIII XIV XV XVI XVII"
" XVIII XIX XX XXI XXII XXIII XXIV XXV XXVI XXVII XXVIII XXIX XXX"
" XXXI XXXII XXXIII XXXIV XXXV XXXVI XXXVII XXXVIII XXXIX XL ";
const static string kLUpWord = kXLUpWord + "XLI XLII XLIII XLIV XLV XLVI XLVII XLVIII XLIX L ";
const static int kDelay = 1000;

static bool solutionExists(XLUpDisplay& /* display */, const Grid<char>& /* grid */,
                           const string& /* numbers */, const coord& /* curr */, Stack<coord>& /* path */) {
    // replace with your own implementation, which will almost certainly involve a
    // wrapper function of some sort. (I've commented out the variable names above to suppress
    // compiler warnings about unused variables names.  Just reintroduce them.)
	return false;
}

int main() {
    XLUpDisplay display;
	cout << "Welcome to the XLUp puzzle solver." << endl;
	Grid<char> grid;
	coord start;
	readMaze(grid, start, kPuzzleFileName);
    display.drawBoard(grid);
    cout << "Click the mouse anywhere to begin!" << flush;
    waitForClick();
    cout << endl;
	Stack<coord> path;
	if (solutionExists(display, grid, kXLUpWord, start, path)) {
		cout << "A solution was found.  Watch!" << endl << endl;
        pause(kDelay);
        display.drawBoard(grid); // redraw board
		while (!path.isEmpty()) {
            coord move = path.pop();
			display.officiallyMove(move);
            cout << grid[move.row][move.col] << flush;
		}
        cout << endl;
	} else {
		cout << "No solution could be found." << endl;
	}
	
	return 0;
}
