#ifndef _xlup_file_read_
#define _xlup_file_read_

#include "grid.h"
#include "xlup-types.h"
#include <string>

/**
 * Populates the referenced Grid with the Roman numeral digits that make up
 * an XL-Up puzzle, and populates the referenced coord with the position where
 * the search should begin.
 */

void readMaze(Grid<char>& grid, coord& start, const std::string& filename);

#endif
