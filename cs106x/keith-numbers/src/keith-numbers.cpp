/**
 * Provides the implementation of a program that counts up
 * from 1, but lists as many Keith numbers as it can find up to 10000.
 */
#include <iostream>
#include <fstream>
using namespace std;

#include "console.h"
#include "simpio.h"
#include "vector.h"

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

int main() {
	introduce();
	for (int n = 1; n < 10000; n++) {
		// replace the following with the logic needed to print
		// only Keith numbers, along with the sequence that
		// proves it's a Keith number (as described in the section handout)
		cout << n << endl;
	}
	
	cout << endl;
	cout << "That's all of them! " << endl;
	return 0;
}
