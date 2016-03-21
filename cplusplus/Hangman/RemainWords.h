#ifndef _REMAINWORDS_H
#define _REMAINWORDS_H

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class PositionChar{
public:
	PositionChar(int n):chars(n, '_'){}
	void set_char(vector<int> pos, char c);
	friend ostream& operator<<(ostream& os, const PositionChar& item);
private:
	vector<char> chars;
};

ostream& operator<<(ostream& os, const PositionChar& item);

class RemainWords{
public:
	RemainWords(vector<string> words, int n):words(words), ps(n){};
	void guess(char c);
	vector<string>& get_words() {return this->words;};
	friend ostream& operator<<(ostream& os, const RemainWords& item);
private:
	vector<string> words;
	PositionChar ps;
};

ostream& operator<<(ostream& os, const RemainWords& item);

#endif