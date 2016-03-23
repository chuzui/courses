// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: rewrite this comment

#include <iostream>
#include <algorithm>
#include <cstdio>
#include "console.h"
#include "gwindow.h"
#include "grid.h"
#include "simpio.h"
#include "strlib.h"
#include "gbufferedimage.h"
#include "gevents.h"
#include "random.h"

using namespace std;

static const int    WHITE = 0xFFFFFF;
static const int    BLACK = 0x000000;
static const int    GREEN = 0x00FF00;

static bool     openImageFromFilename(GBufferedImage &img, string filename);
static bool 	saveImageToFilename(const GBufferedImage &img, string filename);
static void     getMouseClickLocation(int &row, int &col);
static void     scatter(GBufferedImage &img);
static void     edge_detection(GBufferedImage &img);
static void     green_screen(GBufferedImage &img);

/* Depending on how you approach your problem decomposition, you
 * may want to rewrite some of these lines, move them inside loops,
 * or move them inside helper functions, etc.
 *
 * TODO: rewrite this comment.
 */
int main() {
    GWindow gw;
    gw.setTitle("Fauxtoshop");
    gw.setVisible(true);

    cout << "Welcome to Fauxtoshop!" << endl;


    cout << "Enter name of image file to open (or blank to quiet): ";

    string img_name;
    getline(cin, img_name);

    cout << "Opening image file, may take a minute..." << endl;

    GBufferedImage img;
    while (!openImageFromFilename(img, img_name))
    {
        cout << "Can't open the file, please enter again: ";
        getline(cin, img_name);
    }

    gw.setSize(img.getWidth(), img.getHeight());
    gw.add(&img,0,0);

    string menu = "Which image filter would you like to apply?\n"
                  "         1 - Scatter\n"
                  "         2 - Edge detection\n"
                  "         3 - \"Green screen\" with another image\n"
                  "         4 - Compare image with another image";
    cout << menu << endl;

    string choice_str = "Your choice: ";
    int choice = getInteger(choice_str, choice_str);

    switch(choice)
    {
        case 1:
            scatter(img);
            break;
        case 2:
            edge_detection(img);
            break;
        case 3:
            green_screen(img);
            break;
    }


    int row, col;
    getMouseClickLocation(row, col);
    return 0;
}


/* STARTER CODE HELPER FUNCTION - DO NOT EDIT
 *
 * Attempts to open the image file 'filename'.
 *
 * This function returns true when the image file was successfully
 * opened and the 'img' object now contains that image, otherwise it
 * returns false.
 */
static bool openImageFromFilename(GBufferedImage &img, string filename) {
    try { img.load(filename); }
    catch (...) { return false; }
    return true;
}

/* STARTER CODE HELPER FUNCTION - DO NOT EDIT
 *
 * Attempts to save the image file to 'filename'.
 *
 * This function returns true when the image was successfully saved
 * to the file specified, otherwise it returns false.
 */
static bool saveImageToFilename(const GBufferedImage &img, string filename) {
    try {
        img.save(filename);
    } catch (...) {
        return false;
    }
    return true;
}

/* STARTER CODE HELPER FUNCTION - DO NOT EDIT
 *
 * Waits for a mouse click in the GWindow and reports click location.
 *
 * When this function returns, row and col are set to the row and
 * column where a mouse click was detected.
 */
static void getMouseClickLocation(int &row, int &col) {
    GMouseEvent me;
    do {
        me = getNextEvent(MOUSE_EVENT);
    } while (me.getEventType() != MOUSE_CLICKED);
    row = me.getY();
    col = me.getX();
}

static void scatter(GBufferedImage &img)
{
    cout << "Enter degree of scatter [1-100]: ";
    int degree;
    cin >> degree;

    Grid<int> original  = img.toGrid();
    int height  = original.height();
    int width = original.width();

    Grid<int> new_grid(height, width);

    for (int row = 0; row < height; ++row)
        for (int col = 0; col < width; ++col)
        {
            int left_col = max(0, col - degree);
            int right_col = min(width - 1, col + degree);
            int sample_col = randomInteger(left_col, right_col);

            int up_row = max(0, row - degree);
            int down_row = min(height - 1, row + degree);
            int sample_row = randomInteger(up_row, down_row);

            new_grid[row][col] = original[sample_row][sample_col];
        }

    img.fromGrid(new_grid);
}

static int rgb_diff(int rgb1, int rgb2)
{
    int red1, green1, blue1;
    GBufferedImage::getRedGreenBlue(rgb1, red1, green1, blue1);

    int red2, green2, blue2;
    GBufferedImage::getRedGreenBlue(rgb2, red2, green2, blue2);

    int red_diff = abs(red1 - red2);
    int green_diff = abs(green1 - green2);
    int blue_diff = abs(blue1 - blue2);

    return max(max(red_diff, green_diff), blue_diff);
}

static bool is_edge(const Grid<int>& original, int row, int col, int threshold)
{
    int height  = original.height();
    int width = original.width();

    int self_pixel = original[row][col];
    for (int row_step = -1; row_step <= 1; ++row_step)
        for (int col_step = -1; col_step <= 1; ++col_step)
        {
            int curr_row = row + row_step;
            int curr_col = col + col_step;

            if (curr_row >= 0 && curr_row < height &&
                curr_col >= 0 && curr_col < width)
            {
                int curr_pixel = original[curr_row][curr_col];
                if (rgb_diff(self_pixel, curr_pixel) > threshold)
                    return true;
            }
        }

    return false;
}

static void edge_detection(GBufferedImage &img)
{
    cout << "Enter threshold for edge detection: ";
    int threshold;
    cin >> threshold;

    Grid<int> original  = img.toGrid();
    int height  = original.height();
    int width = original.width();

    Grid<int> new_grid(height, width);

    for (int row = 0; row < height; ++row)
        for (int col = 0; col < width; ++col)
        {
            if (is_edge(original, row, col, threshold))
            {
                new_grid[row][col] = BLACK;
            }
            else
            {
                new_grid[row][col] = WHITE;
            }

        }

    img.fromGrid(new_grid);
}

static void green_screen(GBufferedImage &img)
{
    cout << "Now choose another file to add to your background image.\n";
    cout << "Enter name of image file to open: ";
    string img_name;
    getline(cin, img_name);

    cout << "Opening image file, may take a minute...\n";
    GBufferedImage sticker_img;
    while (!openImageFromFilename(sticker_img, img_name))
    {
        cout << "Can't open the file, please enter again: ";
        getline(cin, img_name);
    }

    string choose_threshold = "Now choose a tolerance threshold: ";
    int threshold = getInteger(choose_threshold, choose_threshold);

    cout << "Enter location to place image as \"(row, col)\" (or blank to use mouse): ";
    string location;
    getline(cin, location);

    int loc_row, loc_col;
    while(sscanf(location.c_str(), "(%d,%d)", &loc_row, &loc_col) != 2)
    {
        if (location.size() == 0)
        {
            cout << "Now click the background image to place image: " << endl;
            getMouseClickLocation(loc_row, loc_col);
            cout << "You chose " << loc_row << "," << loc_col << endl;
            break;
        }
        else
        {
            cout << "Can't read location, please enter again: ";
            getline(cin, location);
        }
    }


    Grid<int> original  = img.toGrid();
    int ori_height  = original.height();
    int ori_width = original.width();

    Grid<int> sticker  = sticker_img.toGrid();
    int sticker_height  = sticker.height();
    int sticker_width = sticker.width();

    for (int row = 0; row < sticker_height; ++row)
        for (int col = 0; col < sticker_width; ++col)
        {
            int ori_row = loc_row + row;
            int ori_col = loc_col + col;

            if (ori_row < ori_height && ori_col < ori_width)
            {
                int pixel = sticker[row][col];
                if (rgb_diff(pixel, GREEN) > threshold)
                {
                    original[ori_row][ori_col] = pixel;
                }
            }
        }

    img.fromGrid(original);
}
