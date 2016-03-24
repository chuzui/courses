/**
 * Provides the implementation of a program that counts up
 * from 1, but lists as many Keith numbers as it can find up to 10000.
 */
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "console.h"
#include "simpio.h"
#include "error.h"
#include "strlib.h"

void introduce() {
	ifstream infile("keith-numbers.txt");
	if (!infile) error("Failed to open keith-numbers.txt.  Terminating.");
	
	while (true) {
		string line;
		getline(infile, line);
		if (infile.fail()) break;
		cout << line << endl;
	}
	
	cout << endl;
	getLine("Hit [Enter] to start: ");
	cout << endl;
}

bool isKeithNumber(vector<int>& seq, int n)
{
	string str = integerToString(n);

	int numSize = str.size();
	for (char c : str)
		seq.push_back(c - '0');

	while (seq.back() < n)
	{
		int next = 0;

		for (int i = seq.size() - numSize; i < seq.size(); ++i)
		{
			next += seq[i];
		}

		seq.push_back(next);
	}

	return seq.back() == n;
}

int main() {
	introduce();
	for (int n = 1; n < 10000; n++) {
		// replace the following with the logic needed to print
		// only Keith numbers, along with the sequence that
		// proves it's a Keith number (as described in the section handout)
		vector<int> seq;

		if (isKeithNumber(seq, n))
		{
			cout << n << ": [";
			for (int i = 0; i < seq.size() - 1; ++i) {
				cout << seq[i] << ", ";
			}
			cout << n <<  "]" << endl;
		}
	}
	
	cout << endl;
	cout << "That's all of them! " << endl;
	return 0;
}
