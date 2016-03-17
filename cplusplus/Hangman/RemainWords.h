#ifndef _REMAINWORDS_H
#define _REMAINWORDS_H

#include <vector>
#include <iostream>
using namespace std;

class PositionChar{
public:
	PositionChar(int n):chars(n, '_'){};
	void set_char(vector<int> pos, char c);
private:
	vector<char> chars;

};

class RemainWords{
public:
	RemainWords(vector<string> words):words(words){};
	void guess(char c);
	vector<string>& get_words() {return this->words;};

private:
	vector<string> words;
};

#endif