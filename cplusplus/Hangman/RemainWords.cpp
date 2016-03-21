#include "RemainWords.h"
#include <map>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
using namespace std;

void PositionChar::set_char(vector<int> pos, char c)
{
	for (int p: pos)
		chars[p] = c;
}


ostream& operator<<(ostream& os, const PositionChar& item)
{
	copy(item.chars.begin(), item.chars.end(), ostream_iterator<char>(os));
	return os;
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


	vector<int> max_pos;
	for (auto& item : pos_to_words)
	{
		if (item.second.size() > pos_to_words[max_pos].size())
		{
			max_pos = item.first;
		}
	}

	// copy(max_pos.begin(), max_pos.end(), ostream_iterator<int>(cout));

	words = pos_to_words[max_pos];
	ps.set_char(max_pos, c);
}

ostream& operator<<(ostream& os, const RemainWords& item)
{
	os << item.ps << " " << item.words.size();
	return os;
}