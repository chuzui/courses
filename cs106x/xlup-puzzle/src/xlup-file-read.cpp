/**
 * File: xlup-file-read.cpp
 * ------------------------
 * Defines a function that knows how to read an XL-Up
 * maze file from a file.  We put this particular function
 * in a separate module just to get it out of main module.
 */

#include <fstream>
using namespace std;

#include "xlup-file-read.h"

void readMaze(Grid<char>& grid, coord& start, const string& filename) {
    ifstream infile(filename.c_str());
    if (!infile) {
        cout << "File named \"" + filename + "\" could not be read." << endl;
        exit(1);
    }

	int numRows, numCols;
	infile >> numCols >> numRows;
	grid.resize(numRows, numCols);

    string line;
    getline(infile, line); // read rest of first line
	
	infile >> start.row >> start.col;
    getline(infile, line); // read rest of second line
    
	for (int row = 0; row < grid.numRows(); row++) {
		getline(infile, line);
		for (int col = 0; col < grid.numCols(); col++) {
			grid[row][col] = line[col];
		}
	}
}


