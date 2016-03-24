/**
 * File: random-sentence-generator.cpp
 * -----------------------------------
 * Presents a short program capable of reading in
 * context-free grammar files and generating arbitrary
 * sentences from them.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

#include "console.h"
#include "simpio.h"   // for getLine
#include "strlib.h"   // for toLowerCase, trim
#include "random.h"

static const string kGrammarsDirectory = "grammars/";
static const string kGrammarFileExtension = ".g";
static string getNormalizedFilename(string filename) {
    string normalizedFileName = kGrammarsDirectory + filename;
    if (!endsWith(normalizedFileName, kGrammarFileExtension))
        normalizedFileName += kGrammarFileExtension;
    return normalizedFileName;
}

static bool isValidGrammarFilename(string filename) {
    string normalizedFileName = getNormalizedFilename(filename);
    ifstream infile(normalizedFileName.c_str());
    return !infile.fail();
}

static string getFileName() {
    while (true) {
        string filename = trim(getLine("Name of grammar file? [<return> to quit]: "));
        if (filename.empty() || isValidGrammarFilename(filename)) return filename;
        cout << "Failed to open the grammar file named \"" << filename << "\". Please try again...." << endl;
    }
}

static void readGrammer(string filename, map<string, vector<string>>& nonTermMap)
{
    ifstream grammmFile(filename.c_str());

    string nonTerm;
   
    while (!grammmFile.eof())
    {
        getLine(grammmFile, nonTerm);
        // cout << nonTerm << endl;
        if (nonTerm.empty())
            continue;

        nonTermMap[nonTerm] = vector<string>();

        int num;
        grammmFile >> num >> ws;

        string def;
        for (int i=0; i < num; ++i) 
        {
            getLine(grammmFile, def);
            nonTermMap[nonTerm].push_back(def);
        }
    }
}

static string genSentence(map<string, vector<string>>& nonTermMap)
{
    string s = "<start>";

    int ntermStart, ntermEnd;

    while ((ntermStart = s.find('<')) != string::npos)
    {
        ntermEnd = s.find('>');

        string nterm = s.substr(ntermStart, ntermEnd - ntermStart + 1);
        int numTerm = nonTermMap[nterm].size();

        int choice = randomInteger(0, numTerm - 1);
        string replaceTerm = nonTermMap[nterm][choice];

        s.replace(ntermStart, ntermEnd - ntermStart + 1, replaceTerm);
    }

    return s;
}

int main() {
    while (true) {
        string filename = getFileName();
        if (filename.empty()) break;
        
        map<string, vector<string>> nonTermMap;
        readGrammer(getNormalizedFilename(filename), nonTermMap);

        for (int i=0; i < 3; ++i)
            cout << genSentence(nonTermMap) << endl << endl ;
    }
    
    cout << "Thanks for playing!" << endl;
    return 0;
}
