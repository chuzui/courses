/**
 * File: dominosa.cpp
 * ------------------
 * This animates the brute-force discovery of a solution
 * to a 2 x n dominosa board.
 */

#include <iostream>
#include <cmath>
#include <set>
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

struct pairNum
{
	int one;
	int two;

	pairNum(int first, int second)
	{
		if (first < second)
		{
			one = first;
			two = second;
		}
		else
		{
			one = second;
			two = first;
		}
	}
};

inline bool operator<(const pairNum& one, const pairNum& two) {
    if (one.one != two.one)
        return one.one < two.one;
    else
        return one.two < two.two;
}

static void populateBoard(Grid<int>& board, int low, int high) {
	for (int row = 0; row < board.numRows(); row++) {
		for (int col = 0; col < board.numCols(); col++) {
			board[row][col] = randomInteger(low, high);
		}
	}
}

static bool canSolveBoard(DominosaDisplay& display,
	 					  Grid<int>& board, 
	 					  set<pairNum>& pairNums, 
	 					  int currCol
	 					  )
{
	int col = board.width();

	if (currCol == col) return true;
	if (currCol < col - 1)
	{
		pairNum p1(board[0][currCol], board[0][currCol+1]);
		pairNum p2(board[1][currCol], board[1][currCol+1]);
		if (pairNums.find(p1) == pairNums.end() && pairNums.find(p2) == pairNums.end())
		{
			pairNums.insert(p1);
			pairNums.insert(p2);

			coord c11{0, currCol}, c12{0, currCol+1};
			coord c21{1, currCol}, c22{1, currCol+1};
			display.vetoProvisionalPairing(c11, c12);
			display.vetoProvisionalPairing(c21, c22);

			if (canSolveBoard(display, board, pairNums, currCol + 2))
			{
				return true;
			}

			display.eraseProvisionalPairing(c11, c12);
			display.eraseProvisionalPairing(c21, c22);

			pairNums.erase(p1);
			pairNums.erase(p2);
		}
	}
	

	pairNum p(board[0][currCol], board[1][currCol]);
	if (pairNums.find(p) == pairNums.end())
	{
		pairNums.insert(p);

		coord c11{0, currCol}, c12{1, currCol};
		display.vetoProvisionalPairing(c11, c12);

		if (canSolveBoard(display, board, pairNums, currCol + 1))
		{
			return true;
		}

		display.eraseProvisionalPairing(c11, c12);

		pairNums.erase(p);
	}

	return false;
}

static bool canSolveBoard(DominosaDisplay& display, Grid<int>& board) {
    // replace this with your own solution, which will almost certainly be a wrapper function

    set<pairNum> pairNums;

    bool isSolved = canSolveBoard(display, board, pairNums, 0);

    // if (isSolved)	
    // {
    // 	for (auto& p: pairNums)
    // 		cout << p.one << " " << p.two << endl;

    // 	cout << pairNums.size() << endl;
    // }
    return isSolved;
    
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
