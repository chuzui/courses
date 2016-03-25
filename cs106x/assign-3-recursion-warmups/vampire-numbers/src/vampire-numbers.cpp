/**
 * File: vampire-numbers.cpp
 * -------------------------
 * Provides a program that repeatedly prompts the user for positive
 * numbers with an even number of digits and informs them
 * whether the number is a Vampire number or not.
 */

#include <string>    // for string
#include <iostream>  // for cout, endl
#include <algorithm>
#include <map>
using namespace std;

#include "console.h" 
#include "simpio.h" // for getInteger
#include "strlib.h" // for stringToInteger, integerToString

long long getLongLong(string prompt, string reprompt="") {
    if (reprompt == "") {
        reprompt = "Illegal integer format. Try again.";
    }
    // appendSpace(prompt);
    long long value;
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        if (autograder::getConsoleEchoUserInput()) {
            cout << line << endl;
        }
        istringstream stream(line);
        stream >> value >> ws;
        if (!stream.fail() && stream.eof()) break;
        cout << reprompt << endl;
        if (prompt == "") prompt = "Enter an integer: ";
    }
    return value;
}

string longLongToString(long long n) {
    ostringstream stream;
    stream << n;
    return stream.str();
}

static long long getPossibleVampireNumber() {
    while (true) {
        long long response = getLongLong("Enter a positive integer [or 0 to quit]: ");
        // long long response = 999999174936152983639999LL;
        if (response >= 0) return response;
        cout << "Ah, sorry.  I need a nonnegative response.  Try again... " << endl;
    }
}

static bool isVampireNumber(long long number, long long tFirst, map<char, int>& remain, int remain_num ,long long& first, long long& second) {
    if (remain_num == 0) return false;  

    if (tFirst != 0 && (number % tFirst) == 0)
    {
        long long tSecond = number / tFirst;
        string sSecond = longLongToString(tSecond);

        map<char, int> mapSecond;
        for (char c: sSecond)
            mapSecond[c] += 1;

        bool isSame = true;
        for (char c = '0'; c <= '9'; ++c)
        {
            if (remain[c] != mapSecond[c])
            {
                isSame = false;
                break;
            }
        }

        if (isSame)
        {
            first = tFirst;
            second = tSecond;
            return true;
        }
    }

    for (char c = '0'; c <= '9'; ++c)
    {
        if (tFirst == 0 && c == '0')
            continue;

        if (remain[c] > 0)
        {
            long long nextFirst = tFirst * 10 + c - '0';
            
            --remain[c];

            if (isVampireNumber(number, nextFirst, remain, remain_num - 1, first, second))
                return true;

            ++remain[c];
        }
    }
    return false;
}

static bool isVampireNumber(long long number, long long& first, long long& second) {
    // replace this line with your own implementation.  You will want
    // to implement this as a wrapper around a second version of isVampireNumber
    // that does the actual recursion.
    map<char, int> remain;
    for (char c: longLongToString(number))
        remain[c] += 1;

    return isVampireNumber(number, 0, remain, longLongToString(number).size(), first, second);
}

int main() {
    cout << "Here's a program that tells you whether or not a "
         << "number you enter is Vampire." << endl << endl;
    while (true) {
        long long number = getPossibleVampireNumber();
        if (number == 0) break;
        cout << number << endl; 
        long long first, second;
        if (isVampireNumber(number, first, second)) {
            cout << "Woo! " << number << " is a Vampire number, and "
                 << first << " and " << second << " are its fangs." << endl << endl;
        } else {
            cout << "Nope! The number " << number << " isn't Vampire." << endl << endl;
        }
    }
    cout << endl;
    cout << "All done!" << endl;
    return 0;
}
