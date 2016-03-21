#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "RemainWords.h"
using namespace std;

int main()
{
	ifstream dict_file;
	dict_file.open("dictionary.txt");

	map<int, vector<string>> length_to_words;
	string word;

	while(dict_file >> word)
	{
		length_to_words[word.size()].push_back(word);
	}

	dict_file.close();

	int length = 8;

	cout << length_to_words[length].size() << endl;

	RemainWords rw(length_to_words[length], length);


	char guess_c;

	while (cin >> guess_c)
	{
		rw.guess(guess_c);
		cout << rw << endl;
	}

	
	
}