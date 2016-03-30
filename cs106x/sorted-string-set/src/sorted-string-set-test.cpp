/**
 * File: sorted-string-set-test.cpp
 * -------------------------------
 * Exercises the SortedStringSet class exported by sorted-string-set.h.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "vector.h"
#include "lexicon.h"
#include "sorted-string-set.h"
using namespace std;

static int WeakHash(const string& /* value */, int /* modulo */) {
	return 0;
}

static int SimpleForwardHash(const string& value, int modulo) {
    const int kBase = 79;
    const int kMultiplier = 397;
	unsigned long hashcode = kBase;
    for (size_t i = 0; i < value.size(); i++) {
		hashcode = kMultiplier * hashcode + value[i];
	}
	
	return hashcode % modulo;
}

static int SimpleBackwardHash(const string& value, int modulo) {
    const int kBase = 113;
    const int kMultiplier = 259;
	unsigned long hashcode = kBase;
    for (size_t i = value.size() - 1; i <= value.size(); i--) {
		hashcode = kMultiplier * hashcode + value[i];
	}
	
	return hashcode % modulo;
}

static int StrongHash(const string& value, int modulo) {
	const long kMultiplier = -1664117991L;
	unsigned long hashcode = 0;
    for (size_t i = 0; i < value.size(); i++) {
		hashcode = hashcode * kMultiplier + value[i]; 
	}
	
	return int(hashcode & (unsigned(-1) >> 1)) % modulo;
}

static Vector<int (*)(const string&, int)> getHashFunctions() {
	Vector<int (*)(const string&, int)> hashers;
    hashers += WeakHash, SimpleForwardHash, SimpleBackwardHash, StrongHash;
	return hashers;
}

static inline void recordInsertion(int numWords) {
    if (numWords % 10000 == 0) cout << "." << flush;
    if (numWords % 400000 == 0) cout << endl;
}

int main() {
	SortedStringSet words(getHashFunctions());
    Lexicon english("dictionary.txt");

    cout << "Just created SortedStringSet." << endl;
    cout << "Inserting lots and lots of strings [each dot is 10000 strings]." << endl;
    for (const string& word: english) {
		words.add(word);
        recordInsertion(words.size());
		for (char ch = 'a'; ch <= 'z'; ch++) {
            string str = ch + word + ch;
			words.add(str);
            recordInsertion(words.size());
		}
	}

    cout << " [" << words.size() << " words in all]" << endl << endl;

    cout << "Confirming all words we expect to be present are present [wait for it... " << flush;
    for (const string& word: english) {
        if (!words.contains(word))
            error("SortedStringSet didn't contain \"" + word + "\" when it should have.");
        for (char ch = 'a'; ch <= 'z'; ch++) {
            string str = ch + word + ch;
            if (!words.contains(str)) {
                error("SortedStringSet didn't contain \"" + str + "\" when it should have.");
            }
            if (words.contains(word + string(10, ch)))
                error("SortedStringSet contained a string that shouldn't be present.");
        }
	}
    
    cout << "and everything checks out!!]" << endl;
    return 0;
}
