/**
 * File: dominosa.cpp
 * ------------------
 * This animates the brute-force discovery of a solution
 * to a 2 x n dominosa board.
 */

#include <iostream>
#include <cmath>
using namespace std;

#include "simpio.h"
#include "grid.h"
#include "random.h"
#include "dominosa-graphics.h"

static void welcome() {
	cout << "Here we'll illustrate the use of recursive backtracking to" << endl;
	cout << "discover a solution to various 2 x n Dominosa boards.  In some" << endl;
	cout << "cases there won't be any solutions, and in the cases where there are" << endl;
	cout << "multiple solutions, we'll just find one of them." << endl;
	cout << endl;
}

static int getIntegerInRange(string prompt, int low, int high) {
	while (true) {
		int response = getInteger(prompt);
		if (response == 0 || (response >= low && response <= high)) return response;
		cout << "Sorry, but I can't use that number." << endl;
	}
}

static void populateBoard(Grid<int>& board, int low, int high) {
	for (int row = 0; row < board.numRows(); row++) {
		for (int col = 0; col < board.numCols(); col++) {
			board[row][col] = randomInteger(low, high);
		}
	}
}

static bool canSolveBoard(DominosaDisplay& display, Grid<int>& board) {
    // replace this with your own solution, which will almost certainly be a wrapper function
	return false;
}

int main() {
	DominosaDisplay display;
	welcome();
	while (true) {
		int numColumns = getIntegerInRange("How many columns? [0 to exit]: ", 9, 25);
		if (numColumns == 0) break;
		Grid<int> board(2, numColumns);
		populateBoard(board, 1, ceil(2 * sqrt(numColumns)));
		display.drawBoard(board);
		if (canSolveBoard(display, board)) {
			cout << "The board can be solved, and one such solution is drawn above." << endl;
		} else {
			cout << "This board you see can't be solved." << endl;
		}
	}
	
	cout << "Okay, thanks for watching, and come back soon." << endl;
    cout << "Click the mouse anywhere in the window to exit." << endl;
	return 0;
}
