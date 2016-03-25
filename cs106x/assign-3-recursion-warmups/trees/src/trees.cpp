/**
 * File: trees.cpp
 * ---------------
 * Draws a recursive tree as specified in the Assignment 3 handout.
 */

#include <string>    // for string
#include <iostream>  // for cout, endl
using namespace std;

#include "console.h" // required of all CS106 C++ programs
#include "gwindow.h" // for GWindow class and its setTitle, setColor, and drawPolarLine methods
#include "gtypes.h"  // for GPoint class
#include "gevents.h" // for the GMouseEvent type
#include "random.h"  // for randomChance function

const static double kWindowWidth = 600;
const static double kWindowHeight = 600;
const static string kWindowTitle = "Recursive Trees";
const static double kTrunkLength  = kWindowHeight/4;
const static double kShrinkFactor = 0.70;
const static int kBranchAngleSeparation = 15;
const static int kTrunkStartAngle = 90;
const static string kLeafColor = "#2e8b57";
const static string kTrunkColor = "#8b7765";
const static double kBranchProbability = 1.0;


static void drawTree(GWindow& window, int order, GPoint startPoint, int startAngle, double len) {
    if (order == 0)
    {
        window.setColor(kLeafColor);
        window.drawPolarLine(startPoint, len, startAngle);
    }
    else
    {
        double nextLen = len * kShrinkFactor;

        window.setColor(order < 2 ? kLeafColor : kTrunkColor);
        GPoint trunkEnd = window.drawPolarLine(startPoint, len, startAngle);

        for (int i = 0; i < 7; ++i)
        {
            if (randomReal(0.0, 1.0) < 0.8)
            {
                int angle = startAngle - 45 + i * kBranchAngleSeparation;
            
                drawTree(window, order - 1, trunkEnd, angle, nextLen);
            }  
        }
    }
}

static void drawTree(GWindow& window, int order) {
    GPoint trunkBase(window.getWidth()/2, window.getHeight());
    // GPoint trunkEnd(window.getWidth()/2, window.getHeight() - kTrunkLength);
    drawTree(window, order, trunkBase, kTrunkStartAngle, kTrunkLength);
}

const static int kHighestOrder = 5;
int main() {
    GWindow window(kWindowWidth, kWindowHeight);
    window.setWindowTitle(kWindowTitle);
    cout << "Repeatedly click the mouse in the graphics window to draw " << endl;
    cout << "recursive trees of higher and higher order." << endl;
    for (int order = 0; order <= kHighestOrder; order++) {
        waitForClick();
        window.clear();
        drawTree(window, order);
    }
    
    cout << endl;
    cout << "All trees through order " << kHighestOrder << " have been drawn." << endl;
    cout << "Click the mouse anywhere in the graphics window to quit." << endl;
    waitForClick();
    return 0;
}
