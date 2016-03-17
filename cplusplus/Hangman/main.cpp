#include <iostream>
#include <fstream>
#include <map>
#include <vector>
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

	for (auto& item : length_to_words)
	{
		cout << item.first << " " << item.second.size() << endl;
	}

	dict_file.close();
}