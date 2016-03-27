/**
 * File: xlup-types.h
 * ------------------
 * Defines the coord type (and the relevant operator< function) 
 * and a short utility function that allow us to compute 
 * coordinate neighbors very easily.
 *
 * Implementations are inlined so a companion .cpp files isn't
 * necessary (though in general, you shouldn't rely on the inline
 * keyword for all but the shortest and most obvious of implementations.)
 */

#ifndef _xlup_types_
#define _xlup_types_

#include "direction.h" // for enumerated Direction type

struct coord {
	int row;
	int col;
};

inline bool operator<(const coord& one, const coord& two) {
    if (one.row < two.row) return true;
    if (two.row < one.row) return false;
    return one.col < two.col;
}

inline coord neighboringCoord(const coord& c, Direction dir) {
	coord next = c;
	switch (dir) {
		case NORTH: next.row--; break;
		case EAST: next.col++; break;
		case SOUTH: next.row++; break;
		case WEST: next.col--; break;
	}
	
	return next;
}

#endif
