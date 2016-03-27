/**
 * File: xlup-graphics.h
 * ---------------------
 * Exports the graphics package that helps animate the process
 * by which recursive backtracking can be used to search for a
 * solution to the XL-Up puzzle.
 */

#include <string>
#include "grid.h"
#include "vector.h"
#include "gwindow.h"
#include "xlup-types.h"

class XLUpDisplay : private GWindow {
public:

/**
 * Constructor: XLUpDisplay
 * ------------------------
 * Defaultly constructs the XLUpDisplay without committing to a particular board.
 */
    XLUpDisplay();
    
/**
 * Method: drawBoard
 * -----------------
 * Updates the XLUpDisplay to draw the grid of characters ('X's, 'I's, ' 's, etc)
 * to the screen, leaving the characters displayed for the lifetime of the XLUpDisplay.
 */
    void drawBoard(const Grid<char>& grid);

/**
 * Method: officiallyMove
 * ----------------------
 * Highlights the identified coordinate in dark green (allowing
 * the most recent official move to fade to a lighter green).
 */
    void officiallyMove(const coord& move);

/**
 * Method: provisonallyMove
 * ------------------------
 * Highlights the identified coordinate in dark blue (letting
 * previous provisional moves fade to a lighter blue until they
 * are explicityly erased).
 */
    void provisonallyMove(const coord& move);

/**
 * Method: vetoProvisionalMove
 * ---------------------------
 * Highlights the identified coordinate (assumed to have been provisionally
 * occupied) in angry red. :)
 */
    void vetoProvisionalMove(const coord& move);

/**
 * Method: eraseProvisionalMove
 * ---------------------------
 * Negates the effects of the most recent provisional move.
 */
	void eraseProvisionalMove(const coord& move);

private:
	void drawMove(const coord& move, const std::string& color);
	void drawBox(double llx, double lly, double width, double height, const std::string& color);
	void drawFilledBox(double llx, double lly, double width, double height,
                       const std::string& fill, const std::string& border);
	void drawCenteredDigit(char digit, double cx, double cy, const std::string& color);
	void redrawProvisionalMoves();

    Grid<char> grid;
    double cellDimension;
    double boardulx;
    double boarduly;
	Vector<coord> activeProvisionalMoves;
    Vector<coord> shadow;
};
