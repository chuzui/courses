/**
 * File: make-change.cpp
 * ---------------------
 * This program recursively computes the numbers of ways one
 * can make change for any given amount of money when given an
 * unlimited number of denominations of coins.
 */

#include <iostream>
using namespace std;

#include "console.h"
#include "vector.h"

static int countWaysToMakeChange(const Vector<int>& denominations, int amount) {
    // replace with your own implementation, which will almost
    // certainly benefit from being implemented as a wrapper around the function
    // call that actually does the recursion.
    return 0;
}

int main() {
    Vector<int> denominations;
    denominations += 25, 10, 5;
    cout << "Number of ways to make change for a dollar using " << denominations << ": "
         << countWaysToMakeChange(denominations, 100) << endl;
    denominations += 1;
    cout << "Number of ways to make change for a dollar using " << denominations << ": "
         << countWaysToMakeChange(denominations, 100) << endl;
    return 0;
}
