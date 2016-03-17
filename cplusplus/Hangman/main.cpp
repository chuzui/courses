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

	int length = 8;

	RemainWords rw(length_to_words[length]);

	rw.guess('e');


	dict_file.close();
}