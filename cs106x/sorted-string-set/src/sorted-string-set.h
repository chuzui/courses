/**
 * File: sorted-string-set.h
 * -------------------------
 * Stores a collection of strings so that all are accessible in sorted
 * order.  The SortedStringSet layers over a Set<string>, except that it
 * includes Bloom Filter techniques so that a failing contains operation
 * runs in time that's proportional to the length of the string, and not the
 * size of the set.
 *
 * I give you a gratuitous wrapper around a Set<string>, and it's your
 * job to update the .h and the .cpp by installing a Bloom filter.
 * You should dynamically allocate your own memory instead of using a
 * Vector<bool>, the motivation being that you need the practice with
 * dynamic memory allocation and raw array.
 */

#include <string>
#include <vector>
#include "set.h"

class SortedStringSet {
public:
	SortedStringSet(const Vector<int (*)(const std::string&, int)>& hashers);
	~SortedStringSet();
    int size() const { return values.size(); }
	bool contains(const std::string& value) const;
	void add(const std::string& value);
    
private:
	static const int initLength = 1001;

    Set<std::string> values;
    Vector<int (*)(const std::string&, int)> hasherFuncs;
    bool* filter;

    int filterLength;
    int trueNum;

    void updateFilter(const std::string& value);
};
