#include "RemainWords.h"
#include <map>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

void PositionChar::set_char(vector<int> pos, char c)
{
	for (int p: pos)
		this->chars[p] = c;
}

void RemainWords::guess(char c)
{
	map<vector<int>, vector<string>> pos_to_words;
	for (string& word : this->words)
	{
		vector<int> pos;
		int index = 0;

		for_each(word.begin(), word.end(), [&pos, &c, &index](char iter_c){
			if (iter_c == c)
			{
				pos.push_back(index);	
			}	
			++index;
		});

		if (pos_to_words.find(pos) == pos_to_words.end())
		{
			pos_to_words[pos] = vector<string>();
		}
		pos_to_words[pos].push_back(word);
	}

	for (auto& item : pos_to_words)
	{
		if (item.second.size() == 68)
		{
			for (auto& word: item.second)
			{
				cout << word << endl;
			}
		}
		
	}
}