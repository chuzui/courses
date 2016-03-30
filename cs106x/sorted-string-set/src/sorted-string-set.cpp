/**
 * File: sorted-string-set.cpp
 * ---------------------------
 * Presents the implementation of the the SortedStringSet, which
 * encapsulates a Set<string>, but inserts a Bloom filter in between
 * the client and the Set<string> so that failing searchs return much,
 * much more quickly.
 *
 * I give you a gratuitous wrapper around a Set<string>, and it's your
 * job to update the .h and the .cpp by installing a Bloom filter.
 * You should dynamically allocate your own memory instead of using a 
 * Vector<bool>, the motivation being that you need the practice with
 * dynamic memory allocation and raw array.
 */

#include "sorted-string-set.h"
using namespace std;

SortedStringSet::SortedStringSet(const Vector<int (*)(const string&, int)>& hashers) {}
SortedStringSet::~SortedStringSet() {}

bool SortedStringSet::contains(const string& value) const {
	return values.contains(value);
}

void SortedStringSet::add(const string& value) {
	values.add(value);
}

