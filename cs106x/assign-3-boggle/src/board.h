#ifndef _BOARD_H
#define _BOARD_H

#include <string>
using namespace std;

class Board
{
public:
	Board (int n): dimension(n), letters(n * n, ' '), letterUsed(n * n, false) {}
	Board (int n, string initLetters): dimension(n), letters(initLetters), letterUsed(n * n, false) {}
	char get_letter(int row, int col) const { return letters[row * dimension + col]; }
	void set_letter(int row, int col, char c) { letters[row * dimension + col] = c;}

	void set_used(int row, int col) { letterUsed[row * dimension + col] = true; }
	void set_unused(int row, int col) { letterUsed[row * dimension + col] = false; }
	bool is_used(int row, int col) const { return letterUsed[row * dimension + col]; }
	void reset_used ()
	{
		for (auto&& isUsed : letterUsed)
			isUsed = false;
	}

	int get_dim() const { return dimension; }
private:
	int dimension;
	string letters;
	vector<bool> letterUsed;
};

#endif