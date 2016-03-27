/**
 * File: xlup-graphics.cpp
 * -----------------------
 * Provides the implementation of all of the XLUpDisplay
 * methods.  The code isn't all that fascinating, as it's 
 * all a fairly brute force way of drawing strings and boxes
 * to the screen.
 *
 * The implementation here uses the old-school CS106B/X graphics
 * libraries, but it still works well.
 */

#include "xlup-graphics.h"
#include "gobjects.h"

static const double kDimension = 504; // 7 inches * 72 pixels / inch
static const double kWidthInset = 18;
static const double kCellPadding = 2;
static const string kCertifylMoveColor = "#5555aa";
static const string kVetoMoveColor = "#ff4444";
static const string kMoveColor = "#44aa44";

static const string kShadowMoveColor = "#ccffcc";
static const int kShortDelay = 20;
static const int kLongDelay = 100;

XLUpDisplay::XLUpDisplay() : GWindow(kDimension, kDimension) {
    cellDimension = 0;
    boardulx = 0;
    boarduly = 0;
}

void XLUpDisplay::drawBoard(const Grid<char>& grid) {
    clear();
    activeProvisionalMoves.clear();
    shadow.clear();
    this->grid = grid;
    cellDimension = (kDimension - 2 * kWidthInset) / grid.numCols();
	boardulx = (kDimension - grid.numCols() * cellDimension) / 2;
    boarduly = (kDimension - grid.numRows() * cellDimension) / 2;
	
	for (int row = 0; row < grid.numRows(); row++) {
		for (int col = 0; col < grid.numCols(); col++) {
            double ulx = boardulx + col * cellDimension + kCellPadding;
            double uly = boarduly + row * cellDimension + kCellPadding;
            double side = cellDimension - 2 * kCellPadding;
            drawFilledBox(ulx, uly, side, side, "White", "Gray");
            drawCenteredDigit(grid[row][col], ulx + side/2, uly + side/2, "Black");
		}
	}
}

void XLUpDisplay::officiallyMove(const coord& move) {
    if (grid[move.row][move.col] == ' ') {
        for (const coord& s: shadow)
            drawMove(s, "White");
        shadow.clear();
    }
    
	drawMove(move, kMoveColor);
	::pause(kLongDelay);
    
    if (grid[move.row][move.col] == ' ') {
        drawMove(move, "White");
    } else {
        shadow.add(move);
        drawMove(move, kShadowMoveColor);
    }
}

static const string kProvisionalMoveColor = "#ccccff";
static const string kActiveProvisionalMoveColor = "#2222aa";
void XLUpDisplay::provisonallyMove(const coord& move) {
    if (!activeProvisionalMoves.isEmpty()) {
        const coord& lastProvisionalMove =
            activeProvisionalMoves[activeProvisionalMoves.size() - 1];
        drawMove(lastProvisionalMove, kProvisionalMoveColor);
    }
    activeProvisionalMoves.add(move);
	drawMove(move, kActiveProvisionalMoveColor);
    pause(kShortDelay);
}
    
void XLUpDisplay::vetoProvisionalMove(const coord& move) {
	drawMove(move, kVetoMoveColor);
    pause(kShortDelay);
}

void XLUpDisplay::eraseProvisionalMove(const coord& move) {
	drawMove(move, "White");
    activeProvisionalMoves.remove(activeProvisionalMoves.size() - 1);
	redrawProvisionalMoves();
    pause(kShortDelay);
}

void XLUpDisplay::redrawProvisionalMoves() {
	for (int i = 0; i < activeProvisionalMoves.size(); i++) {
		drawMove(activeProvisionalMoves[i], kProvisionalMoveColor);
	}
}

void XLUpDisplay::drawMove(const coord& move, const string& color) {
	double cellulx = boardulx + move.col * cellDimension + kCellPadding;
	double celluly = boarduly + move.row * cellDimension + kCellPadding;
	
	double moveulx = boardulx + move.col * cellDimension + 4 * kCellPadding;
	double moveuly = boarduly + move.row * cellDimension + 4 * kCellPadding;
	double moveWidth = cellDimension - 8 * kCellPadding;
    double moveHeight = cellDimension - 8 * kCellPadding;
	drawFilledBox(moveulx, moveuly, moveWidth, moveHeight, color, color);
	double side = cellDimension - 2 * kCellPadding;
    drawBox(cellulx, celluly, side, side, "Gray");
}

void XLUpDisplay::drawBox(double ulx, double uly, double width, double height, const string& color) {
    setColor(color);
    drawRect(ulx, uly, width, height);
}

void XLUpDisplay::drawFilledBox(double ulx, double uly, double width, double height,
                                const string& fill, const string& border) {
    setColor(fill);
    fillRect(ulx, uly, width, height);
    setColor(border);
    drawRect(ulx, uly, width, height);
}

static const double kScaleFactor = 0.7;
void XLUpDisplay::drawCenteredDigit(char digit, double cx, double cy, const string& color) {
	string text = string(1, digit);
    GLabel *label = new GLabel(text);
    label->setFont("Courier-Bold-" + integerToString(kScaleFactor * cellDimension));
    label->setColor(color);
    double ulx = cx - label->getWidth()/2;
    double uly = cy + 2 * label->getFontAscent()/5;
    add(label, ulx, uly);
}

