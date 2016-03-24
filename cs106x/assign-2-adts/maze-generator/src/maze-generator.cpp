/**
 * File: maze-generator.cpp
 * ------------------------
 * Presents an adaptation of Kruskal's algorithm to generate mazes.
 */

#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

#include "console.h"
#include "simpio.h"
#include "maze-graphics.h"
#include "maze-types.h"

static int getMazeDimension(string prompt,
                            int minDimension = 7, int maxDimension = 50) {
	while (true) {
		int response = getInteger(prompt);
		if (response == 0) return response;
        if (response >= minDimension && response <= maxDimension) return response;
		cout << "Please enter a number between "
			 << minDimension << " and " 
		     << maxDimension << ", inclusive." << endl;
	}
}

static void genCellsAndWalls(vector<wall>& walls, vector<cell>& cells, int dimension)
{
	for (int i = 0; i < dimension; ++i)
			for (int j = 0; j < dimension; ++j)
			{
				cell c = {i, j};
				cells.push_back(c);
			}

	for (int i = 0; i < dimension; ++i)
		for (int j = 0; j < dimension - 1; ++j)
		{
			int index = i * dimension + j;
			wall w = {cells[index], cells[index+1]};
			walls.push_back(w);
		}

	for (int i = 0; i < dimension - 1; ++i)
		for (int j = 0; j < dimension; ++j)
		{
			int index = i * dimension + j;
			wall w = {cells[index], cells[index+dimension]};
			walls.push_back(w);
		}
}

static bool isSameChamber(const wall& w, vector<set<cell>>& chambers, int& wallOne, int& wallTwo)
{
	for (int i = 0; i < chambers.size(); ++i)
	{
		if (chambers[i].find(w.one) != chambers[i].end())
			wallOne = i;

		if (chambers[i].find(w.two) != chambers[i].end())
			wallTwo = i;
	}
	
	return wallOne == wallTwo;
}

int main() {
	while (true) {
		int dimension = getMazeDimension("What should the dimension of your maze be [0 to exit]? ");
		if (dimension == 0) break;

		
		vector<cell> cells;
		vector<wall> walls;
		genCellsAndWalls(walls, cells, dimension);

		MazeGeneratorView mgv;
		mgv.setDimension(dimension);
		mgv.drawBorder();

		for(auto& w: walls)
		{
			mgv.drawWall(w);
		}

		random_shuffle(walls.begin(), walls.end());

		int removed_num = 0;
		int removed_total = dimension * dimension - 1;
		vector<set<cell>> chambers;

		for (auto& c: cells)
		{
			set<cell> chamber;
			chamber.insert(c);
			chambers.push_back(chamber);
		}

		for (auto& w: walls)
		{
			int wallOne = 0;
			int wallTwo = 0;
			if (!isSameChamber(w, chambers, wallOne, wallTwo))
			{
				mgv.removeWall(w);
				
				chambers[wallOne].insert(chambers[wallTwo].begin(), chambers[wallTwo].end());
				chambers.erase(chambers.begin() + wallTwo);

				++removed_num;
				::pause(100);

				if (removed_num == removed_total)
					break;
			}
		}

		// for(auto& w: walls)
		// {
		// 	mgv.re(w);
		// }
		
		int i;
		cin >> i;
		// cout << "This is where I'd animate the construction of a maze of dimension " << dimension << "." << endl;
	}

	return 0;
}
