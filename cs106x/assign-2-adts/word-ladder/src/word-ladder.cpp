/**
 * File: word-ladder.cpp
 * ---------------------
 * Implements a program to find word ladders connecting pairs of words.
 */

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
using namespace std;

#include "console.h"
#include "lexicon.h"
#include "strlib.h"
#include "simpio.h"

static string getWord(Lexicon& english, string prompt) {
    while (true) {
        string response = trim(toLowerCase(getLine(prompt)));
        if (response.empty() || english.contains(response)) return response;
        cout << "Your response needs to be an English word, so please try again." << endl;
    }
}

static void generateLadder(Lexicon& english, string start, string end) {
    queue<string> q;
    q.push(start);

    map<string, vector<string>> wordToLadder;
    wordToLadder[start] = vector<string>();

    int word_size = start.size();
    while (!q.empty())
    {
        string word = q.front();
        q.pop();
        vector<string> ladder = wordToLadder[word];

        if (word == end)
        {
            for (auto& w: ladder)
                cout << w << "->";

            cout << word << endl;
            break;
        }

        for (int i = 0; i < word_size; ++i)
            for (char c = 'a'; c <= 'z'; ++c)
            {
                string new_word = word;
                new_word[i] = c;
                
                if (english.contains(new_word) &&
                    new_word != word           && 
                    wordToLadder.find(new_word) == wordToLadder.end())
                {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    q.push(new_word);
                    wordToLadder[new_word] = new_ladder;
                }
           
            }

    }
}

static const string kEnglishLanguageDatafile = "EnglishWords.dat";
static void playWordLadder() {
    Lexicon english(kEnglishLanguageDatafile);
    while (true) {
        string start = getWord(english, "Please enter the source word [return to quit]: ");
        if (start.empty()) break;
        string end = getWord(english, "Please enter the destination word [return to quit]: ");
        if (end.empty()) break;
        generateLadder(english, start, end);
    }
}

int main() {
    cout << "Welcome to the CS106 word ladder application!" << endl << endl;
    playWordLadder();
    cout << "Thanks for playing!" << endl;
    return 0;
}
