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

SortedStringSet::SortedStringSet(const Vector<int (*)(const string&, int)>& hashers) 
	: hasherFuncs(hashers)
{
	filterLength = initLength;
	filter = new bool[filterLength];

	for (int i = 0; i < filterLength; i++)
		filter[i] = false;

	trueNum = 0;
}

SortedStringSet::~SortedStringSet() 
{
	delete[] filter;
}

bool SortedStringSet::contains(const string& value) const {	
	for (auto& filterFunc : hasherFuncs)
	{
		int index = filterFunc(value, filterLength);
		if (!filter[index])
		{
			return false;
		}
	}

	return values.contains(value);
}

void SortedStringSet::add(const string& value) {
	updateFilter(value);
	values.add(value);

	if (trueNum > (filterLength - trueNum))
	{
		filterLength *= hasherFuncs.size();
		bool* newFilter = new bool[filterLength];

		delete filter;
		filter  = newFilter;

		for (auto& value : values)
		{
			updateFilter(value);
		}
	}
}

void SortedStringSet::updateFilter(const std::string& value)
{
	for (auto& filterFunc : hasherFuncs)
	{
		int index = filterFunc(value, filterLength);
		if (!filter[index])
		{
			filter[index] = true;
			++trueNum;
		}
	}
}

